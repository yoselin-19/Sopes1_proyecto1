obj-m += memo_201403819_201403862.o
obj-m += cpu_201403819_201403862.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
