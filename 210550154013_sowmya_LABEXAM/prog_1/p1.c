#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <linux/sched.h>

int flag = 1;

char ker_buff[50]; //kernel buffer
struct semaphore sem1;
struct semaphore sem2;


//Function prototypes
ssize_t write_dev1(struct file *file_op_sub,const char __user *u_buff,size_t count, loff_t *offp);
ssize_t read_dev1(struct file *file_op_sub, char __user *u_buff, size_t count, loff_t *offp);


struct file_operations fop_dev1=
{
	.owner = THIS_MODULE,
	.read = read_dev1,
	.write = write_dev1,
};

DECLARE_WAIT_QUEUE_HEAD (mywait);
//sub write call
ssize_t write_dev1(struct file *file_op_sub, const char __user *u_buff, size_t count,loff_t *offp)
{
	int result;
	printk("In write call\n");
	ssize_t retval;
	if(down_interruptible(&sem1))
	     return -ERESTARTSYS;
	   
	result = copy_from_user(ker_buff, u_buff, count);
	if(result == 0)
	{
		printk("data received from user of dev1: %s\n",ker_buff);
		retval = count;
		flag = 0;
		wake_up_interruptible(&mywait);
		return retval;
	}
	else
	{
		printk("data not received\n");
		return (-1);
	}

	
}

//sub read call
ssize_t read_dev1(struct file *file_op_sub, char __user *u_buff, size_t count, loff_t *offp)
{
	int result;
	ssize_t retval;
	if(flag == 1)
	{
		wait_event_interruptible(mywait,flag==0);
	}
	     
	result = copy_to_user(u_buff,&ker_buff,sizeof(ker_buff));
	if (result ==0)
	{
		flag =1;
		printk("send to the user from dev1\n");
		retval = sizeof(ker_buff);
		return retval;
	}
	else
	{
		printk("sending data is not done");
		return (-1);
	}
	
	up(&sem2);
}

//Function prototypes
ssize_t write_dev2(struct file *file_op_sub,const char __user *u_buff,size_t count, loff_t *offp);
ssize_t read_dev2(struct file *file_op_sub, char __user *u_buff, size_t count, loff_t *offp);

struct file_operations fop_dev2=
{
	.owner = THIS_MODULE,
	.read = read_dev2,
	.write = write_dev2,
};


//sub write call
ssize_t write_dev2(struct file *file_op_sub, const char __user *u_buff, size_t count,loff_t *offp)
{
	int result;
	ssize_t retval;
	
	//Acquiring semaphore
	if(down_interruptible(&sem2))
	  return -ERESTARTSYS;
	     
	result = copy_from_user(ker_buff, u_buff, count);
	if(result == 0)
	{
		printk("data from user of dev2 : %s\n",ker_buff);
		retval = count;
		flag = 0;
		wake_up_interruptible(&mywait);
		return retval;
	}
	else
	{
		printk("data not received\n");
		return (-1);
	}
	
}

//sub read call
ssize_t read_dev2(struct file *file_op_sub, char __user *u_buff, size_t count, loff_t *offp)
{
	int result;
	ssize_t retval;
	if(flag == 1)
	{
		wait_event_interruptible(mywait,flag==0);
	}
	    
	result = copy_to_user(u_buff,&ker_buff,sizeof(ker_buff));
	if (result ==0)
	{
		flag = 1;
		printk("send to the user from dev2\n");
		retval = sizeof(ker_buff);
		return retval;
	}
	else
	{
		printk("sending data is not done");
		return (-1);
	}
	up(&sem1);
}



//structure variables for device files
struct cdev *mycdev1;
struct cdev *mycdev2;


dev_t Mydev;
dev_t Mydev1;
dev_t Mydev2;

//init module
static int ker_syn_init(void) 
{
	int result;
	int res_dev1;
	int res_dev2;
	int MAJOR;
	result = alloc_chrdev_region(&Mydev, 0,2,"chardriver"); // dynamically allocate device number
	if (result < 0) 
	{
		printk(KERN_ALERT "there is no allocated region\n");
		return 0;
	}

	MAJOR = MAJOR(Mydev); 
	Mydev1 = MKDEV(MAJOR,0);
	Mydev2 = MKDEV(MAJOR,1);

	mycdev1 = cdev_alloc(); 
	mycdev1->ops = &fop_dev1;
	
	mycdev2 = cdev_alloc();
	mycdev2->ops = &fop_dev2;

	res_dev1 = cdev_add(mycdev1,Mydev1,1);
	if(res_dev1 < 0 ) 
	{
		printk(KERN_ALERT "not allocated dev1\n");
		return (-1);
	}

	res_dev2 = cdev_add(mycdev2,Mydev2,1);
	if(res_dev2 < 0)
	{
		printk(KERN_ALERT "not allocated dev2\n");
		return (-1);
	}
	
	//sem initialization
	sema_init(&sem1,1);
	sema_init(&sem2,0);

	return 0;
}
//exit module
static void ker_syn_exit(void)
{
	cdev_del(mycdev1);
	cdev_del(mycdev2);
	unregister_chrdev_region(Mydev, 2);
}

module_init(ker_syn_init);
module_exit(ker_syn_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SOWMYA");
MODULE_DESCRIPTION("kernel syncronization mechanism");



