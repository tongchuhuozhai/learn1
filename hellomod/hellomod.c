#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("GPL");
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
