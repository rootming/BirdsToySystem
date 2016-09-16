obj-m := secbulk.o
KDIR := /lib/modules/`uname -r`/build
PWD  := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	rm -rf *.order *.symvers
