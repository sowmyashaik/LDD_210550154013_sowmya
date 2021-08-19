##ifneq($(KERNELRELEASE),)
        obj-m:=2_IOCTL.o
##else
	KDIR=/lib/modules/$(shell uname -r)/build/
	PWD:=$(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc -o writeApp writeApp.c
	gcc -o readApp readApp.c
	gcc -o ioctlApp ioctlApp.c

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm writeApp readApp ioctlApp

install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install

#endif

