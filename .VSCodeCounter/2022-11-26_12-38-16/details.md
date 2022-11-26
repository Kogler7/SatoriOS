# Details

Date : 2022-11-26 12:38:16

Directory d:\\CodeBase\\satori-os

Total : 89 files,  3899 codes, 375 comments, 689 blanks, all 4963 lines

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [Makefile](/Makefile) | Makefile | 11 | 0 | 4 | 15 |
| [README.md](/README.md) | Markdown | 23 | 0 | 2 | 25 |
| [build.md](/build.md) | Markdown | 1 | 0 | 2 | 3 |
| [include/app/vim.h](/include/app/vim.h) | C++ | 12 | 0 | 9 | 21 |
| [include/arch/loongarch.h](/include/arch/loongarch.h) | C | 184 | 17 | 38 | 239 |
| [include/arch/ls7a.h](/include/arch/ls7a.h) | C | 18 | 1 | 8 | 27 |
| [include/boot/boot_param.h](/include/boot/boot_param.h) | C++ | 76 | 6 | 19 | 101 |
| [include/config/info.h](/include/config/info.h) | C | 12 | 0 | 3 | 15 |
| [include/drivers/kbd.h](/include/drivers/kbd.h) | C | 22 | 0 | 8 | 30 |
| [include/drivers/kbdmap.h](/include/drivers/kbdmap.h) | C | 254 | 15 | 14 | 283 |
| [include/fs/fs.h](/include/fs/fs.h) | C++ | 25 | 1 | 5 | 31 |
| [include/mm/bitmap.h](/include/mm/bitmap.h) | C | 10 | 0 | 6 | 16 |
| [include/mm/buddy.h](/include/mm/buddy.h) | C++ | 24 | 0 | 5 | 29 |
| [include/mm/kmalloc.h](/include/mm/kmalloc.h) | C++ | 9 | 0 | 3 | 12 |
| [include/mm/malloc.h](/include/mm/malloc.h) | C++ | 9 | 0 | 3 | 12 |
| [include/mm/mem_block.h](/include/mm/mem_block.h) | C | 6 | 0 | 0 | 6 |
| [include/mm/mm.h](/include/mm/mm.h) | C++ | 44 | 0 | 20 | 64 |
| [include/mm/mm_types.h](/include/mm/mm_types.h) | C++ | 11 | 0 | 5 | 16 |
| [include/mm/slab.h](/include/mm/slab.h) | C++ | 33 | 0 | 9 | 42 |
| [include/mm/sys_heap.h](/include/mm/sys_heap.h) | C++ | 11 | 0 | 3 | 14 |
| [include/serial/serial.h](/include/serial/serial.h) | C | 16 | 1 | 5 | 22 |
| [include/shell/impl.h](/include/shell/impl.h) | C++ | 7 | 0 | 2 | 9 |
| [include/shell/parser.h](/include/shell/parser.h) | C++ | 6 | 0 | 2 | 8 |
| [include/shell/shell.h](/include/shell/shell.h) | C | 29 | 0 | 11 | 40 |
| [include/sysio/buffer.h](/include/sysio/buffer.h) | C++ | 23 | 0 | 4 | 27 |
| [include/sysio/io.h](/include/sysio/io.h) | C++ | 10 | 0 | 3 | 13 |
| [include/temp/larchintrin.h](/include/temp/larchintrin.h) | C | 178 | 72 | 47 | 297 |
| [include/types.h](/include/types.h) | C | 20 | 1 | 8 | 29 |
| [include/utils/mem.h](/include/utils/mem.h) | C++ | 6 | 0 | 2 | 8 |
| [include/utils/string.h](/include/utils/string.h) | C++ | 9 | 0 | 2 | 11 |
| [kernel/Makefile](/kernel/Makefile) | Makefile | 31 | 0 | 10 | 41 |
| [kernel/app/Makefile](/kernel/app/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/app/tester.c](/kernel/app/tester.c) | C | 0 | 0 | 1 | 1 |
| [kernel/app/vim.c](/kernel/app/vim.c) | C | 198 | 2 | 13 | 213 |
| [kernel/boot/Makefile](/kernel/boot/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/boot/boot_param.c](/kernel/boot/boot_param.c) | C | 124 | 21 | 26 | 171 |
| [kernel/config/Makefile](/kernel/config/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/config/config.md](/kernel/config/config.md) | Markdown | 0 | 0 | 1 | 1 |
| [kernel/config/info.c](/kernel/config/info.c) | C | 25 | 0 | 9 | 34 |
| [kernel/drivers/Makefile](/kernel/drivers/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/drivers/driver.md](/kernel/drivers/driver.md) | Markdown | 1 | 0 | 1 | 2 |
| [kernel/drivers/kbd.c](/kernel/drivers/kbd.c) | C | 120 | 12 | 16 | 148 |
| [kernel/drivers/kbdmap.c](/kernel/drivers/kbdmap.c) | C | 146 | 6 | 7 | 159 |
| [kernel/entry.c](/kernel/entry.c) | C | 25 | 3 | 8 | 36 |
| [kernel/fs/Makefile](/kernel/fs/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/fs/fs.c](/kernel/fs/fs.c) | C | 253 | 3 | 16 | 272 |
| [kernel/kernel.md](/kernel/kernel.md) | Markdown | 2 | 0 | 2 | 4 |
| [kernel/mm/Makefile](/kernel/mm/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/mm/bitmap.c](/kernel/mm/bitmap.c) | C | 76 | 2 | 6 | 84 |
| [kernel/mm/buddy.c](/kernel/mm/buddy.c) | C | 122 | 2 | 10 | 134 |
| [kernel/mm/cache.c](/kernel/mm/cache.c) | C | 0 | 0 | 1 | 1 |
| [kernel/mm/kmalloc.c](/kernel/mm/kmalloc.c) | C | 31 | 0 | 5 | 36 |
| [kernel/mm/malloc.c](/kernel/mm/malloc.c) | C | 37 | 0 | 4 | 41 |
| [kernel/mm/mem_block.c](/kernel/mm/mem_block.c) | C | 1 | 7 | 4 | 12 |
| [kernel/mm/memory.md](/kernel/mm/memory.md) | Markdown | 68 | 0 | 56 | 124 |
| [kernel/mm/mm.c](/kernel/mm/mm.c) | C | 37 | 29 | 8 | 74 |
| [kernel/mm/page.c](/kernel/mm/page.c) | C | 0 | 24 | 1 | 25 |
| [kernel/mm/slab.c](/kernel/mm/slab.c) | C | 15 | 6 | 3 | 24 |
| [kernel/mm/sys_heap.c](/kernel/mm/sys_heap.c) | C | 58 | 0 | 8 | 66 |
| [kernel/mm/tlb.c](/kernel/mm/tlb.c) | C | 0 | 57 | 9 | 66 |
| [kernel/sched/Makefile](/kernel/sched/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/sched/sched.c](/kernel/sched/sched.c) | C | 2 | 4 | 2 | 8 |
| [kernel/sched/sched.md](/kernel/sched/sched.md) | Markdown | 2 | 0 | 2 | 4 |
| [kernel/shell/Makefile](/kernel/shell/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/shell/cmd.c](/kernel/shell/cmd.c) | C | 254 | 0 | 1 | 255 |
| [kernel/shell/impl.c](/kernel/shell/impl.c) | C | 61 | 0 | 5 | 66 |
| [kernel/shell/parser.c](/kernel/shell/parser.c) | C | 101 | 7 | 9 | 117 |
| [kernel/shell/shell.c](/kernel/shell/shell.c) | C | 57 | 2 | 6 | 65 |
| [kernel/shell/shell.md](/kernel/shell/shell.md) | Markdown | 0 | 0 | 1 | 1 |
| [kernel/sys/Makefile](/kernel/sys/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/sys/sys.c](/kernel/sys/sys.c) | C | 0 | 0 | 1 | 1 |
| [kernel/sys/syscall.md](/kernel/sys/syscall.md) | Markdown | 0 | 0 | 1 | 1 |
| [kernel/sysio/Makefile](/kernel/sysio/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/sysio/buffer.c](/kernel/sysio/buffer.c) | C | 74 | 1 | 12 | 87 |
| [kernel/sysio/io.c](/kernel/sysio/io.c) | C | 118 | 10 | 15 | 143 |
| [kernel/trap/Makefile](/kernel/trap/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/trap/extioi.c](/kernel/trap/extioi.c) | C | 19 | 6 | 7 | 32 |
| [kernel/trap/ls7a_intc.c](/kernel/trap/ls7a_intc.c) | C | 18 | 6 | 8 | 32 |
| [kernel/trap/pckbd.c](/kernel/trap/pckbd.c) | C | 31 | 10 | 10 | 51 |
| [kernel/trap/trap.c](/kernel/trap/trap.c) | C | 162 | 18 | 23 | 203 |
| [kernel/trap/trap.md](/kernel/trap/trap.md) | Markdown | 3 | 0 | 2 | 5 |
| [kernel/utils/Makefile](/kernel/utils/Makefile) | Makefile | 18 | 0 | 6 | 24 |
| [kernel/utils/mem.c](/kernel/utils/mem.c) | C | 34 | 0 | 3 | 37 |
| [kernel/utils/string.c](/kernel/utils/string.c) | C | 85 | 10 | 6 | 101 |
| [notes.md](/notes.md) | Markdown | 0 | 0 | 2 | 2 |
| [run_loongarch.sh](/run_loongarch.sh) | Shell Script | 61 | 13 | 6 | 80 |
| [start.sh](/start.sh) | Shell Script | 4 | 0 | 1 | 5 |
| [tools/mmp.csv](/tools/mmp.csv) | CSV | 16 | 0 | 1 | 17 |
| [tools/vis_mmap.py](/tools/vis_mmap.py) | Python | 112 | 0 | 16 | 128 |

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)