/*
 * Simple Kernel Module to practice instantiating a device file and interfacing with a user application/request.
 */

// linux kernel includes
#include <linux/module.h>
#include <linux/init.h>

// needed for accessing filesystem
#include <linux/fs.h>

// meta info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("N Arc");
MODULE_DESCRIPTION("Registers a device number and implements some callback functions");

#define MYMAJOR 90
#define DEVICEFILENAME "my_dev_nr"

/*
 * @brief This function is called when the device file is opened
 *
 * @param device_file, pointer to inode, metadata about a file/directory
 * @param instance, pointer to open file (not an actual file) used by kernel exclusively 
 */
static int driver_open(struct inode* device_file, struct file* instance)
{
    printk(KERN_INFO "dev_nr - open called\n");
    return 0;
}

/*
 * @brief This function is called when the device file is closed
 *
 * @param device_file, pointer to inode, metadata about a file/directory
 * @param instance, pointer to file object containing encapsulations
 */
static int driver_close(struct inode* device_file, struct file* instance)
{
    printk(KERN_INFO "dev_nr - close called\n");
    return 0;
}

// declare & set the file operations for this module
static struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close
};

// declare functions for loading and exiting kernel module

/**
 * @brief This function called when module loaded into kernel
 */
static int __init ModuleInit(void)
{
    int retVal;
	printk(KERN_INFO "Attempting to register device...\n");

    // manually select a device number, ex) ls /proc/devices
    // search for a free number on your system...
    retVal = register_chrdev(MYMAJOR, DEVICEFILENAME, &fops);

    // if registering device was OK
    if(retVal == 0)
    {
        printk(KERN_INFO "dev_nr - registered!\nDevice number Major: %d, Minor: %d\n", MYMAJOR,0);
    }
    // if there was already a device with the Major Number assigned
    else if(retVal > 0)
    {
        printk(KERN_INFO "dev_nr - registered!\nDevice number Major: %d, Minor: %d\n", retVal>>20, retVal & 0xFFFFF);

    }
    // something is just wrong during registration
    else
    {
       printk(KERN_INFO "Could not register device...\n");
       return -1;
    }
	return 0;
}

/**
 * @brief This function is called when the module is removed from the kernel.
 */
static void __exit ModuleExit(void)
{
    printk(KERN_INFO "Unregistering device...\n");
    unregister_chrdev(MYMAJOR, DEVICEFILENAME); 
}

module_init(ModuleInit);
module_exit(ModuleExit);
