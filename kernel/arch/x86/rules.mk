ARCH_KERNEL_OBJS:=\
	$(ARCH_KERNEL_OBJS)\
	$(SRCROOT)/kernel/arch/x86/portio.o\
	$(SRCROOT)/kernel/arch/x86/qemu_exit.o

ARCH_KERNEL_CPPFLAGS:=$(ARCH_KERNEL_CPPFLAGS) -I$(SRCROOT)/kernel/arch/x86/include
