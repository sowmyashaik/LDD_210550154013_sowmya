#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("SOWMYA");
MODULE_DESCRIPTION("INT CHAR type parameter passing");

static int intvar1=2;
static int intvar2=1;
static char* charvar;

//Function for Addition of two integers
static int add(int intvar1, int intvar2)
{
	return (intvar1+intvar2);
}

//Function for Subtraction of two integers
static int sub(int intvar1, int intvar2)
{
	return (intvar1-intvar2);
}

//Function for Multiplication of two integers
static int mul(int intvar1, int intvar2)
{
	return (intvar1*intvar2);
}

//Function for Division of two integers
static int div(int intvar1, int intvar2)
{
	return (intvar1/intvar2);
}


//MACRO PARAM for int and char
module_param(intvar1, int, S_IRUGO);
module_param(intvar2, int, S_IRUGO);
module_param(charvar, charp, S_IRUGO);

//INIT Function
static int __init param_init(void)
{
	printk("In init function\n");
	printk("The value of int type paramater intvar1 is %d\n",intvar1);
	printk("The value of int type paramater intvar2 is %d\n",intvar2);
	//printk("The value of char type paramater charvar is %s\n",charvar);
	if(*charvar == 'A')
	{
	//calling add Function and printing add result
	 printk("Addition of two integers is : %d\n",add(intvar1,intvar2));
	}
	if(*charvar == 'S')
	{
	 //calling sub Function and printing sub result
	 printk("Subtraction of two integers is : %d\n",sub(intvar1,intvar2));
	}
	if(*charvar == 'M')
	{
	 //calling mul Function and printing mul result
	 printk("Multiplication of two integers is : %d\n",mul(intvar1,intvar2));
	}
	if(*charvar == 'D')
	{
	 //calling div Function and printing div result
	 printk("Division of two integers is : %d\n",div(intvar1,intvar2));
	}
	
	
	return 0;
}

//CLEANUP Function
static void __exit param_exit(void)
{
	printk("In exit function\n");
	printk("byee_byee_module\n");
}

//MACROS
module_init(param_init);
module_exit(param_exit);
