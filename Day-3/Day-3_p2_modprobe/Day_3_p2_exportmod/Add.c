#include<linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SOWMYA");
MODULE_DESCRIPTION("EXPORT SYMBOL");

int Helloworld_type=1;

static int Helloworld_add(int a, int b);
//INIT function for program
static int __init hello_init(void)
{
	printk("In init module... Module param is :%d\n",Helloworld_type);
	printk("Hello_world\n");
	return 0;
}

static int Helloworld_add(int a, int b)
{
	printk("Helloworld_add....\n");
	return (a+b);
}

EXPORT_SYMBOL_GPL(Helloworld_add);

//CLEANUP function
static void __exit hello_exit(void)
{
	printk("In cleanup module...Module param is :%d\n",Helloworld_type);
	printk("Good_byee\n");
}

//MACROS
module_init(hello_init);
module_exit(hello_exit);

//MACRO PARAM for Helloworld_type
module_param(Helloworld_type, int,S_IRUGO);
