# Exploring Linux Kernel Programming

Welcome to my project repo.

---

## Intent

I wanted to explore interacting with the Linux Kernel!

## Table of Content
[Background](#background)<br>
[Topics](#topics)<br>
[References](#references)<br>

## Background
What is the Kernel? A simple question but with varying degrees of depth towards an answer.

In my own simple explanation, a kernel allows the user to access underlying hardware through system calls. As an example, I've written high level programs that needed to access files on the system. So the underlying call was ultimately handled by a system call that made an underlying call through the kernel.

The kernel is considered a hardware abstraction layer!
```
Rough Diagram:
--------------
|  user app  |
--------------
|   kernel   |
--------------
|     HW     |
--------------

**NOTE: The OS does make use of the kernel (why do you think in python you can perform os.system calls?)
```

So this was a high level explanation of the usage of a kernel. There are other areas the kernel is involved in such as: process and resource management, process scheduling, etc. But I'll hold off on explaining this for now.

## Topics

## References
- Johannes 4GNU_Linux Youtube channel and Linux Driver series
- https://tldp.org/LDP/lkmpg/2.6/html/index.html
