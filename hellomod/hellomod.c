#include <linux/interrupt.h>
#include <linux/module.h>
#include <asm/uaccess.h> // if not contain this file, copy_to_user would error for compitiple error.
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/types.h>

#include <linux/mm.h>

#include <linux/workqueue.h>

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
#include "hellomod.h"
/*
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>
*/

MODULE_LICENSE("GPL");
/*
0x12345678 could be a hardware address, define a poninter 
 which points this address, this pointer's type is volatile 
 unsigned. 
 
 */
#define hw_pointer ((volatile unsigned*)0x12345678)

// define the variable to get the content of hardware address
#define hw_pointer_value (*hw_pointer)



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

/*
Although these function are defined in this file, they must be declared before called. 
*/
void l_work_queue();
void l_pointMem();
void l_irq();

// 
char *device_name;
const int device_id = 100;
int irq_number = 12;

static int __init hello_init(void)
{
	device_name = kmalloc(20, GFP_KERNEL);
	device_name ="name1";

        dev_t d = MKDEV(device_id, 0);

	int register_code = register_chrdev_region(d, 1, device_name);
	if( register_code < 0 ){
	   printk("register_code : %d", register_code);
	   return 1;
	}

	globalmem_devp = kmalloc(sizeof(struct globalmem_dev), GFP_KERNEL);
	memset(globalmem_devp, 0, sizeof(globalmem_devp));

	// init char device
	#if 1
	// this is static initilization
 	cdev_init(&globalmem_devp->cdev, &fops);
	#else
	// this is dynamic initialization
	globalmem_devp->cdev = cdev_alloc();
	globalmem_devp->cdev.ops = &fops;		 
	#endif

	cdev_add(&globalmem_devp->cdev, d, 1);
	printk("test .............. " );	

	l_work_queue();
	l_pointMem();
	l_irq();
		
}
void func(){
	printk("delayed work........");
}

void l_pointMem(){
	short int x;
	x = 0x0001;
	
	char *p[2];
	char *p1;
	// p = (char *[])&x;
	p1 = (char *)&x;
}

void l_work_queue(){
	struct workqueue_struct *wqs;
        create_singlethread_workqueue("workqueue1");
	struct delayed_work *dw;
	INIT_DELAYED_WORK(dw, func);
}

void l_work_queue_1()
{
	wait_queue_head_t queue_head;
	init_waitqueue_head(&queue_head);
	//DECLARE_WAITQUEUE("queue1", );	
	
}
void irq_handle()
{
	printk("irq_handle");
}


void l_irq()
{
	request_irq(irq_number, irq_handle, 0, device_name, &device_id);
}


static void __exit hello_exit(void)
{

	cdev_del(&globalmem_devp->cdev);
	kfree(globalmem_devp);
	free_irq(irq_number, device_name);
	printk("hello exit. " );
}

long sub_add1(int a, int b)
{
	return a+b;
}

EXPORT_SYMBOL(sub_add1);

module_init(hello_init);
module_exit(hello_exit);
