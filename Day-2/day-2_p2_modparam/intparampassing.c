#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SOWMYA");
MODULE_DESCRIPTION("INT type parameter passing");

static int intvar=2;

module_param(intvar, int, S_IRUGO);

static int __init param_init(void)
{
	printk("In init function\n");
	printk("The value of int type paramater intvar is %d\n",intvar);
	return 0;
}

static void __exit param_exit(void)
{
	printk("In exit function\n");
	printk("byee_byee_module\n");
}

module_init(param_init);
module_exit(param_exit);
