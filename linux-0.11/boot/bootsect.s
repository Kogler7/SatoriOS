; 该文件应该被编译并存储在硬盘的 0 盘 0 道 1 扇区(即启动区的第一扇区)

; 整个编译过程，就是通过 Makefile 和 build.c 配合完成的，最终会：
; 1. 把 bootsect.s 编译成 bootsect 放在硬盘的 1 扇区。
; 2. 把 setup.s 编译成 setup 放在硬盘的 2~5 扇区。
; 3. 把剩下的全部代码（head.s 作为开头）编译成 system 放在硬盘的随后 240 个扇区。

; SYS_SIZE is the number of clicks (16 bytes) to be loaded.
; 0x3000 is 0x30000 bytes = 196kB, more than enough for current
; versions of linux
;
SYSSIZE = 0x3000
;
;	bootsect.s		(C) 1991 Linus Torvalds
;
; bootsect.s is loaded at 0x7c00 by the bios-startup routines, and moves
; iself out of the way to address 0x90000, and jumps there.
; BIOS 会将该程序搬运到内存的 0x7c00 这个位置，而 CPU 也会从这个位置开始执行
; It then loads 'setup' directly after itself (0x90200), and the system
; at 0x10000, using BIOS interrupts. 
;
; NOTE; currently system is at most 8*65536 bytes long. This should be no
; problem, even in the future. I want to keep it simple. This 512 kB
; kernel size should be enough, especially as this doesn't contain the
; buffer cache as in minix
;
; The loader has been made as simple as possible, and continuos
; read errors will result in a unbreakable loop. Reboot by hand. It
; loads pretty fast by getting whole sectors at a time whenever possible.

.globl begtext, begdata, begbss, endtext, enddata, endbss
.text
begtext:
.data
begdata:
.bss
begbss:
.text

SETUPLEN = 4				; nr of setup-sectors
BOOTSEG  = 0x07c0			; original address of boot-sector
INITSEG  = 0x9000			; we move boot here - out of the way
SETUPSEG = 0x9020			; setup starts here
SYSSEG   = 0x1000			; system loaded at 0x10000 (65536).
ENDSEG   = SYSSEG + SYSSIZE		; where to stop loading

; ROOT_DEV:	0x000 - same type of floppy as boot.
;		0x301 - first partition on first drive etc
ROOT_DEV = 0x306

entry start
start:
	mov	ax,#BOOTSEG
	mov	ds,ax ;DS=0x7c0，充当段基址的作用
	; x86 为了让自己在 16 位这个实模式下能访问到 20 位的地址线，段基址要先左移四位。
	; 0x07c0 左移四位就是 0x7c00，那这就刚好和这段代码被 BIOS 加载到的内存地址 0x7c00 一样
	mov	ax,#INITSEG
	mov	es,ax ;ES=0x9000
	mov	cx,#256
	; 0x9000~0x91ff 总计 256 个字(512 字节)的空间，用来存放 setup 程序
	sub	si,si
	sub	di,di
	; 清空 si, di 寄存器
	; 用 ES:DI 指向 0x9000，用 DS:SI 指向 0x7c00
	rep
	movw
	; 将 0x7c00~0x7dff 的内容复制到 0x9000~0x91ff
	jmpi	go,INITSEG
	; jmpi 是一个段间跳转指令，表示跳转到 0x9000:go 处执行
	; 跳转到 0x9000，即 go 函数
go:	mov	ax,cs ;AX=0x9000
	; cs 寄存器表示代码段寄存器
	; CPU 当前正在执行的代码在内存中的位置，就是由 cs:ip 这组寄存器配合指向的
	; 其中 cs 是基址，ip 是偏移地址
	; 因此 cs 寄存器的值就是 0x9000
	mov	ds,ax ;DS=0x9000，跳转后自然 DS 也要跟着变
	mov	es,ax ;ES=0x9000
; put stack at 0x9ff00.
	; ss 为栈段寄存器，后面要配合栈基址寄存器 sp 来表示此时的栈顶地址
	; 栈由内存高地址向低地址发展，栈底地址就是 0x9ff00
	; 0x9000~0x9ff00 总计 64KB 的空间，栈空间足够，保证栈中内容一般不会影响至代码段
	mov	ss,ax ;SS=0x9000
	mov	sp,#0xFF00		; SP=0x9ff00

; load the setup-sectors directly after the bootblock.
; Note that 'es' is already set up.

load_setup:
	; 将硬盘的第 2 个扇区开始，把数据加载到内存 0x90200 处，共加载 4 个扇区
	mov	dx,#0x0000		; drive 0, head 0
	; dx 寄存器的低 8 位表示磁盘驱动器号，高 8 位表示磁头号
	mov	cx,#0x0002		; sector 2, track 0
	; cx 寄存器的低 8 位表示扇区号，中间 8 位表示磁道号，高 8 位保留（存疑？）
	mov	bx,#0x0200		; address = 512, in INITSEG
	; bx 寄存器的低 8 位表示偏移地址，高 8 位表示段基址
	mov	ax,#0x0200+SETUPLEN	; service 2, nr of sectors
	; ax 寄存器的低 8 位表示要读取的扇区数（共4个扇区），高 8 位表示要调用的 BIOS 中断号
	int	0x13			; read it
	; 13h 号中断是 BIOS 中的磁盘读写服务
	; 读取磁盘上的 setup 程序，放到 0x9020~0x9fff
	jnc	ok_load_setup		; ok - continue
	mov	dx,#0x0000
	mov	ax,#0x0000		; reset the diskette
	int	0x13
	j	load_setup

ok_load_setup:

; Get disk drive parameters, specifically nr of sectors/track

	mov	dl,#0x00
	; dl 寄存器的低 8 位表示磁盘驱动器号
	mov	ax,#0x0800		; service 8, get drive parameters
	; AH=8 是 BIOS 中的获取磁盘参数服务
	; AL=0 表示获取驱动器 0 的参数
	int	0x13
	; 13h 号中断是 BIOS 中的磁盘读写服务
	mov	ch,#0x00
	seg cs
	mov	sectors,cx
	mov	ax,#INITSEG
	mov	es,ax

; Print some inane message

	mov	ah,#0x03		; read cursor pos
	xor	bh,bh
	int	0x10
	
	mov	cx,#24
	mov	bx,#0x0007		; page 0, attribute 7 (normal)
	mov	bp,#msg1
	mov	ax,#0x1301		; write string, move cursor
	int	0x10

; ok, we've written the message, now
; we want to load the system (at 0x10000)
; 省略了很多非主逻辑的代码，比如在屏幕上输出 Loading system ... 这个字符串以防止用户等烦了
; 把从硬盘第 6 个扇区开始往后的 240 个扇区，加载到内存 0x10000 处

	mov	ax,#SYSSEG	; load system at 0x10000
	mov	es,ax		; segment of 0x010000
	call	read_it
	call	kill_motor

; After that we check which root-device to use. If the device is
; defined (!= 0), nothing is done and the given device is used.
; Otherwise, either /dev/PS0 (2,28) or /dev/at0 (2,8), depending
; on the number of sectors that the BIOS reports currently.

	seg cs
	mov	ax,root_dev
	cmp	ax,#0
	jne	root_defined
	seg cs
	mov	bx,sectors
	mov	ax,#0x0208		; /dev/ps0 - 1.2Mb
	cmp	bx,#15
	je	root_defined
	mov	ax,#0x021c		; /dev/PS0 - 1.44Mb
	cmp	bx,#18
	je	root_defined
undef_root:
	jmp undef_root
root_defined:
	seg cs
	mov	root_dev,ax

; after that (everyting loaded), we jump to
; the setup-routine loaded directly after
; the bootblock:

	jmpi	0,SETUPSEG

; This routine loads the system at address 0x10000, making sure
; no 64kB boundaries are crossed. We try to load it as fast as
; possible, loading whole tracks whenever we can.
;
; in:	es - starting address segment (normally 0x1000)
;
sread:	.word 1+SETUPLEN	; sectors read of current track
head:	.word 0			; current head
track:	.word 0			; current track

read_it:
	mov ax,es
	test ax,#0x0fff
die:	jne die			; es must be at 64kB boundary
	xor bx,bx		; bx is starting address within segment
rp_read:
	mov ax,es
	cmp ax,#ENDSEG		; have we loaded all yet?
	jb ok1_read
	ret
ok1_read:
	seg cs
	mov ax,sectors
	sub ax,sread
	mov cx,ax
	shl cx,#9
	add cx,bx
	jnc ok2_read
	je ok2_read
	xor ax,ax
	sub ax,bx
	shr ax,#9
ok2_read:
	call read_track
	mov cx,ax
	add ax,sread
	seg cs
	cmp ax,sectors
	jne ok3_read
	mov ax,#1
	sub ax,head
	jne ok4_read
	inc track
ok4_read:
	mov head,ax
	xor ax,ax
ok3_read:
	mov sread,ax
	shl cx,#9
	add bx,cx
	jnc rp_read
	mov ax,es
	add ax,#0x1000
	mov es,ax
	xor bx,bx
	jmp rp_read

read_track:
	push ax
	push bx
	push cx
	push dx
	mov dx,track
	mov cx,sread
	inc cx
	mov ch,dl
	mov dx,head
	mov dh,dl
	mov dl,#0
	and dx,#0x0100
	mov ah,#2
	int 0x13
	jc bad_rt
	pop dx
	pop cx
	pop bx
	pop ax
	ret
bad_rt:	mov ax,#0
	mov dx,#0
	int 0x13
	pop dx
	pop cx
	pop bx
	pop ax
	jmp read_track

/*
 * This procedure turns off the floppy drive motor, so
 * that we enter the kernel in a known state, and
 * don't have to worry about it later.
 */
kill_motor:
	push dx
	mov dx,#0x3f2
	mov al,#0
	outb
	pop dx
	ret

sectors:
	.word 0

msg1:
	.byte 13,10
	.ascii "Loading system ..."
	.byte 13,10,13,10

.org 508
root_dev:
	.word ROOT_DEV
boot_flag:
	.word 0xAA55

.text
endtext:
.data
enddata:
.bss
endbss:
