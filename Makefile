DMESG_OUTPUT := $(shell dmesg | grep -iq 'AMD Memory Encryption Features active: SEV' && echo 1 || echo 0)

ifeq ($(DMESG_OUTPUT),1)
SRC := ivshmem_uio-sev.c
else
SRC := ivshmem_uio.c
endif

ivshmem_uio-objs := $(SRC:.c=.o)
obj-m := ivshmem_uio.o

KDIR  := /lib/modules/$(shell uname -r)/build
PWD   := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.ko *.o ivshmem_uio.mod.c Module.symvers
