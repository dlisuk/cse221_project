#define ARMV6_PMCR_ENABLE               (1 << 0)
#define ARMV6_PMCR_CTR01_RESET          (1 << 1)
#define ARMV6_PMCR_CCOUNT_RESET         (1 << 2)
#define ARMV6_PMCR_CCOUNT_DIV           (1 << 3)
#define ARMV6_PMCR_COUNT0_IEN           (1 << 4)
#define ARMV6_PMCR_COUNT1_IEN           (1 << 5)
#define ARMV6_PMCR_CCOUNT_IEN           (1 << 6)
#define ARMV6_PMCR_COUNT0_OVERFLOW      (1 << 8)
#define ARMV6_PMCR_COUNT1_OVERFLOW      (1 << 9)
#define ARMV6_PMCR_CCOUNT_OVERFLOW      (1 << 10)
#define ARMV6_PMCR_EVT_COUNT0_SHIFT     20
#define ARMV6_PMCR_EVT_COUNT0_MASK      (0xFF << ARMV6_PMCR_EVT_COUNT0_SHIFT)
#define ARMV6_PMCR_EVT_COUNT1_SHIFT     12
#define ARMV6_PMCR_EVT_COUNT1_MASK      (0xFF << ARMV6_PMCR_EVT_COUNT1_SHIFT)
#define ARMV6_EVENT_CPU_CYCLES      0xFF

inline void reset(){ 
	unsigned flags = ARMV6_PMCR_ENABLE |ARMV6_PMCR_CCOUNT_RESET |ARMV6_PMCR_CCOUNT_DIV | ARMV6_PMCR_CTR01_RESET | (ARMV6_EVENT_CPU_CYCLES << ARMV6_PMCR_EVT_COUNT0_SHIFT);
	asm volatile("mcr   p15, 0, %0, c15, c12, 1" : : "r"(0));
        asm volatile("mcr   p15, 0, %0, c15, c12, 0" : : "r"(flags));
}

#define GET_HIGH(value) asm volatile("mrc   p15, 0, %0, c15, c12, 2" : "=r"(value));
#define GET_LOW(value) asm volatile("mrc   p15, 0, %0, c15, c12, 1" : "=r"(value));

