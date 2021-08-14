#include "synch_semaphore.h"


#define LOCK 0
#define UNLOCK 1
#define NMINORS 1

#define DELAY 5000

//declaring variable of type struct semaphore to perform operations
struct semaphore sample_sem;

int major;
int minor=0;
dev_t deviceno;
struct cdev synch_semaphore_cdev;
struct class *synch_semaphore_class;
struct device *synch_semaphore_device;

//read call
ssize_t synch_semaphore_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offp)
{
	static unsigned int fake_val = 10;
	printk("In read function\n");
	
	//Acquring semaphore
	if(down_interruptible(&sample_sem))
	  return -ERESTARTSYS;
	  
	// start of critical section
	msleep(DELAY); //current thread goto sleep
	
	fake_val++;
	copy_to_user(ubuf, &fake_val, sizeof(fake_val)); //sending data to the user
	
	up(&sample_sem);
	//end of critical section
	
	return sizeof(fake_val);
	
}

//struct file operations
struct file_operations synch_semaphore_fops = 
{
	.owner = THIS_MODULE,
	.read = synch_semaphore_read,
};

//INIT function
static int __init synch_semaphore_init(void)
{
	PINFO("In init function\n");
	alloc_chrdev_region(&deviceno, minor,NMINORS, DRIVER_NAME); //allocating major number dynamically
	major = MAJOR(deviceno);
	
	cdev_init(&synch_semaphore_cdev,&synch_semaphore_fops);
	cdev_add(&synch_semaphore_cdev, deviceno, 1);
	
	synch_semaphore_class = class_create(THIS_MODULE, DRIVER_NAME);
	synch_semaphore_device = device_create(synch_semaphore_class, NULL, deviceno, NULL, "sample_cdev");
	
	//sem init
	sema_init(&sample_sem,UNLOCK);
	return 0;
}


//EXIT function
static void __exit synch_semaphore_exit(void)
{
	PINFO("In exit function\n");
	device_destroy(synch_semaphore_class, deviceno);
	class_destroy(synch_semaphore_class);
	
	cdev_del(&synch_semaphore_cdev);
	unregister_chrdev_region(deviceno,NMINORS);
}

module_init(synch_semaphore_init);
module_exit(synch_semaphore_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SOWMYA");
MODULE_DESCRIPTION("synchronization semaphore");
	
	
