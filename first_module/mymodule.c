// linux kernel includes
#include <linux/module.h>
#include <linux/init.h>

// meta info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("N Arc");
MODULE_DESCRIPTION("My 1st linux kernel module");

// declare functions for loading and exiting kernel module

/**
 * @brief This function called when module loaded into kernel
 */
static int __init ModuleInit(void)
{
	printk("Hello Kernel...\n");
	return 0;
}

/**
 * @brief This function is called when the module is removed from the kernel.
 */
static void __exit ModuleExit(void)
{
    printk("Goodbye Kernel...\n");    
}

module_init(ModuleInit);
module_exit(ModuleExit);
