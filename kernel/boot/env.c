#include "util.h"
#include "boot_param.h"
#define MAX_PACKAGES 16
#define EPERM 1
#define NULL ((void *)0)
#define EFI_BOOT		0 //efi.h
#define NR_CPUS CONFIG_NR_CPUS
#define CONFIG_NR_CPUS	1 //threads.h

struct BootParamsInterface *efi_bp;
struct loongsonlist_mem_map *loongson_mem_map;
struct loongsonlist_vbios *pvbios;
struct loongson_system_configuration loongson_sysconf;
EXPORT_SYMBOL(loongson_sysconf);

u64 loongson_chipcfg[MAX_PACKAGES];
u64 loongson_chiptemp[MAX_PACKAGES];
u64 loongson_freqctrl[MAX_PACKAGES];
unsigned long long smp_group[MAX_PACKAGES];

static void register_addrs_set(u64 *registers, const u64 addr, int num)
{
	u64 i;

	for (i = 0; i < num; i++) {
		*registers = (i << 44) | addr;
		registers++;
	}
}

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
	if (ext_listhdr_checksum((u8 *)loongson_mem_map, head->length)) {
		pr_warn("mem checksum error\n");
		return -EPERM;
	}

	return 0;
}

static int parse_vbios(struct _extention_list_hdr *head)
{
	pvbios = (struct loongsonlist_vbios *)head;

	if (ext_listhdr_checksum((u8 *)pvbios, head->length)) {
		pr_warn("vbios_addr checksum error\n");
		return -EPERM;
	}

	loongson_sysconf.vgabios_addr = TO_CAC((unsigned long)pvbios->vbios_addr);

	return 0;
}

static int parse_screeninfo(struct _extention_list_hdr *head)
{
	struct loongsonlist_screeninfo *pscreeninfo;

	pscreeninfo = (struct loongsonlist_screeninfo *)head;
	if (ext_listhdr_checksum((u8 *)pscreeninfo, head->length)) {
		pr_warn("screeninfo_addr checksum error\n");
		return -EPERM;
	}

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
			if (parse_mem(fhead) !=0) {
				pr_warn("parse mem failed\n");
				return -EPERM;
			}
		} else if (memcmp(&(fhead->Signature), LOONGSON_VBIOS_LINKLIST, 5) == 0) {
			if (parse_vbios(fhead) != 0) {
				pr_warn("parse vbios failed\n");
				return -EPERM;
			}
		} else if (memcmp(&(fhead->Signature), LOONGSON_SCREENINFO_LINKLIST, 5) == 0) {
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

static void parse_bpi_flags(void)
{
	// if (efi_bp->Flags & BPI_FLAGS_UEFI_SUPPORTED)
	// 	set_bit(EFI_BOOT, &efi.flags);
	// else
	// 	clear_bit(EFI_BOOT, &efi.flags);
}

static int get_bpi_version(void *signature)
{
	char data[8];
	int r, version = 0;

	memset(data, 0, 8);
	memcpy(data, signature + 4, 4);
	r = kstrtoint(data, 10, &version);

	if (r < 0 || version < BPI_VERSION_V1)
		panic("Fatal error, invalid BPI version: %d\n", version);

	if (version >= BPI_VERSION_V2)
		parse_bpi_flags();

	return version;
}

void fw_init_environ(void)
{
	// struct _extention_list_hdr *fhead;

	// efi_bp = (struct BootParamsInterface *)_fw_envp;
	// loongson_sysconf.bpi_ver = get_bpi_version(&efi_bp->Signature);

	// register_addrs_set(smp_group, TO_UNCAC(0x1fe01000), 16);
	// register_addrs_set(loongson_chipcfg, TO_UNCAC(0x1fe00180), 16);
	// register_addrs_set(loongson_chiptemp, TO_UNCAC(0x1fe0019c), 16);
	// register_addrs_set(loongson_freqctrl, TO_UNCAC(0x1fe001d0), 16);
	// fhead = efi_bp->ExtList ? (struct _extention_list_hdr *)TO_CAC((unsigned long)efi_bp->ExtList) : NULL;
	// if (list_find(fhead))
	// 	pr_warn("Scan bootparam failed\n");
}

static int init_cpu_fullname(void)
{
	int cpu;

	// if (loongson_sysconf.cpuname && !strncmp(loongson_sysconf.cpuname, "Loongson", 8)) {
	// 	for (cpu = 0; cpu < NR_CPUS; cpu++)
	// 		__cpu_full_name[cpu] = loongson_sysconf.cpuname;
	// }
	return 0;
}
arch_initcall(init_cpu_fullname);
