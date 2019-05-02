ARCH_KERNEL_OBJS=\
	$(SRCROOT)/kernel/arch/arm/arch_init.o\
	$(SRCROOT)/kernel/arch/arm/qemu_exit.o

ARCH_KERNEL_CFLAGS=-mcpu=arm1176jzf-s -fpic
ARCH_KERNEL_CPPFLAGS=-I$(SRCROOT)/kernel/arch/arm/include
