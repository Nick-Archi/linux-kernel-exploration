# Device Numbers and Files 

## Table of Content
[Introduction](#introduction)<br>
[Objective](#objective)<br>
[Prereqs](#prereqs)<br>
[Building](#building)<br>
[Executing](#executing)<br>
[References](#references)<br>

## Introduction
Devices are connected to the Linux Kernel at /dev. To interact with these devices, a kernel module is usually loaded.

```
Snippet Call:

$ ls /dev/
autofs         input         ram1    tty13  tty39  tty7       vcsm-cma
block          kmsg          ram10   tty14  tty4   tty8       vcsu
```

So what if you had a theoretical device and you wanted to interface with? How would this be achieved? You would have to essentially create a kernel module and register this so that user applications can have an interface.


```
Rough Illustration:
---------------          --------------          ---------------
|  theor. HW  |   <->    |  dev_file  |   <->    |   user_app  |   
---------------          --------------          ---------------
```

---

## Objective
- create a kernel module and register this with the kernel
- create a sample user space application that will interface with the .ko 

## Prereqs
- Everything should already be installed on your Linux machine (make, insmod, rmmod)...but just in case

```
Find out Kernel Version:
$ uname -r

Update Packages:
$ sudo apt update && sudo apt upgrade -y

Install Kernel Headers:
$ sudo apt install -y raspberrypi-kernel-headers

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

    - Creating a char unbuffered device file
    ```
    $ sudo mknod /dev/<device_file_name> c <kernel_module_major_num> <minor_num>
    ex) $ sudo mknod /dev/chardev c 90 0
    $ sudo chmod 666 /dev/chardev #change file permissions
    ```

    - Build & Execute Sample User Space Application
    ```
    $ gcc <user_c_file> -c <executable_name>
    ex) gcc test.c -c test
    ```

    - Remove Device File from /dev
    ```
    $ sudo rm /dev/<device_file_name>
    ```

## References
- https://tldp.org/LDP/lkmpg/2.6/html/x569.html
