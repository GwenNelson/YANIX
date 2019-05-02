ARCH_KERNEL_OBJS=$(SRCROOT)/kernel/arch/i386/arch_init.o
ARCH_KERNEL_CPPFLAGS=-I$(SRCROOT)/kernel/arch/i386/include

include $(SRCROOT)/kernel/arch/x86/rules.mk
