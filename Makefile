obj-m += mytime.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
load:
	insmod ./mytime.ko
unload:
	rmmod ./mytime.ko
