// static void setup_pw(void)
// {
// 	unsigned long pgd_i, pgd_w;
// #ifndef __PAGETABLE_PMD_FOLDED
// 	unsigned long pmd_i, pmd_w;
// #endif
// 	unsigned long pte_i, pte_w;

// 	pgd_i = PGDIR_SHIFT;  /* 1st level PGD */
// #ifndef __PAGETABLE_PMD_FOLDED
// 	pgd_w = PGDIR_SHIFT - PMD_SHIFT + PGD_ORDER;
// 	pmd_i = PMD_SHIFT;    /* 2nd level PMD */
// 	pmd_w = PMD_SHIFT - PAGE_SHIFT;
// #else
// 	pgd_w = PGDIR_SHIFT - PAGE_SHIFT + PGD_ORDER;
// #endif
// 	pte_i  = PAGE_SHIFT;    /* 3rd level PTE */
// 	pte_w  = PAGE_SHIFT - 3;

// #ifndef __PAGETABLE_PMD_FOLDED
// 	csr_writeq(pte_i | pte_w << 5 | pmd_i << 10 | pmd_w << 15, LOONGARCH_CSR_PWCTL0);
// 	csr_writeq(pgd_i | pgd_w << 6, LOONGARCH_CSR_PWCTL1);
// #else
// 	csr_writeq(pte_i | pte_w << 5, LOONGARCH_CSR_PWCTL0);
// 	csr_writeq(pgd_i | pgd_w << 6, LOONGARCH_CSR_PWCTL1);
// #endif
// 	csr_writeq((long)swapper_pg_dir, LOONGARCH_CSR_PGDH);
// 	csr_writeq((long)invalid_pg_dir, LOONGARCH_CSR_PGDL);
// 	csr_writeq((long)smp_processor_id(), LOONGARCH_CSR_TMID);
// }

// void setup_tlb_handler(void)
// {
// 	static int run_once = 0;

// 	setup_pw();
// 	output_pgtable_bits_defines();

// 	/* The tlb handlers are generated only once */
// 	if (!run_once) {
// 		memcpy((void *)tlbrentry, handle_tlb_refill, 0x80);
// 		local_flush_icache_range(tlbrentry, tlbrentry + 0x80);
// 		set_handler(EXCCODE_TLBI * VECSIZE, handle_tlb_load, VECSIZE);
// 		set_handler(EXCCODE_TLBL * VECSIZE, handle_tlb_load, VECSIZE);
// 		set_handler(EXCCODE_TLBS * VECSIZE, handle_tlb_store, VECSIZE);
// 		set_handler(EXCCODE_TLBM * VECSIZE, handle_tlb_modify, VECSIZE);
// 		set_handler(EXCCODE_TLBNR * VECSIZE, handle_tlb_protect, VECSIZE);
// 		set_handler(EXCCODE_TLBNX * VECSIZE, handle_tlb_protect, VECSIZE);
// 		set_handler(EXCCODE_TLBPE * VECSIZE, handle_tlb_protect, VECSIZE);
// 		run_once++;
// 	}
// }

// void tlb_init(void)
// {
// 	write_csr_pagesize(PS_DEFAULT_SIZE);
// 	write_csr_stlbpgsize(PS_DEFAULT_SIZE);
// 	write_csr_tlbrefill_pagesize(PS_DEFAULT_SIZE);

// 	if (read_csr_pagesize() != PS_DEFAULT_SIZE)
// 		panic("MMU doesn't support PAGE_SIZE=0x%lx", PAGE_SIZE);

// 	setup_tlb_handler();
// 	local_flush_tlb_all();
// }
