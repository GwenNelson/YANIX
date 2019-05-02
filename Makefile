.PHONY: all clean run-qemu
.DEFAULT_GOAL := all
.SUFFIXES: .o .c .s

include make.conf

include kernel/rules.mk

all: $(SYSROOT)/boot/kernel.elf

clean:
	find . -name *.o | xargs -n 1 rm
	find . -name *.elf | xargs -n 1 rm
	find . -name *.d | xargs -n 1 rm
	rm -rf sysroot

run-qemu: all
	qemu-system-$(ARCH) -kernel sysroot/boot/kernel.elf -serial mon:stdio -m 4G

