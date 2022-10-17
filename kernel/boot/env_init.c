#include "util.h"
#include "satio/printf.h"
#include "boot/env_init.h"
#define MAX_PACKAGES 16
#define EPERM 1
#define NULL ((void *)0)
#define EFI_BOOT		0 //efi.h
#define NR_CPUS CONFIG_NR_CPUS
#define CONFIG_NR_CPUS	1 //threads.h

//loongarch.h
#define _CONST64_(x) x ## LL //addrspace.h

#define CSR_DMW1_VSEG		_CONST64_(0x9000)
#define CSR_DMW1_BASE		(CSR_DMW1_VSEG << DMW_PABITS)
#ifndef CAC_BASE
#define CAC_BASE		CSR_DMW1_BASE
#endif

#ifndef UNCAC_BASE
#define UNCAC_BASE		CSR_DMW0_BASE
#endif
//addrspace.h
#define DMW_PABITS	48
#define TO_PHYS_MASK	((1ULL << DMW_PABITS) - 1)
#define TO_PHYS(x)		(	      ((x) & TO_PHYS_MASK))
#define TO_CAC(x)		(CAC_BASE   | ((x) & TO_PHYS_MASK))
#define TO_UNCAC(x)		(UNCAC_BASE | ((x) & TO_PHYS_MASK))
//在直接使用地址时也许应该注意类型转换

#define pr_warn(text) printf(text)

struct BootParamsInterface *efi_bp;
struct loongsonlist_mem_map *loongson_mem_map;
struct loongsonlist_vbios *pvbios;
struct loongson_system_configuration loongson_sysconf;
// extern struct loongson_board_info b_info;
// extern struct BootParamsInterface *efi_bp;
// extern struct loongsonlist_mem_map *loongson_mem_map;
// extern struct loongson_system_configuration loongson_sysconf;

static u8 ext_listhdr_checksum(u8 *buffer, u32 length)
{
	u8 sum = 0;
	u8 *end = buffer + length;

	while (buffer < end) {
		sum = (u8)(sum + *(buffer++));
	}

	return (sum);
}

static int parse_mem(struct _extention_list_hdr *head)
{
	loongson_mem_map = (struct loongsonlist_mem_map *)head;
	
	printf("map_cnt:%d\n",loongson_mem_map->map_count);

	printf("\nmem:\n");
	for (int i=0;i<100;i++){
		printf("%x ",*((char*)loongson_mem_map+i));
	}
	printf("\nmemmap:\n");
	for (int i=0;i<100;i++){
		printf("%x ",*((char*)loongson_mem_map->map+i));
	}
	if (ext_listhdr_checksum((u8 *)loongson_mem_map, head->length)) {
		pr_warn("mem checksum error\n");
		return -EPERM;
	}

	return 0;
}

static int parse_vbios(struct _extention_list_hdr *head)
{
	// pvbios = (struct loongsonlist_vbios *)head;

	// if (ext_listhdr_checksum((u8 *)pvbios, head->length)) {
	// 	pr_warn("vbios_addr checksum error\n");
	// 	return -EPERM;
	// }

	// loongson_sysconf.vgabios_addr = TO_CAC((unsigned long)pvbios->vbios_addr);

	return 0;
}

static int parse_screeninfo(struct _extention_list_hdr *head)
{
	// struct loongsonlist_screeninfo *pscreeninfo;

	// pscreeninfo = (struct loongsonlist_screeninfo *)head;
	// if (ext_listhdr_checksum((u8 *)pscreeninfo, head->length)) {
	// 	pr_warn("screeninfo_addr checksum error\n");
	// 	return -EPERM;
	// }

	// memcpy(&screen_info, &pscreeninfo->si, sizeof(screen_info));

	return 0;
}

static int list_find(struct _extention_list_hdr *head)
{
	struct _extention_list_hdr *fhead = head;

	if (fhead == NULL) {
		pr_warn("the link is empty!\n");
		return -1;
	}

	while(fhead != NULL) {
		if (memcmp(&(fhead->Signature), LOONGSON_MEM_LINKLIST, 3) == 0) {
			printf("Parsing Memory Map...\n");
			if (parse_mem(fhead) !=0) {
				pr_warn("parse mem failed\n");
				return -EPERM;
			}
		} else if (memcmp(&(fhead->Signature), LOONGSON_VBIOS_LINKLIST, 5) == 0) {
			printf("Parsing VBIOS...\n");
			if (parse_vbios(fhead) != 0) {
				pr_warn("parse vbios failed\n");
				return -EPERM;
			}
		} else if (memcmp(&(fhead->Signature), LOONGSON_SCREENINFO_LINKLIST, 5) == 0) {
			printf("Parsing Screen Info...\n");
			if (parse_screeninfo(fhead) != 0) {
				pr_warn("parse screeninfo failed\n");
				return -EPERM;
			}
		}
		if (fhead->next)
			fhead = (struct _extention_list_hdr *)TO_CAC((unsigned long)fhead->next);
		else
			fhead = fhead->next;
	}

	return 0;
}

void env_init(struct BootParamsInterface *efi_bp){
    struct _extention_list_hdr *fhead;
	fhead = efi_bp->ExtList ? (struct _extention_list_hdr *)TO_CAC((unsigned long)efi_bp->ExtList) : NULL;
	if (list_find(fhead))
		pr_warn("Scan bootparam failed\n");
}