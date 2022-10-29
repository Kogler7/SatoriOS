#ifndef __mini_kernel_loongarch_h_
#define __mini_kernel_loongarch_h_

#include <gcc/larchintrin.h>

/* Basic CSR registers */
#define LOONGARCH_CSR_CRMD		0x0	/* Current mode info */
#define  CSR_CRMD_WE_SHIFT		9
#define  CSR_CRMD_WE			(_ULCAST_(0x1) << CSR_CRMD_WE_SHIFT)
#define  CSR_CRMD_DACM_SHIFT		7
#define  CSR_CRMD_DACM_WIDTH		2
#define  CSR_CRMD_DACM			(_ULCAST_(0x3) << CSR_CRMD_DACM_SHIFT)
#define  CSR_CRMD_DACF_SHIFT		5
#define  CSR_CRMD_DACF_WIDTH		2
#define  CSR_CRMD_DACF			(_ULCAST_(0x3) << CSR_CRMD_DACF_SHIFT)
#define  CSR_CRMD_PG_SHIFT		4
#define  CSR_CRMD_PG			(_ULCAST_(0x1) << CSR_CRMD_PG_SHIFT)
#define  CSR_CRMD_DA_SHIFT		3
#define  CSR_CRMD_DA			(_ULCAST_(0x1) << CSR_CRMD_DA_SHIFT)
#define  CSR_CRMD_IE_SHIFT		2
#define  CSR_CRMD_IE			(_ULCAST_(0x1) << CSR_CRMD_IE_SHIFT)
#define  CSR_CRMD_PLV_SHIFT		0
#define  CSR_CRMD_PLV_WIDTH		2
#define  CSR_CRMD_PLV			(_ULCAST_(0x3) << CSR_CRMD_PLV_SHIFT)

#define PLV_KERN			0
#define PLV_USER			3
#define PLV_MASK			0x3

#define LOONGARCH_CSR_PRMD		0x1	/* Prev-exception mode info */
#define  CSR_PRMD_PWE_SHIFT		3
#define  CSR_PRMD_PWE			(_ULCAST_(0x1) << CSR_PRMD_PWE_SHIFT)
#define  CSR_PRMD_PIE_SHIFT		2
#define  CSR_PRMD_PIE			(_ULCAST_(0x1) << CSR_PRMD_PIE_SHIFT)
#define  CSR_PRMD_PPLV_SHIFT		0
#define  CSR_PRMD_PPLV_WIDTH		2
#define  CSR_PRMD_PPLV			(_ULCAST_(0x3) << CSR_PRMD_PPLV_SHIFT)

#define LOONGARCH_CSR_EUEN		0x2	/* Extended unit enable */
#define  CSR_EUEN_LBTEN_SHIFT		3
#define  CSR_EUEN_LBTEN			(_ULCAST_(0x1) << CSR_EUEN_LBTEN_SHIFT)
#define  CSR_EUEN_LASXEN_SHIFT		2
#define  CSR_EUEN_LASXEN		(_ULCAST_(0x1) << CSR_EUEN_LASXEN_SHIFT)
#define  CSR_EUEN_LSXEN_SHIFT		1
#define  CSR_EUEN_LSXEN			(_ULCAST_(0x1) << CSR_EUEN_LSXEN_SHIFT)
#define  CSR_EUEN_FPEN_SHIFT		0
#define  CSR_EUEN_FPEN			(_ULCAST_(0x1) << CSR_EUEN_FPEN_SHIFT)

#define LOONGARCH_CSR_MISC		0x3	/* Misc config */

#define LOONGARCH_CSR_ECFG		0x4	/* Exception config */
#define  CSR_ECFG_VS_SHIFT		16
#define  CSR_ECFG_VS_WIDTH		3
#define  CSR_ECFG_VS			(_ULCAST_(0x7) << CSR_ECFG_VS_SHIFT)
#define  CSR_ECFG_IM_SHIFT		0
#define  CSR_ECFG_IM_WIDTH		13
#define  CSR_ECFG_IM			(_ULCAST_(0x1fff) << CSR_ECFG_IM_SHIFT)

#define LOONGARCH_CSR_ESTAT		0x5	/* Exception status */
#define  CSR_ESTAT_ESUBCODE_SHIFT	22
#define  CSR_ESTAT_ESUBCODE_WIDTH	9
#define  CSR_ESTAT_ESUBCODE		(_ULCAST_(0x1ff) << CSR_ESTAT_ESUBCODE_SHIFT)
#define  CSR_ESTAT_EXC_SHIFT		16
#define  CSR_ESTAT_EXC_WIDTH		6
#define  CSR_ESTAT_EXC			(_ULCAST_(0x3f) << CSR_ESTAT_EXC_SHIFT)
#define  CSR_ESTAT_IS_SHIFT		0
#define  CSR_ESTAT_IS_WIDTH		15
#define  CSR_ESTAT_IS			(_ULCAST_(0x7fff) << CSR_ESTAT_IS_SHIFT)

#define LOONGARCH_CSR_ERA		0x6	/* ERA */

#define LOONGARCH_CSR_BADV		0x7	/* Bad virtual address */

#define LOONGARCH_CSR_BADI		0x8	/* Bad instruction */

#define LOONGARCH_CSR_EENTRY		0xc	/* Exception entry */

/* TLB related CSR registers */
#define LOONGARCH_CSR_TLBIDX		0x10	/* TLB Index, EHINV, PageSize, NP */
#define  CSR_TLBIDX_EHINV_SHIFT		31
#define  CSR_TLBIDX_EHINV		(_ULCAST_(1) << CSR_TLBIDX_EHINV_SHIFT)
#define  CSR_TLBIDX_PS_SHIFT		24
#define  CSR_TLBIDX_PS_WIDTH		6
#define  CSR_TLBIDX_PS			(_ULCAST_(0x3f) << CSR_TLBIDX_PS_SHIFT)
#define  CSR_TLBIDX_IDX_SHIFT		0
#define  CSR_TLBIDX_IDX_WIDTH		12
#define  CSR_TLBIDX_IDX			(_ULCAST_(0xfff) << CSR_TLBIDX_IDX_SHIFT)
#define  CSR_TLBIDX_SIZEM		0x3f000000
#define  CSR_TLBIDX_SIZE		CSR_TLBIDX_PS_SHIFT
#define  CSR_TLBIDX_IDXM		0xfff
#define  CSR_INVALID_ENTRY(e)		(CSR_TLBIDX_EHINV | e)

#define LOONGARCH_CSR_TLBEHI		0x11	/* TLB EntryHi */

#define LOONGARCH_CSR_TLBELO0		0x12	/* TLB EntryLo0 */
#define  CSR_TLBLO0_RPLV_SHIFT		63
#define  CSR_TLBLO0_RPLV		(_ULCAST_(0x1) << CSR_TLBLO0_RPLV_SHIFT)
#define  CSR_TLBLO0_NX_SHIFT		62
#define  CSR_TLBLO0_NX			(_ULCAST_(0x1) << CSR_TLBLO0_NX_SHIFT)
#define  CSR_TLBLO0_NR_SHIFT		61
#define  CSR_TLBLO0_NR			(_ULCAST_(0x1) << CSR_TLBLO0_NR_SHIFT)
#define  CSR_TLBLO0_PFN_SHIFT		12
#define  CSR_TLBLO0_PFN_WIDTH		36
#define  CSR_TLBLO0_PFN			(_ULCAST_(0xfffffffff) << CSR_TLBLO0_PFN_SHIFT)
#define  CSR_TLBLO0_GLOBAL_SHIFT	6
#define  CSR_TLBLO0_GLOBAL		(_ULCAST_(0x1) << CSR_TLBLO0_GLOBAL_SHIFT)
#define  CSR_TLBLO0_CCA_SHIFT		4
#define  CSR_TLBLO0_CCA_WIDTH		2
#define  CSR_TLBLO0_CCA			(_ULCAST_(0x3) << CSR_TLBLO0_CCA_SHIFT)
#define  CSR_TLBLO0_PLV_SHIFT		2
#define  CSR_TLBLO0_PLV_WIDTH		2
#define  CSR_TLBLO0_PLV			(_ULCAST_(0x3) << CSR_TLBLO0_PLV_SHIFT)
#define  CSR_TLBLO0_WE_SHIFT		1
#define  CSR_TLBLO0_WE			(_ULCAST_(0x1) << CSR_TLBLO0_WE_SHIFT)
#define  CSR_TLBLO0_V_SHIFT		0
#define  CSR_TLBLO0_V			(_ULCAST_(0x1) << CSR_TLBLO0_V_SHIFT)

#define LOONGARCH_CSR_TLBELO1		0x13	/* TLB EntryLo1 */
#define  CSR_TLBLO1_RPLV_SHIFT		63
#define  CSR_TLBLO1_RPLV		(_ULCAST_(0x1) << CSR_TLBLO1_RPLV_SHIFT)
#define  CSR_TLBLO1_NX_SHIFT		62
#define  CSR_TLBLO1_NX			(_ULCAST_(0x1) << CSR_TLBLO1_NX_SHIFT)
#define  CSR_TLBLO1_NR_SHIFT		61
#define  CSR_TLBLO1_NR			(_ULCAST_(0x1) << CSR_TLBLO1_NR_SHIFT)
#define  CSR_TLBLO1_PFN_SHIFT		12
#define  CSR_TLBLO1_PFN_WIDTH		36
#define  CSR_TLBLO1_PFN			(_ULCAST_(0xfffffffff) << CSR_TLBLO1_PFN_SHIFT)
#define  CSR_TLBLO1_GLOBAL_SHIFT	6
#define  CSR_TLBLO1_GLOBAL		(_ULCAST_(0x1) << CSR_TLBLO1_GLOBAL_SHIFT)
#define  CSR_TLBLO1_CCA_SHIFT		4
#define  CSR_TLBLO1_CCA_WIDTH		2
#define  CSR_TLBLO1_CCA			(_ULCAST_(0x3) << CSR_TLBLO1_CCA_SHIFT)
#define  CSR_TLBLO1_PLV_SHIFT		2
#define  CSR_TLBLO1_PLV_WIDTH		2
#define  CSR_TLBLO1_PLV			(_ULCAST_(0x3) << CSR_TLBLO1_PLV_SHIFT)
#define  CSR_TLBLO1_WE_SHIFT		1
#define  CSR_TLBLO1_WE			(_ULCAST_(0x1) << CSR_TLBLO1_WE_SHIFT)
#define  CSR_TLBLO1_V_SHIFT		0
#define  CSR_TLBLO1_V			(_ULCAST_(0x1) << CSR_TLBLO1_V_SHIFT)

#define LOONGARCH_CSR_GTLBC		0x15	/* Guest TLB control */
#define  CSR_GTLBC_RID_SHIFT		16
#define  CSR_GTLBC_RID_WIDTH		8
#define  CSR_GTLBC_RID			(_ULCAST_(0xff) << CSR_GTLBC_RID_SHIFT)
#define  CSR_GTLBC_TOTI_SHIFT		13
#define  CSR_GTLBC_TOTI			(_ULCAST_(0x1) << CSR_GTLBC_TOTI_SHIFT)
#define  CSR_GTLBC_USERID_SHIFT		12
#define  CSR_GTLBC_USERID		(_ULCAST_(0x1) << CSR_GTLBC_USERID_SHIFT)
#define  CSR_GTLBC_GMTLBSZ_SHIFT	0
#define  CSR_GTLBC_GMTLBSZ_WIDTH	6
#define  CSR_GTLBC_GMTLBSZ		(_ULCAST_(0x3f) << CSR_GTLBC_GMTLBSZ_SHIFT)

#define LOONGARCH_CSR_TRGP		0x16	/* TLBR read guest info */
#define  CSR_TRGP_RID_SHIFT		16
#define  CSR_TRGP_RID_WIDTH		8
#define  CSR_TRGP_RID			(_ULCAST_(0xff) << CSR_TRGP_RID_SHIFT)
#define  CSR_TRGP_GTLB_SHIFT		0
#define  CSR_TRGP_GTLB			(1 << CSR_TRGP_GTLB_SHIFT)

#define LOONGARCH_CSR_ASID		0x18	/* ASID */
#define  CSR_ASID_BIT_SHIFT		16	/* ASIDBits */
#define  CSR_ASID_BIT_WIDTH		8
#define  CSR_ASID_BIT			(_ULCAST_(0xff) << CSR_ASID_BIT_SHIFT)
#define  CSR_ASID_ASID_SHIFT		0
#define  CSR_ASID_ASID_WIDTH		10
#define  CSR_ASID_ASID			(_ULCAST_(0x3ff) << CSR_ASID_ASID_SHIFT)

#define LOONGARCH_CSR_PGDL		0x19	/* Page table base address when VA[47] = 0 */

#define LOONGARCH_CSR_PGDH		0x1a	/* Page table base address when VA[47] = 1 */

#define LOONGARCH_CSR_PGD		0x1b	/* Page table base */

#define LOONGARCH_CSR_PWCTL0		0x1c	/* PWCtl0 */
#define  CSR_PWCTL0_PTEW_SHIFT		30
#define  CSR_PWCTL0_PTEW_WIDTH		2
#define  CSR_PWCTL0_PTEW		(_ULCAST_(0x3) << CSR_PWCTL0_PTEW_SHIFT)
#define  CSR_PWCTL0_DIR1WIDTH_SHIFT	25
#define  CSR_PWCTL0_DIR1WIDTH_WIDTH	5
#define  CSR_PWCTL0_DIR1WIDTH		(_ULCAST_(0x1f) << CSR_PWCTL0_DIR1WIDTH_SHIFT)
#define  CSR_PWCTL0_DIR1BASE_SHIFT	20
#define  CSR_PWCTL0_DIR1BASE_WIDTH	5
#define  CSR_PWCTL0_DIR1BASE		(_ULCAST_(0x1f) << CSR_PWCTL0_DIR1BASE_SHIFT)
#define  CSR_PWCTL0_DIR0WIDTH_SHIFT	15
#define  CSR_PWCTL0_DIR0WIDTH_WIDTH	5
#define  CSR_PWCTL0_DIR0WIDTH		(_ULCAST_(0x1f) << CSR_PWCTL0_DIR0WIDTH_SHIFT)
#define  CSR_PWCTL0_DIR0BASE_SHIFT	10
#define  CSR_PWCTL0_DIR0BASE_WIDTH	5
#define  CSR_PWCTL0_DIR0BASE		(_ULCAST_(0x1f) << CSR_PWCTL0_DIR0BASE_SHIFT)
#define  CSR_PWCTL0_PTWIDTH_SHIFT	5
#define  CSR_PWCTL0_PTWIDTH_WIDTH	5
#define  CSR_PWCTL0_PTWIDTH		(_ULCAST_(0x1f) << CSR_PWCTL0_PTWIDTH_SHIFT)
#define  CSR_PWCTL0_PTBASE_SHIFT	0
#define  CSR_PWCTL0_PTBASE_WIDTH	5
#define  CSR_PWCTL0_PTBASE		(_ULCAST_(0x1f) << CSR_PWCTL0_PTBASE_SHIFT)

#define LOONGARCH_CSR_PWCTL1		0x1d	/* PWCtl1 */
#define  CSR_PWCTL1_DIR3WIDTH_SHIFT	18
#define  CSR_PWCTL1_DIR3WIDTH_WIDTH	5
#define  CSR_PWCTL1_DIR3WIDTH		(_ULCAST_(0x1f) << CSR_PWCTL1_DIR3WIDTH_SHIFT)
#define  CSR_PWCTL1_DIR3BASE_SHIFT	12
#define  CSR_PWCTL1_DIR3BASE_WIDTH	5
#define  CSR_PWCTL1_DIR3BASE		(_ULCAST_(0x1f) << CSR_PWCTL0_DIR3BASE_SHIFT)
#define  CSR_PWCTL1_DIR2WIDTH_SHIFT	6
#define  CSR_PWCTL1_DIR2WIDTH_WIDTH	5
#define  CSR_PWCTL1_DIR2WIDTH		(_ULCAST_(0x1f) << CSR_PWCTL1_DIR2WIDTH_SHIFT)
#define  CSR_PWCTL1_DIR2BASE_SHIFT	0
#define  CSR_PWCTL1_DIR2BASE_WIDTH	5
#define  CSR_PWCTL1_DIR2BASE		(_ULCAST_(0x1f) << CSR_PWCTL0_DIR2BASE_SHIFT)

#define LOONGARCH_CSR_STLBPGSIZE	0x1e
#define  CSR_STLBPGSIZE_PS_WIDTH	6
#define  CSR_STLBPGSIZE_PS		(_ULCAST_(0x3f))

#define LOONGARCH_CSR_RVACFG		0x1f
#define  CSR_RVACFG_RDVA_WIDTH		4
#define  CSR_RVACFG_RDVA		(_ULCAST_(0xf))

/* interrupt enable bit */
#define  CSR_CRMD_IE_SHIFT		    2
#define  CSR_CRMD_IE	            ( 0x1 << CSR_CRMD_IE_SHIFT )

/* extioi registers */
#define LOONGARCH_IOCSR_EXTIOI_EN_BASE          0x1600
#define LOONGARCH_IOCSR_EXTIOI_ISR_BASE         0x1800
#define LOONGARCH_IOCSR_EXTIOI_MAP_BASE         0x14c0
#define LOONGARCH_IOCSR_EXTIOI_ROUTE_BASE       0x1c00
#define LOONGARCH_IOCSR_EXRIOI_NODETYPE_BASE    0x14a0

static inline unsigned int r_csr_crmd()
{
  unsigned int x;
  __asm volatile("csrrd %0, 0x0" : "=r" (x) );
  return x;
}

static inline void w_csr_crmd(unsigned int x)
{
  __asm volatile("csrwr %0, 0x0" : : "r" (x));
}

#define PRMD_PPLV (3U << 0)  // Previous Privilege
#define PRMD_PIE  (1U << 2)  // Previous Int_enable

static inline unsigned int r_csr_prmd()
{
  unsigned int x;
  __asm volatile("csrrd %0, 0x1" : "=r" (x) );
  return x;
}

static inline void w_csr_prmd(unsigned int x)
{
  __asm volatile("csrwr %0, 0x1" : : "r" (x));
}

static inline unsigned long r_csr_era()
{
  unsigned long x;
  __asm volatile("csrrd %0, 0x6" : "=r" (x) );
  return x;
}

static inline void w_csr_era(unsigned long x)
{
  __asm volatile("csrwr %0, 0x6" : : "r" (x));
}

/* ESTAT bit 16..21 is ecode field */
#define CSR_ESTAT_ECODE  (0x3fU << 16)

static inline unsigned int r_csr_estat()
{
  unsigned int x;
  __asm volatile("csrrd %0, 0x5" : "=r" (x) );
  return x;
}

/* vector interrupt scale, when bit 16..18 == 0
 * all interrupt share the same entry
 */
#define CSR_ECFG_VS_SHIFT  16 
/* 8 external hardware interrupt */
#define HWI_VEC  0x3fcU
/* timer interrupt bit */
#define CSR_ECFG_LIE_TI_SHIFT  11
#define TI_VEC  (0x1 << CSR_ECFG_LIE_TI_SHIFT)

static inline unsigned int r_csr_ecfg()
{
  unsigned int x;
  __asm volatile("csrrd %0, 0x4" : "=r" (x) );
  return x;
}

static inline void w_csr_ecfg(unsigned int x)
{
  __asm volatile("csrwr %0, 0x4" : : "r" (x) );
}

/* timer interrupt clear */
#define CSR_TICLR_CLR  (0x1 << 0)

static inline unsigned int r_csr_ticlr()
{
  unsigned int x;
  __asm volatile("csrrd %0, 0x44" : "=r" (x) );
  return x;
}

static inline void w_csr_ticlr(unsigned int x)
{
  __asm volatile("csrwr %0, 0x44" : : "r" (x) );
}

static inline unsigned long r_csr_eentry()
{
  unsigned long x;
  __asm volatile("csrrd %0, 0xc" : "=r" (x) );
  return x;
}

static inline unsigned long r_csr_tlbrelo0()
{
  unsigned long x;
  __asm volatile("csrrd %0, 0x8c" : "=r" (x) );
  return x;
}

static inline unsigned long r_csr_tlbrelo1()
{
  unsigned long x;
  __asm volatile("csrrd %0, 0x8d" : "=r" (x) );
  return x;
}

static inline void w_csr_eentry(unsigned long x)
{
  __asm volatile("csrwr %0, 0xc" : : "r" (x) );
}

static inline void w_csr_tlbrentry(unsigned long x)
{
  __asm volatile("csrwr %0, 0x88" : : "r" (x) );
}

static inline void w_csr_merrentry(unsigned long x)
{
  __asm volatile("csrwr %0, 0x93" : : "r" (x) );
}

static inline void w_csr_stlbps(unsigned int x)
{
  __asm volatile("csrwr %0, 0x1e" : : "r" (x) );
}

static inline void w_csr_asid(unsigned int x)
{
  __asm volatile("csrwr %0, 0x18" : : "r" (x) );
}

/* timer enable */
#define CSR_TCFG_EN            (1U << 0)
/* timer perioid */
#define CSR_TCFG_PER           (1U << 1)

static inline void w_csr_tcfg(unsigned long x)
{
  __asm volatile("csrwr %0, 0x41" : : "r" (x) );
}

/* IOCSR */
static inline unsigned int iocsr_readl(unsigned int reg)
{
	return __iocsrrd_w(reg);
}

static inline unsigned long iocsr_readq(unsigned int reg)
{
	return __iocsrrd_d(reg);
}

static inline void iocsr_writel(unsigned int val, unsigned int reg)
{
	__iocsrwr_w(val, reg);
}

static inline void iocsr_writeq(unsigned long val, unsigned int reg)
{
	__iocsrwr_d(val, reg);
}

static inline int intr_get()
{
  unsigned int x = r_csr_crmd();
  return (x & CSR_CRMD_IE) != 0;
}

// enable device interrupts
static inline void intr_on()
{
  w_csr_crmd(r_csr_crmd() | CSR_CRMD_IE);
}

// disable device interrupts
static inline void intr_off()
{
  w_csr_crmd(r_csr_crmd() & ~CSR_CRMD_IE);
}

#endif
