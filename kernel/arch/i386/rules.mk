ARCH_KERNEL_OBJS=$(SRCROOT)/kernel/arch/i386/arch_init.o\
		 $(SRCROOT)/kernel/arch/i386/gdt.o\
		 $(SRCROOT)/kernel/arch/i386/gdt_flush.o\
		 $(SRCROOT)/kernel/arch/i386/tss_flush.o

ARCH_KERNEL_CPPFLAGS=-I$(SRCROOT)/kernel/arch/i386/include

include $(SRCROOT)/kernel/arch/x86/rules.mk
