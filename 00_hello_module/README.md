# Hello Kernel

A "Hello World" kernel module to get me familiar with:
- Writing a .c file and compiling that into a .ko (kernel module) file
- Loading and unloading the module with the usage of insmod and rmmod
- Using dmesg to view the logs

---

## Table of Content
[Prereqs](#prereqs)<br>
[Building](#building)<br>
[Executing](#executing)<br>
[References](#references)<br>

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

    ```
    $ sudo insmod <module>.ko
    $ sudo rmmod <module>.ko
    ```

## References
