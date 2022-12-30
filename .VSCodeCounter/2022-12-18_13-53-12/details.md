# Details

Date : 2022-12-18 13:53:12

Directory d:\\CodeBase\\satori-os

Total : 140 files,  7279 codes, 456 comments, 1508 blanks, all 9243 lines

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [Makefile](/Makefile) | Makefile | 11 | 0 | 4 | 15 |
| [README.md](/README.md) | Markdown | 23 | 0 | 2 | 25 |
| [build.md](/build.md) | Markdown | 1 | 0 | 2 | 3 |
| [include/app/vim.h](/include/app/vim.h) | C++ | 4 | 0 | 2 | 6 |
| [include/arch/loongarch.h](/include/arch/loongarch.h) | C | 184 | 16 | 38 | 238 |
| [include/arch/ls7a.h](/include/arch/ls7a.h) | C | 18 | 1 | 8 | 27 |
| [include/arch/port.h](/include/arch/port.h) | C | 9 | 0 | 3 | 12 |
| [include/boot/boot_param.h](/include/boot/boot_param.h) | C | 81 | 6 | 20 | 107 |
| [include/config/config.h](/include/config/config.h) | C++ | 1 | 0 | 0 | 1 |
| [include/config/info.h](/include/config/info.h) | C | 12 | 0 | 3 | 15 |
| [include/config/kbdmap.h](/include/config/kbdmap.h) | C | 262 | 16 | 17 | 295 |
| [include/drivers/ansi.h](/include/drivers/ansi.h) | C | 212 | 26 | 39 | 277 |
| [include/drivers/driver.md](/include/drivers/driver.md) | Markdown | 6 | 0 | 7 | 13 |
| [include/drivers/kbd.h](/include/drivers/kbd.h) | C | 28 | 0 | 9 | 37 |
| [include/drivers/rtx.h](/include/drivers/rtx.h) | C++ | 79 | 3 | 25 | 107 |
| [include/drivers/serial.h](/include/drivers/serial.h) | C | 18 | 1 | 6 | 25 |
| [include/drivers/vdsk.h](/include/drivers/vdsk.h) | C++ | 3 | 1 | 3 | 7 |
| [include/fs/dir.h](/include/fs/dir.h) | C++ | 3 | 0 | 2 | 5 |
| [include/fs/fs-old.h](/include/fs/fs-old.h) | C++ | 26 | 1 | 6 | 33 |
| [include/fs/fs.h](/include/fs/fs.h) | C++ | 3 | 0 | 3 | 6 |
| [include/fs/rfs.h](/include/fs/rfs.h) | C++ | 3 | 0 | 2 | 5 |
| [include/fs/tfs.h](/include/fs/tfs.h) | C++ | 3 | 0 | 3 | 6 |
| [include/fs/vfs.h](/include/fs/vfs.h) | C++ | 18 | 0 | 6 | 24 |
| [include/gcc.h](/include/gcc.h) | C++ | 29 | 0 | 10 | 39 |
| [include/io/kbdin.h](/include/io/kbdin.h) | C++ | 12 | 0 | 5 | 17 |
| [include/io/kinfo.h](/include/io/kinfo.h) | C | 50 | 0 | 10 | 60 |
| [include/io/stdin.h](/include/io/stdin.h) | C | 15 | 0 | 11 | 26 |
| [include/io/stdio.h](/include/io/stdio.h) | C | 5 | 0 | 3 | 8 |
| [include/io/stdout.h](/include/io/stdout.h) | C | 36 | 0 | 9 | 45 |
| [include/isp/asm.h](/include/isp/asm.h) | C++ | 3 | 0 | 3 | 6 |
| [include/isp/isp.h](/include/isp/isp.h) | C++ | 20 | 0 | 6 | 26 |
| [include/isp/prep.h](/include/isp/prep.h) | C++ | 3 | 0 | 3 | 6 |
| [include/lib/buffer.h](/include/lib/buffer.h) | C | 41 | 0 | 14 | 55 |
| [include/lib/map.h](/include/lib/map.h) | C++ | 11 | 0 | 5 | 16 |
| [include/lib/string.h](/include/lib/string.h) | C | 12 | 0 | 3 | 15 |
| [include/lib/text.h](/include/lib/text.h) | C | 68 | 0 | 23 | 91 |
| [include/mm/bitmap.h](/include/mm/bitmap.h) | C | 10 | 0 | 6 | 16 |
| [include/mm/buddy.h](/include/mm/buddy.h) | C++ | 24 | 0 | 6 | 30 |
| [include/mm/kmalloc.h](/include/mm/kmalloc.h) | C++ | 9 | 0 | 3 | 12 |
| [include/mm/malloc.h](/include/mm/malloc.h) | C++ | 9 | 0 | 3 | 12 |
| [include/mm/mem_block.h](/include/mm/mem_block.h) | C | 6 | 0 | 0 | 6 |
| [include/mm/mm.h](/include/mm/mm.h) | C++ | 27 | 0 | 17 | 44 |
| [include/mm/mm_types.h](/include/mm/mm_types.h) | C++ | 11 | 0 | 5 | 16 |
| [include/mm/slab.h](/include/mm/slab.h) | C++ | 33 | 0 | 9 | 42 |
| [include/mm/sys_heap.h](/include/mm/sys_heap.h) | C++ | 12 | 0 | 4 | 16 |
| [include/sched/pcb.h](/include/sched/pcb.h) | C++ | 16 | 0 | 3 | 19 |
| [include/sched/sched.h](/include/sched/sched.h) | C++ | 3 | 0 | 3 | 6 |
| [include/shell/impl.h](/include/shell/impl.h) | C | 15 | 0 | 2 | 17 |
| [include/shell/parser.h](/include/shell/parser.h) | C++ | 6 | 0 | 2 | 8 |
| [include/shell/shell.h](/include/shell/shell.h) | C | 29 | 0 | 10 | 39 |
| [include/sys/syscall.h](/include/sys/syscall.h) | C++ | 36 | 0 | 13 | 49 |
| [include/temp/larchintrin.h](/include/temp/larchintrin.h) | C | 178 | 72 | 47 | 297 |
| [include/types.h](/include/types.h) | C | 27 | 0 | 8 | 35 |
| [include/vpu/addr.h](/include/vpu/addr.h) | C++ | 14 | 0 | 5 | 19 |
| [include/vpu/exec.h](/include/vpu/exec.h) | C++ | 22 | 0 | 7 | 29 |
| [include/vpu/gate.h](/include/vpu/gate.h) | C++ | 14 | 0 | 3 | 17 |
| [include/vpu/instr.h](/include/vpu/instr.h) | C++ | 91 | 8 | 36 | 135 |
| [include/vpu/page.h](/include/vpu/page.h) | C++ | 24 | 0 | 5 | 29 |
| [include/vpu/vdt.h](/include/vpu/vdt.h) | C++ | 50 | 0 | 9 | 59 |
| [include/vpu/vmmu.h](/include/vpu/vmmu.h) | C++ | 10 | 0 | 5 | 15 |
| [include/vpu/vpu.h](/include/vpu/vpu.h) | C++ | 76 | 1 | 20 | 97 |
| [include/vpu/vpu.md](/include/vpu/vpu.md) | Markdown | 23 | 0 | 21 | 44 |
| [include/vpu/vtlb.h](/include/vpu/vtlb.h) | C++ | 18 | 0 | 5 | 23 |
| [kernel/Makefile](/kernel/Makefile) | Makefile | 31 | 0 | 10 | 41 |
| [kernel/app/Makefile](/kernel/app/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/app/tester.c](/kernel/app/tester.c) | C | 0 | 0 | 1 | 1 |
| [kernel/app/vim.c](/kernel/app/vim.c) | C | 104 | 19 | 5 | 128 |
| [kernel/boot/Makefile](/kernel/boot/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/boot/boot_param.c](/kernel/boot/boot_param.c) | C | 143 | 16 | 30 | 189 |
| [kernel/config/Makefile](/kernel/config/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/config/config.md](/kernel/config/config.md) | Markdown | 0 | 0 | 1 | 1 |
| [kernel/config/info.c](/kernel/config/info.c) | C | 25 | 0 | 9 | 34 |
| [kernel/config/keymap.c](/kernel/config/keymap.c) | C | 146 | 6 | 8 | 160 |
| [kernel/drivers/Makefile](/kernel/drivers/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/drivers/ansi.c](/kernel/drivers/ansi.c) | C | 33 | 0 | 7 | 40 |
| [kernel/drivers/driver.md](/kernel/drivers/driver.md) | Markdown | 1 | 0 | 1 | 2 |
| [kernel/drivers/kbd.c](/kernel/drivers/kbd.c) | C | 117 | 2 | 13 | 132 |
| [kernel/drivers/rtx.c](/kernel/drivers/rtx.c) | C | 70 | 3 | 9 | 82 |
| [kernel/entry.c](/kernel/entry.c) | C | 33 | 4 | 6 | 43 |
| [kernel/fs/Makefile](/kernel/fs/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/fs/filesys.md](/kernel/fs/filesys.md) | Markdown | 12 | 0 | 12 | 24 |
| [kernel/fs/fs-old.c](/kernel/fs/fs-old.c) | C | 253 | 3 | 16 | 272 |
| [kernel/fs/fs.c](/kernel/fs/fs.c) | C | 0 | 0 | 1 | 1 |
| [kernel/io/Makefile](/kernel/io/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/io/kbdin.c](/kernel/io/kbdin.c) | C | 49 | 0 | 6 | 55 |
| [kernel/io/stdin.c](/kernel/io/stdin.c) | C | 70 | 7 | 10 | 87 |
| [kernel/io/stdout.c](/kernel/io/stdout.c) | C | 109 | 1 | 11 | 121 |
| [kernel/isp/Makefile](/kernel/isp/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/isp/asm.c](/kernel/isp/asm.c) | C | 0 | 0 | 1 | 1 |
| [kernel/isp/exec.c](/kernel/isp/exec.c) | C | 0 | 0 | 1 | 1 |
| [kernel/isp/prep.c](/kernel/isp/prep.c) | C | 1 | 0 | 0 | 1 |
| [kernel/kernel.md](/kernel/kernel.md) | Markdown | 2 | 0 | 2 | 4 |
| [kernel/lib/Makefile](/kernel/lib/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/lib/buffer.c](/kernel/lib/buffer.c) | C | 113 | 1 | 13 | 127 |
| [kernel/lib/string.c](/kernel/lib/string.c) | C | 118 | 10 | 9 | 137 |
| [kernel/lib/text.c](/kernel/lib/text.c) | C | 573 | 36 | 42 | 651 |
| [kernel/mm/Makefile](/kernel/mm/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/mm/bitmap.c](/kernel/mm/bitmap.c) | C | 93 | 2 | 6 | 101 |
| [kernel/mm/buddy.c](/kernel/mm/buddy.c) | C | 122 | 2 | 10 | 134 |
| [kernel/mm/cache.c](/kernel/mm/cache.c) | C | 0 | 0 | 1 | 1 |
| [kernel/mm/kmalloc.c](/kernel/mm/kmalloc.c) | C | 31 | 0 | 5 | 36 |
| [kernel/mm/malloc.c](/kernel/mm/malloc.c) | C | 37 | 0 | 4 | 41 |
| [kernel/mm/mem_block.c](/kernel/mm/mem_block.c) | C | 1 | 7 | 4 | 12 |
| [kernel/mm/memory.md](/kernel/mm/memory.md) | Markdown | 72 | 0 | 60 | 132 |
| [kernel/mm/mm.c](/kernel/mm/mm.c) | C | 37 | 29 | 8 | 74 |
| [kernel/mm/page.c](/kernel/mm/page.c) | C | 0 | 24 | 1 | 25 |
| [kernel/mm/slab.c](/kernel/mm/slab.c) | C | 16 | 6 | 3 | 25 |
| [kernel/mm/sys_heap.c](/kernel/mm/sys_heap.c) | C | 77 | 0 | 9 | 86 |
| [kernel/mm/tlb.c](/kernel/mm/tlb.c) | C | 0 | 57 | 9 | 66 |
| [kernel/sched/Makefile](/kernel/sched/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/sched/sched.c](/kernel/sched/sched.c) | C | 2 | 4 | 2 | 8 |
| [kernel/sched/sched.md](/kernel/sched/sched.md) | Markdown | 2 | 0 | 2 | 4 |
| [kernel/shell/Makefile](/kernel/shell/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/shell/cmd.c](/kernel/shell/cmd.c) | C | 238 | 0 | 1 | 239 |
| [kernel/shell/impl.c](/kernel/shell/impl.c) | C | 105 | 5 | 8 | 118 |
| [kernel/shell/parser.c](/kernel/shell/parser.c) | C | 109 | 7 | 9 | 125 |
| [kernel/shell/shell.c](/kernel/shell/shell.c) | C | 25 | 0 | 4 | 29 |
| [kernel/shell/shell.md](/kernel/shell/shell.md) | Markdown | 19 | 0 | 3 | 22 |
| [kernel/sys/Makefile](/kernel/sys/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/sys/syscall.c](/kernel/sys/syscall.c) | C | 33 | 0 | 3 | 36 |
| [kernel/sys/syscall.md](/kernel/sys/syscall.md) | Markdown | 0 | 0 | 1 | 1 |
| [kernel/trap/Makefile](/kernel/trap/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/trap/entry.c](/kernel/trap/entry.c) | C | 73 | 2 | 0 | 75 |
| [kernel/trap/extioi.c](/kernel/trap/extioi.c) | C | 19 | 6 | 7 | 32 |
| [kernel/trap/handle.c](/kernel/trap/handle.c) | C | 70 | 2 | 15 | 87 |
| [kernel/trap/i8042.c](/kernel/trap/i8042.c) | C | 27 | 24 | 12 | 63 |
| [kernel/trap/init.c](/kernel/trap/init.c) | C | 21 | 0 | 7 | 28 |
| [kernel/trap/ls7a.c](/kernel/trap/ls7a.c) | C | 18 | 6 | 8 | 32 |
| [kernel/trap/trap.md](/kernel/trap/trap.md) | Markdown | 49 | 0 | 25 | 74 |
| [kernel/vpu/Makefile](/kernel/vpu/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/vpu/instr.c](/kernel/vpu/instr.c) | C | 264 | 0 | 34 | 298 |
| [kernel/vpu/vmmu.c](/kernel/vpu/vmmu.c) | C | 33 | 0 | 2 | 35 |
| [kernel/vpu/vpu.c](/kernel/vpu/vpu.c) | C | 86 | 0 | 8 | 94 |
| [kernel/vpu/vtlb.c](/kernel/vpu/vtlb.c) | C | 37 | 0 | 6 | 43 |
| [notes.md](/notes.md) | Markdown | 0 | 0 | 2 | 2 |
| [report/Final report.md](/report/Final%20report.md) | Markdown | 1,009 | 0 | 325 | 1,334 |
| [run_loongarch.sh](/run_loongarch.sh) | Shell Script | 61 | 13 | 6 | 80 |
| [start.sh](/start.sh) | Shell Script | 4 | 0 | 1 | 5 |
| [tools/mmp.csv](/tools/mmp.csv) | CSV | 16 | 0 | 1 | 17 |
| [tools/vis_mmap.py](/tools/vis_mmap.py) | Python | 112 | 0 | 16 | 128 |

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)