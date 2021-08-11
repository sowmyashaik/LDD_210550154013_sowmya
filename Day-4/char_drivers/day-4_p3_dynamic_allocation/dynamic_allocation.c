#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

dev_t dev = 0;

#define NAME MyCharDevice


static int __init CharDevice_init(void);
static void __exit CharDevice_exit(void);

//init module
static int __init CharDevice_init(void)
{
	if((alloc_chrdev_region(&dev,0,1,"MyCharDevice")) < 0)//allocating Major number
	{
		printk("cannot allocate major number\n");
		return (-1);
	}
	printk("\n MAJOR NO. is %d.... MINOR NO. is %d\n",MAJOR(dev),MINOR(dev));
	printk("Module inserted successfully\n");
	return 0;
}


//cleanup module
static void __exit CharDevice_exit(void)
{
	unregister_chrdev_region(dev,1);//unregister device region
	printk("\n kernel module removed successfully\n");
}

//MACROS
module_init(CharDevice_init);
module_exit(CharDevice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SOWMYA");
MODULE_DESCRIPTION("Dynamically allocating the major and minor numbers");



		
	
	

