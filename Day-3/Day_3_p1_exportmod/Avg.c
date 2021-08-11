#include<linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include "Header.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SOWMYA");
MODULE_DESCRIPTION("EXPORT SYMBOL");

//int Helloworld_type=1;

//static int Helloworld_add(int a, int b);
int a_m2=2, b_m2=3;
//INIT function for program
static int __init hello_init(void)
{
	int Average;
	printk("In init module... Module param a_m2 is :%d\n",a_m2);
	printk("Hello_world\n");
	Average=Helloworld_add(a_m2,b_m2)/2;
	printk("Average is : %d\n",Average);
	return 0;
}


//CLEANUP function
static void __exit hello_exit(void)
{
	printk("In cleanup module...Module param a_m2 is :%d\n",a_m2);
	printk("Good_byee\n");
}

//MACROS
module_init(hello_init);
module_exit(hello_exit);

//MACRO PARAM for Helloworld_type
module_param(a_m2, int,S_IRUGO);
module_param(b_m2, int,S_IRUGO);
