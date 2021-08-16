#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>


//Function prototypes
int open_add(struct inode *inode, struct file *file_op_add);
int release_add(struct inode *inode, struct file *file_op_add);
ssize_t write_add(struct file *file_op_add,const char __user *u_buff,size_t count,loff_t *offp );
ssize_t read_add(struct file *file_op_add,char __user *u_buff, size_t count, loff_t *offp);

static int add_result; 

struct file_operations fop_add=
{
	.owner = THIS_MODULE,
	.open = open_add,
	.read = read_add,
	.write = write_add,
	.release = release_add,
};

//add open call
int open_add(struct inode *inode, struct file *file_op_add)
{
	printk("Add open call\n");
	return 0;
}

//add read call
ssize_t read_add(struct file *file_op_add,char __user *u_buff,size_t count,loff_t *offp)
{
	ssize_t retval;
	int result;
	const int *val  = &add_result; 
	result = copy_to_user(u_buff,val,sizeof(add_result));
	if(result >= 0) 
	{
		printk("send the result\n");
		retval = sizeof(add_result);
		return retval;
	}
	else
	{
		printk("sending data not done\n");
		return (-1);
	}
}

//add write call
ssize_t write_add(struct file *file_op_add, const char __user *u_buff, size_t count, loff_t *offp)
{
	int result;
	int k_buff[2]; 
	ssize_t retval;
	result = copy_from_user((char *)k_buff,u_buff,count); 
	if(result >= 0) 
	{
		printk("the data from user are:%d and %d\n",(int)k_buff[0],(int)k_buff[1]); 
		add_result = (int)k_buff[0] + (int)k_buff[1]; 
		printk("the addition result is: %d and its send to user space\n",add_result);
		retval = count;
		return retval; 
	}
	else
	{
		printk("not able to read from user\n");
		return (-1);
	}
}

//add close call
int release_add(struct inode *inode, struct file *file_op_add)
{
	printk("Add close call\n");
	return 0;
}

//Function prototypes
int open_sub(struct inode *inode, struct file *file_op_sub);
int release_sub(struct inode *inode, struct file *file_op_sub);
ssize_t write_sub(struct file *file_op_sub,const char __user *u_buff,size_t count, loff_t *offp);
ssize_t read_sub(struct file *file_op_sub, char __user *u_buff, size_t count, loff_t *offp);

static int sub_result;

struct file_operations fop_sub=
{
	.owner = THIS_MODULE,
	.open = open_sub,
	.read = read_sub,
	.write = write_sub,
	.release = release_sub,
};

//sub open call
int open_sub(struct inode *inode, struct file *file_op_sub)
{
	printk("sub open call\n");
	return 0;
}

//sub write call
ssize_t write_sub(struct file *file_op_sub, const char __user *u_buff, size_t count,loff_t *offp)
{
	int result;
	int k_buff[2];
	ssize_t retval;
	result = copy_from_user((char *)k_buff, u_buff, count);
	if(result >= 0)
	{
		printk("data received from user: %d and %d\n",(int)k_buff[0],(int)k_buff[1]);
		sub_result = (int)k_buff[0] - (int)k_buff[1];
		printk("subtraction is: %d send to the user\n",sub_result);
		retval = count;
		return retval;
	}
	else
	{
		printk("data not received\n");
		return (-1);
	}
}

//sub read call
ssize_t read_sub(struct file *file_op_sub, char __user *u_buff, size_t count, loff_t *offp)
{
	int result;
	ssize_t retval;
	result = copy_to_user(u_buff,&sub_result,sizeof(sub_result));
	if (result >=0)
	{
		printk("result successfully send to the user\n");
		retval = sizeof(sub_result);
		return retval;
	}
	else
	{
		printk("sending data is not done");
		return (-1);
	}
}


//sub close call
int release_sub(struct inode *inode, struct file *file_op_sub)
{
	printk("In sub close call\n");
	return 0;
}

//Function prototypes
int open_mul(struct inode *inode,struct file *file_op_mul);
int release_mul(struct inode *inode, struct file *file_op_mul);
ssize_t write_mul(struct file *file_op_mul, const char __user *u_buff,size_t count,loff_t *offp);
ssize_t read_mul(struct file *file_op_mul,char __user *u_buff,size_t count, loff_t *offp);

static int mul_result;


struct file_operations fop_mul=
{
	.owner = THIS_MODULE,
	.open = open_mul,
	.read = read_mul,
	.write = write_mul,
	.release = release_mul,
};

//mul open call
int open_mul(struct inode *inode, struct file *file_op_mul)
{
	printk("In mul open call\n");
	return 0;
}

//mul write call
ssize_t write_mul(struct file *file_op_mul,const char __user *u_buff,size_t count, loff_t *offp)
{
	int result;
	int k_buff[2];
	ssize_t retval;
	result = copy_from_user((char *)k_buff,u_buff,count);
	if(result >= 0)
	{
		printk("data from user\n");
		printk("data from user: %d and %d\n",(int)k_buff[0],(int)k_buff[1]);
		mul_result = (int)k_buff[0] * (int)k_buff[1];
		printk("multiplication: %d and send to user\n",mul_result);
		retval = count;
		return retval;
	}
	else
	{
		printk("error in writing data from user\n");
		return (-1);
	}
}

//mul read call
ssize_t read_mul(struct file *file_op_mul,char __user *u_buff,size_t count,loff_t *offp)
{
	int result;
	ssize_t retval;
	result = copy_to_user(u_buff,&mul_result,sizeof(mul_result));
	if(result >= 0)
	{
		printk("the sending is done\n");
		retval = sizeof(mul_result);
		return retval;
	}
	else
	{
		printk("The send operation not done successfully\n");
		return (-1);
	}
}

//mul close call
int release_mul(struct inode *inode,struct file *file_op_mul)
{
	printk("In mul close call\n");
	return 0;
}

//function prototypes
int open_div(struct inode *inode,struct file *file_op_div);
int release_div(struct inode *inode,struct file *file_op_div);
ssize_t write_div(struct file *file_op_div, const char __user *u_buff,size_t count,loff_t *offp);
ssize_t read_div(struct file *file_op_div, char __user *u_buff, size_t count, loff_t *offp);

static int div_result;


struct file_operations fop_div=
{
	.owner = THIS_MODULE,
	.open = open_div,
	.read = read_div,
	.write = write_div,
	.release = release_mul,
};

//div open call
int open_div(struct inode *inode,struct file *file_op_div)
{
	printk("In div open call\n");
	return 0;
}

//div write call
ssize_t write_div(struct file *file_op_div, const char __user *u_buff,size_t count, loff_t *offp)
{
	int k_buff[2];
	int result;
	ssize_t retval;
	result = copy_from_user((char *)k_buff,u_buff,count);
	if(result >= 0)
	{
		printk("data received from user done and data are: %d and %d\n",(int)k_buff[0],(int)k_buff[1]);
		div_result = (int)k_buff[0]/(int)k_buff[1];
		printk("the division result is: %d and now send to user",div_result);
		retval = count;
		return retval;
	}
	else
	{
		printk("data read not done successfully\n");
		return (-1);
	}
}

//div read call
ssize_t read_div(struct file *file_op_div,char __user *u_buff, size_t count,loff_t *offp)
{
	int result;
	ssize_t retval;
	result = copy_to_user(u_buff,&div_result,sizeof(div_result));
	if(result >= 0)
	{
		printk("data send to user done\n");
		retval = sizeof(div_result);
		return retval;
	}
	else
	{
		printk("data send not done successfully\n");
		return (-1);
	}
}

//div close call
int release_div(struct inode *inode,struct file *file_op_div)
{
	printk("In div close call\n");
	return 0;
}

//structure variables for device files
struct cdev *AddDev;
struct cdev *SubDev;
struct cdev *MulDev;
struct cdev *DivDev;


dev_t Mydev;
dev_t Mydevadd;
dev_t Mydevsub;
dev_t Mydevmul;
dev_t Mydevdiv;

//init module
static int cal_driver_init(void) 
{
	int result;
	int major;

	result = alloc_chrdev_region(&Mydev, 0,4,"MyCalDriver"); // dynamically allocate device number

	if (result < 0) 
	{
		printk(KERN_ALERT "not allocated region\n");
		return 0;
	}

	major = MAJOR(Mydev); 
	printk(KERN_ALERT "the allocated driver having the major number: %d\n\nminor no 0: for AddDev device\nminor no 1: for SubDev device\nminor no 2: for MulDev device\nminor no 3: for DivDev device\n",major);
	
	Mydevadd = MKDEV(major,0);
	Mydevsub = MKDEV(major,1);
	Mydevmul = MKDEV(major,2);
	Mydevdiv = MKDEV(major,3);

	AddDev = cdev_alloc(); 
	AddDev->ops = &fop_add;
	
	SubDev = cdev_alloc();
	SubDev->ops = &fop_sub;

	MulDev = cdev_alloc();
	MulDev->ops = &fop_mul;

	DivDev = cdev_alloc();
	DivDev->ops = &fop_div;

	int result_add = cdev_add(AddDev,Mydevadd,1);
	if(result_add <0 ) 
	{
		printk(KERN_ALERT "driver not allocated\n");
		return (-1);
	}

	int result_sub = cdev_add(SubDev,Mydevsub,1);
	if(result_sub <0)
	{
		printk(KERN_ALERT "driver not allocated\n");
		return (-1);
	}

	int result_mul = cdev_add(MulDev,Mydevmul,1);
	if(result_mul <0)
	{
		printk(KERN_ALERT "driver not allocated\n");
		return (-1);
	}

	int result_div = cdev_add(DivDev,Mydevdiv,1);
	if(result_div <0)
	{
		printk(KERN_ALERT "driver not allocated\n");
		return (-1);
	}

	return 0;
}
//exit module
static void cal_driver_exit(void)
{
	cdev_del(AddDev);
	cdev_del(SubDev);
	cdev_del(MulDev);
	cdev_del(DivDev);
	//cdev_del(Mydev);
	unregister_chrdev_region(Mydev, 4);
}

module_init(cal_driver_init);
module_exit(cal_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SOWMYA");
MODULE_DESCRIPTION("calculator driver");



