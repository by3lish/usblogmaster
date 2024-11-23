# Makefile for building USB logger module

obj-m += usb_logger.o

# Specify the kernel source directory
KDIR ?= /lib/modules/$(shell uname -r)/build

# Specify the path to the kernel modules directory
PWD := $(shell pwd)

# Default target to build the module
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Target to clean build files
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

# Install the module (requires root)
install:
	sudo insmod usb_logger.ko

# Uninstall the module (requires root)
uninstall:
	sudo rmmod usb_logger
