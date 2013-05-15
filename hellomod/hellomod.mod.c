#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x69cd1ba3, "module_layout" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x37a0cba, "kfree" },
	{ 0x67541273, "cdev_del" },
	{ 0xdae0e9e0, "cdev_add" },
	{ 0xf9d418e0, "cdev_init" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0x40a8d09e, "kmem_cache_alloc_trace" },
	{ 0xc2859108, "kmalloc_caches" },
	{ 0xfda85a7d, "request_threaded_irq" },
	{ 0x9e1bdc28, "init_timer_key" },
	{ 0x8ba977a2, "__alloc_workqueue_key" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x27e1a049, "printk" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "F8484817A998013687BC79F");
