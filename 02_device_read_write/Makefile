# this is the name of target object file
obj-m += read_n_write.o

#execute the makefile for the corresponding kernel
#shell uname -r => returns the kernel name
#modules => that you're building a module?
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
