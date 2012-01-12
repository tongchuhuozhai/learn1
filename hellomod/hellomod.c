#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("GPL");
// 0x12345678 could be a hardware address, define a poninter 
// which points this address, this pointer's type is volatile 
// unsigned. 
#define hw_pointer ((volatile unsigned*)0x12345678)

// define the variable to get the content of hardware address
#define hw_pointer_value (*hw_pointer)

static int __init hello_init(void)
{
	printk("init ");
}

static void __exit hello_exit(void)
{
	printk("hello exit. " );
}


module_init(hello_init);
module_exit(hello_exit);
