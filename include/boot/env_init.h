#include "boot.h"
extern struct BootParamsInterface *efi_bp;
extern struct loongsonlist_mem_map *loongson_mem_map;
extern struct loongsonlist_vbios *pvbios;
extern struct loongson_system_configuration loongson_sysconf;

void env_init(struct BootParamsInterface *efi_bp);