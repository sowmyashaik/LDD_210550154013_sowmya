##ifneq($(KERNELRELEASE),)
	obj-m:=p1.o
##else 
	KDIR=/lib/modules/$(shell uname -r)/build/
	PWD:=$(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm App1 App2

install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install
        
Application1:
	$(shell make App1)

Application2:
	$(shell make App2)

#endif

