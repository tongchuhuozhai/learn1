#include <linux/module.h>
#include <asm/uaccess.h> // 如果不包含这个文件，则copy_to_user报兼容性错误
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/types.h>

#include <linux/mm.h>


#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/time.h>
#include <linux/security.h>
#include <linux/syscalls.h>
#include <linux/audit.h>
#include <linux/capability.h>
#include <linux/seq_file.h>
#include <linux/rwsem.h>
#include <linux/nsproxy.h>
#include <linux/ipc_namespace.h>
/*
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>
*/

MODULE_LICENSE("GPL");
// 0x12345678 could be a hardware address, define a poninter 
// which points this address, this pointer's type is volatile 
// unsigned. 
#define hw_pointer ((volatile unsigned*)0x12345678)

// define the variable to get the content of hardware address
#define hw_pointer_value (*hw_pointer)

struct globalmem_dev {
	struct cdev cdev;	
	char mem[100];
};

struct globalmem_dev *globalmem_devp;

static ssize_t f_read(struct file *f, void __user *buf, size_t count)
{
	struct globalmem_dev *dev = f->private_data;
	copy_to_user(buf, &dev, count); 
	return 1;
}

int f_open(struct inode *inode, struct file *filp)
{
	filp->private_data = globalmem_devp;
	return 0;
}

static const struct file_operations fops = 
{
	.open = f_open,
	.read = f_read,
};

static int __init hello_init(void)
{
	short int x;
	x = 0x0001;
	
	char *p[2];
	char *p1;
	// p = (char *[])&x;
	p1 = (char *)&x;
	
    dev_t d = MKDEV(100, 0);
	register_chrdev_region(d, 1, "ggggggg");

	globalmem_devp = kmalloc(sizeof(struct globalmem_dev), GFP_KERNEL);

	// init char device
 	cdev_init(&globalmem_devp->cdev, &fops);
	globalmem_devp->cdev.ops = &fops;
	cdev_add(&globalmem_devp->cdev, d, 1);
	
	printk("test .............. " );			
}

static void __exit hello_exit(void)
{
	cdev_del(&globalmem_devp->cdev);
	kfree(globalmem_devp);
	printk("hello exit. " );
}


module_init(hello_init);
module_exit(hello_exit);
