#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/workqueue.h>
#include <linux/time.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <asm/mutex.h>

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

#define RESET asm volatile("mcr	p15, 0, %0, c15, c12, 1" : : "r"(0));asm volatile("mcr	p15, 0 ,%0, c15, c12, 0" : : "r"(ARMV6_PMCR_ENABLE |ARMV6_PMCR_CCOUNT_RESET |ARMV6_PMCR_CCOUNT_DIV | ARMV6_PMCR_CTR01_RESET | (ARMV6_EVENT_CPU_CYCLES << ARMV6_PMCR_EVT_COUNT0_SHIFT)));
#define GET_HIGH(value) asm volatile("mrc   p15, 0, %0, c15, c12, 2" : "=r"(value));
#define GET_LOW(value) asm volatile("mrc   p15, 0, %0, c15, c12, 1" : "=r"(value));

unsigned long absdiff(unsigned long s, unsigned long e) {
  //for now, don't worry about overflow correction
  return e - s;
}

unsigned long delta;
int kthreadd(void *unused)
{
	GET_HIGH(delta);
	printk("In thread\n");
	return 0;
}

static int __init exp_init(void)
{
	int err = 0;
	static struct task_struct *thread1;
	int i;
	for( i = 0; i < 100; i ++){
		RESET;
		thread1 = kthread_create(kthreadd, NULL, "thread");
		wake_up_process(thread1);
		set_current_state (TASK_INTERRUPTIBLE);
		schedule_timeout (1 * HZ);
		printk("exp 1 4 timing\t%d\t%lu\n", i, delta);
	}
	return( err ) ;
}

static void __exit exp_exit(void)
{
	printk ("exp14 module unloading...\n") ;
}

module_init(exp_init);
module_exit(exp_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paul Drongowski");
MODULE_DESCRIPTION("Simple ARMv6 profiler");
