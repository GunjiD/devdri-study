obj-m := helloworld.o

all:
	make -C /lib/modules/5.4.0-52-generic/build M=$(PWD) modules