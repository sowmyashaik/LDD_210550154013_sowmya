obj-m:=hello.o
CROSS_COMPILE_KDIR=/lib/modules/$(shell uname -r)/build/
all:
	make -C $(CROSS_COMPILE_KDIR) M=$(PWD) modules

clean:
	make -C $(CROSS_COMPILE_KDIR) M=$(PWD) clean
