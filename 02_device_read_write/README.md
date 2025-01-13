# Device Numbers and Files 

## Table of Content
[Introduction](#introduction)<br>
[Objective](#objective)<br>
[Prereqs](#prereqs)<br>
[Building](#building)<br>
[Executing](#executing)<br>
[References](#references)<br>

## Introduction
In this example, I build upon the 01 module from before and add some new functionality to the kernel module to:
- transfer data between the kernel space and user space 
- auto mate obtaining a major and minor number
- register and create the device file
- properly destroy and unregister device file upon destruction/closing

---

## Objective
- create functionality to write and read sample data from the device file
- create functionality for the kernel module to auto register the device file upon module initialization

## Prereqs
- Everything should already be installed on your Linux machine (make, insmod, rmmod)...but just in case

```
Find out Kernel Version:
$ uname -r

Update Packages:
$ sudo apt update && sudo apt upgrade -y

Install Kernel Headers:
$ sudo apt install -y raspberrypi-kernel-headers

Linux Kernel Headers located in:
/usr/src
ex) $ ls /usr/src/linux-headers-6.6.62+rpt-common-rpi/include/linux/

Install Build Tools:
sudo apt install -y build-essential

```

## Building
    ```
    $ make clean
    $ make
    ```

## Executing
- TIP: To view kernel messages, in a new terminal execute:
    ```
    $ watch -n 1 "dmesg | tail -n 10"
    ```

    - Loading & unloading kernel module
    ```
    $ sudo insmod <module>.ko
    $ cat /proc/devices | grep <device_file_name>
    $ sudo rmmod <module>.ko
    ```

    - Writing & reading from device file
    ```
    $ echo "<TEXT>" > /dev/<device-file-name>
    $ tail -n 1 /dev/<device-file-name>
    ```

## References
- https://tldp.org/LDP/lkmpg/2.6/html/x569.html
- https://www.linuxsavvy.com/resources/linux/man/man9/get_user.9.html
- https://www.unix.com/man-page/suse/9/alloc_chrdev_region/
- https://elixir.bootlin.com/linux/v6.12.6/C/ident/dev_t
- https://embetronicx.com/tutorials/linux/device-drivers/character-device-driver-major-number-and-minor-number/
