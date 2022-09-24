;
;	setup.s		(C) 1991 Linus Torvalds
;
; setup.s is responsible for getting the system data from the BIOS,
; and putting them into the appropriate places in system memory.
; both setup.s and system has been loaded by the bootblock.
;
; This code asks the bios for memory/disk/other parameters, and
; puts them in a "safe" place: 0x90000-0x901FF, ie where the
; boot-block used to be. It is then up to the protected mode
; system to read them from there before the area is overwritten
; for buffer-blocks.
;

; NOTE; These had better be the same as in bootsect.s;

INITSEG  = 0x9000	; we move boot here - out of the way
SYSSEG   = 0x1000	; system loaded at 0x10000 (65536).
SETUPSEG = 0x9020	; this is the current segment

.globl begtext, begdata, begbss, endtext, enddata, endbss
.text
begtext:
.data
begdata:
.bss
begbss:
.text

entry start
start:

; ok, the read went well so we get current cursor position and save it for
; posterity.
	; 计算机在加电自检后会自动初始化到文字模式
	; 在这种模式下，一屏幕可以显示 25 行，每行 80 个字符，也就是 80 列
	mov	ax,#INITSEG	; this is done in bootsect already, but...
	mov	ds,ax
	mov	ah,#0x03	; read cursor pos
	xor	bh,bh
	int	0x10		; save it in known place, con_init fetches
	; 触发 BIOS 提供的显示服务中断处理程序
	; 而 ah 寄存器被赋值为 0x03 表示显示服务里具体的读取光标位置功能
	mov	[0],dx		; it from 0x90000.
	; int 0x10 中断程序执行完毕并返回时，dx 寄存器里的值表示光标的位置
	; 具体说来其高八位 dh 存储了行号，低八位 dl 存储了列号
	; 由于 BIOS 中的光标位置是从 0 开始计数的，所以这里的行号和列号都要减 1
	; 这个内存地址仅仅是偏移地址，还需要加上 ds 这个寄存器里存储的段基址
	; 最终的内存地址是在 0x90000 处，这里存放着光标的位置，以便之后在初始化控制台的时候用到

; Get memory size (extended mem, kB)
; 从 BIOS 中获取内存大小

	mov	ah,#0x88
	int	0x15
	mov	[2],ax

; Get video-card data:
; 从 BIOS 中获取显卡信息

	mov	ah,#0x0f
	int	0x10
	mov	[4],bx		; bh = display page
	mov	[6],ax		; al = video mode, ah = window width

; check for EGA/VGA and some config parameters
; 检查是否为 EGA/VGA 显卡，以及一些配置参数

	mov	ah,#0x12
	mov	bl,#0x10
	int	0x10
	mov	[8],ax
	mov	[10],bx
	mov	[12],cx

; Get hd0 data
; 从 BIOS 中获取硬盘 0 的信息

	mov	ax,#0x0000
	mov	ds,ax
	lds	si,[4*0x41]
	mov	ax,#INITSEG
	mov	es,ax
	mov	di,#0x0080
	mov	cx,#0x10
	rep
	movsb

; Get hd1 data
; 从 BIOS 中获取硬盘 1 的信息

	mov	ax,#0x0000
	mov	ds,ax
	lds	si,[4*0x46]
	mov	ax,#INITSEG
	mov	es,ax
	mov	di,#0x0090
	mov	cx,#0x10
	rep
	movsb

; Check that there IS a hd1 :-)
; 检查硬盘 1 是否存在

	mov	ax,#0x01500
	mov	dl,#0x81
	int	0x13
	jc	no_disk1
	cmp	ah,#3
	je	is_disk1
no_disk1:
	mov	ax,#INITSEG
	mov	es,ax
	mov	di,#0x0090
	mov	cx,#0x10
	mov	ax,#0x00
	rep
	stosb
is_disk1:
; 0x90000 开始往上的位置，原来是 bootsect 和 setup 程序的代码
; 现 bootsect 的一部分代码在已经被操作系统为了记录内存、硬盘、显卡等一些临时存放的数据给覆盖了一部分

; now we want to move to protected mode ...
; 现在我们要进入保护模式了...

	cli			; no interrupts allowed ;
	; 关闭中断
	; 保护模式下，中断是由 CPU 来处理的，而不是由 BIOS 来处理，所以在进入保护模式之前，必须关闭中断
	; 以免在进入保护模式之前，CPU 产生中断，这样就会导致进入保护模式失败
	
	; 但是在关闭中断之后，CPU 会丢失中断请求
	; 所以在进入保护模式之后，必须重新打开中断，以便 CPU 能够处理中断请求

	; 后面我们要把原本是 BIOS 写好的中断向量表给覆盖掉
	; 也就是给破坏掉了，写上我们自己的中断向量表，所以这个时候是不允许中断进来的

; first we move the system to it's rightful place
; 首先我们把系统移动到它应该在的地方
; 把内存地址 0x10000 处开始往后一直到 0x90000 的系统，统统复制到内存的最开始的 0 位置开始的地方
; 0x10000 处是 BIOS 用来存放系统的地方，而 0x00000 处是我们自己用来存放系统的地方

	mov	ax,#0x0000
	cld			; 'direction'=0, movs moves forward
do_move:
	mov	es,ax		; destination segment
	add	ax,#0x1000
	cmp	ax,#0x9000
	jz	end_move
	mov	ds,ax		; source segment
	sub	di,di
	sub	si,si
	mov 	cx,#0x8000
	rep
	movsw
	jmp	do_move

; then we load the segment descriptors

end_move:
	mov	ax,#SETUPSEG	; right, forgot this at first. didn't work :-)
	mov	ds,ax
	lidt	idt_48		; load idt with 0,0
	lgdt	gdt_48		; load gdt with whatever appropriate

; that was painless, now we enable A20

	call	empty_8042
	mov	al,#0xD1		; command write
	out	#0x64,al
	call	empty_8042
	mov	al,#0xDF		; A20 on
	out	#0x60,al
	call	empty_8042

; well, that went ok, I hope. Now we have to reprogram the interrupts :-(
; we put them right after the intel-reserved hardware interrupts, at
; int 0x20-0x2F. There they won't mess up anything. Sadly IBM really
; messed this up with the original PC, and they haven't been able to
; rectify it afterwards. Thus the bios puts interrupts at 0x08-0x0f,
; which is used for the internal hardware interrupts as well. We just
; have to reprogram the 8259's, and it isn't fun.

	mov	al,#0x11		; initialization sequence
	out	#0x20,al		; send it to 8259A-1
	.word	0x00eb,0x00eb		; jmp $+2, jmp $+2
	out	#0xA0,al		; and to 8259A-2
	.word	0x00eb,0x00eb
	mov	al,#0x20		; start of hardware int's (0x20)
	out	#0x21,al
	.word	0x00eb,0x00eb
	mov	al,#0x28		; start of hardware int's 2 (0x28)
	out	#0xA1,al
	.word	0x00eb,0x00eb
	mov	al,#0x04		; 8259-1 is master
	out	#0x21,al
	.word	0x00eb,0x00eb
	mov	al,#0x02		; 8259-2 is slave
	out	#0xA1,al
	.word	0x00eb,0x00eb
	mov	al,#0x01		; 8086 mode for both
	out	#0x21,al
	.word	0x00eb,0x00eb
	out	#0xA1,al
	.word	0x00eb,0x00eb
	mov	al,#0xFF		; mask off all interrupts for now
	out	#0x21,al
	.word	0x00eb,0x00eb
	out	#0xA1,al

; well, that certainly wasn't fun :-(. Hopefully it works, and we don't
; need no steenking BIOS anyway (except for the initial loading :-).
; The BIOS-routine wants lots of unnecessary data, and it's less
; "interesting" anyway. This is how REAL programmers do it.
;
; Well, now's the time to actually move into protected mode. To make
; things as simple as possible, we do no register set-up or anything,
; we let the gnu-compiled 32-bit programs do that. We just jump to
; absolute address 0x00000, in 32-bit protected mode.

	mov	ax,#0x0001	; protected mode (PE) bit
	lmsw	ax		; This is it;
	jmpi	0,8		; jmp offset 0 of segment 8 (cs)

; This routine checks that the keyboard command queue is empty
; No timeout is used - if this hangs there is something wrong with
; the machine, and we probably couldn't proceed anyway.
empty_8042:
	.word	0x00eb,0x00eb
	in	al,#0x64	; 8042 status port
	test	al,#2		; is input buffer full?
	jnz	empty_8042	; yes - loop
	ret

gdt:
	.word	0,0,0,0		; dummy

	.word	0x07FF		; 8Mb - limit=2047 (2048*4096=8Mb)
	.word	0x0000		; base address=0
	.word	0x9A00		; code read/exec
	.word	0x00C0		; granularity=4096, 386

	.word	0x07FF		; 8Mb - limit=2047 (2048*4096=8Mb)
	.word	0x0000		; base address=0
	.word	0x9200		; data read/write
	.word	0x00C0		; granularity=4096, 386

idt_48:
	.word	0			; idt limit=0
	.word	0,0			; idt base=0L

gdt_48:
	.word	0x800		; gdt limit=2048, 256 GDT entries
	.word	512+gdt,0x9	; gdt base = 0X9xxxx
	
.text
endtext:
.data
enddata:
.bss
endbss:
