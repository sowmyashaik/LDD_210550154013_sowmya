#include "synch_spinlock.h"

#define NMINORS 1

#define DELAY 5000

//declaring tasklet variable
//struct tasklet_struct synch_spinlock_tasklet;

//daclaring spinlock variable
spinlock_t slock;

int major;
int minor=0;
dev_t deviceno;
struct cdev synch_spinlock_cdev;
struct class *synch_spinlock_class;
struct device *synch_spinlock_device;

//read call
ssize_t synch_spinlock_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offp)
{
	static unsigned int fake_val = 10;
	printk("In read function\n");
	
	//Acquring spinlock
	spin_lock(&slock);
	  
	// start of critical section
	mdelay(DELAY); //current thread goto sleep
	
	fake_val++;
	copy_to_user(ubuf, &fake_val, sizeof(fake_val)); //sending data to the user
	
	//releasing spinlock
	spin_unlock(&slock);
	//end of critical section
	
	return sizeof(fake_val);
	
}

//struct file operations
struct file_operations synch_spinlock_fops = 
{
	.owner = THIS_MODULE,
	.read = synch_spinlock_read,
};

//INIT function
static int __init synch_spinlock_init(void)
{
	PINFO("In init function\n");
	alloc_chrdev_region(&deviceno, minor,NMINORS, DRIVER_NAME); //allocating major number dynamically
	major = MAJOR(deviceno);
	PINFO("MAJOR = %d",major);
	PINFO("MAJOR\n");
	
	cdev_init(&synch_spinlock_cdev,&synch_spinlock_fops);
	cdev_add(&synch_spinlock_cdev, deviceno, 1);
	
	synch_spinlock_class = class_create(THIS_MODULE, DRIVER_NAME);
	synch_spinlock_device = device_create(synch_spinlock_class, NULL, deviceno, NULL, "sample_cdev");
	
	// initialization of spinlock
	spin_lock_init(&slock);
	return 0;
}


//EXIT function
static void __exit synch_spinlock_exit(void)
{
	PINFO("In exit function\n");
	device_destroy(synch_spinlock_class, deviceno);
	class_destroy(synch_spinlock_class);
	
	cdev_del(&synch_spinlock_cdev);
	unregister_chrdev_region(deviceno,NMINORS);
}

module_init(synch_spinlock_init);
module_exit(synch_spinlock_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SOWMYA");
MODULE_DESCRIPTION("spinlock");
	
	
