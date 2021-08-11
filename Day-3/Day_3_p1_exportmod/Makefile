##ifneq($(KERNELRELEASE).)
	obj-m:=Avg.o Add.o #./Avg/Avg.o
##else	
	KDIR=/lib/modules/5.10.52-v7l+/build/
	PWD:=$(shell pwd)
	
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf /lib/modules/$(shell uname -r)/extra/*
#endif

install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install
	depmod -a
