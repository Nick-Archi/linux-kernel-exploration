/*
 * @brief 
 */

// linux kernel includes
#include <linux/module.h>
#include <linux/init.h>

// needed for accessing filesystem operations
#include <linux/fs.h>

// 
#include <linux/cdev.h>
#include <linux/uaccess.h>

// kernel module meta info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("N Arc");
MODULE_DESCRIPTION("Registers a device number and implements some callback functions");

#define DEVICE_FILE_NAME "my_dev"
#define DRIVER_CLASS "my_drv_class"

// Buffer data for device file
#define BUFFER_SIZE 256
static unsigned char buffer[BUFFER_SIZE];
static unsigned int p_buffer;

// Variables for device & device class
static dev_t my_device_nr; // device number
static struct class* my_class; // device class
static struct cdev my_device; // info regarding device

/*
 * @brief Handler function for reading data out from the dev buffer
 *
 * @param pfile Pointer to file struct for kernel module
 * @param input Pointer to input buffer from caller for storing read
 * @param request number of bytes to read from device file
 * @param offs 
 *
 * @return number of bytes copied from kernel buffer
 */
static ssize_t driver_read(struct file* pfile, char* input, size_t request, loff_t *offs)
{
    /* obtain amount to copy over choosing the minimum b/w 
     * the request and how much was actually read in. Essentially
     * keeping in the size constraint of kernel buffer
     */
    unsigned int bytes_to_copy = min(request, p_buffer);

    // kernel specific call to copy data from ko to user
    unsigned int bytes_left = copy_to_user(input, buffer, bytes_to_copy);

    unsigned int bytes_copied = bytes_to_copy - bytes_left;

   return bytes_copied; 
}

/*
 * @brief Handler function for writing data to the dev buffer
 *
 * @param pfile Pointer to file struct for kernel module
 * @param input Pointer to constant input buffer from caller containing data to write from user to kernel 
 * @param request number of bytes to write from device file
 * @param offs 
 *
 * @return number of bytes copied to kernel buffer
 */
static ssize_t driver_write(struct file* pfile, const char* input, size_t request, loff_t *offs)
{
    /* obtain amount to copy over. Essentially
     * keeping within the size of kernel buffer
     */
    unsigned int bytes_to_copy = min(request, BUFFER_SIZE);

    // kernel specific call to copy data from user to ko 
    unsigned int bytes_left = copy_from_user(buffer, input, bytes_to_copy);

    // update how much data is contained within kernel buffer now
    p_buffer = bytes_to_copy;

    unsigned int bytes_copied = bytes_to_copy - bytes_left;

   return bytes_copied; 
}

/*
 * @brief Handler function for opening device file
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
 * @brief Handler function for calling closure of device file
 *
 * @param device_file, pointer to inode, metadata about a file/directory
 * @param instance, pointer to file object containing encapsulations
 */
static int driver_close(struct inode* device_file, struct file* instance)
{
    printk(KERN_INFO "dev_nr - close called\n");
    return 0;
}

// declare & set the file operations and handles for this module
static struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
    .read = driver_read,
    .write = driver_write
};

// declare functions for loading and exiting kernel module

/**
 * @brief This function called when module loaded into kernel. It will automatically allocate a free device number.
 */
static int __init ModuleInit(void)
{
	printk(KERN_INFO "Attempting to register device...\n");

    // allocate free device number
    if(alloc_chrdev_region(&my_device_nr, 0, 1, DEVICE_FILE_NAME) < 0)
    {
        printk(KERN_ALERT "Device Number couldn't be allocated\n");
        return -1;
    }

    printk(KERN_INFO "%s - Device Number: %d, Minor %d was registered\n",
            DEVICE_FILE_NAME, MAJOR(my_device_nr), MINOR(my_device_nr));

    // create virtual device class
    if ((my_class = class_create(DRIVER_CLASS)) == NULL)
    {
        printk(KERN_ALERT "Device class %s cannot be created\n", DRIVER_CLASS);
        goto classError;
    }

    // create device file
    if(device_create(my_class, NULL, my_device_nr, NULL, DEVICE_FILE_NAME)== NULL)
    {
        printk(KERN_ALERT "Cannot create device file: %s\n", DEVICE_FILE_NAME);
        goto fileError;
    }

    // initialize device file
    cdev_init(&my_device, &fops);

    // intialize device file in /sys/class/
    if(cdev_add(&my_device, my_device_nr, 1) == -1)
    {
        printk(KERN_ALERT "Registering of device %s, to kernel failed", DEVICE_FILE_NAME);
        goto cdevError;
    }

	return 0;

/*
 * Usually goto statements are frowned upon in user space programming but in kernel programming, it allows a cascading effect when an error occurs. It's either this or using conditionals to track at which point an issue occurred and what type of cleanup is required.
 */
cdevError:
    device_destroy(my_class, my_device_nr);
fileError:
    class_destroy(my_class);
classError:
    unregister_chrdev(my_device_nr, DEVICE_FILE_NAME);

    return -1;
}

/**
 * @brief This function is called when the module is removed from the kernel.
 */
static void __exit ModuleExit(void)
{
    cdev_del(&my_device);
    device_destroy(my_class, my_device_nr);
    class_destroy(my_class);
    unregister_chrdev(my_device_nr, DEVICE_FILE_NAME);
    printk(KERN_INFO "Unregistering device...\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
