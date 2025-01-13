# this is the name of target object file
obj-m += dev_nr.o

# name of executable file for test
EXEC_NAME = test

#execute the makefile for the corresponding kernel
#shell uname -r => returns the kernel name
#modules => that you're building a module?
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o ${EXEC_NAME} ${EXEC_NAME}.c

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f ${EXEC_NAME}
