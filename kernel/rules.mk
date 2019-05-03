include $(SRCROOT)/kernel/arch/$(ARCH)/rules.mk
include $(SRCROOT)/kernel/sysinit/rules.mk
include $(SRCROOT)/kernel/plat/$(PLAT)/rules.mk
include $(SRCROOT)/kernel/lib/rules.mk

KERNEL_OBJS=\
	$(KERNEL_LIB_OBJS)\
	$(ARCH_KERNEL_OBJS)\
	$(PLAT_KERNEL_OBJS)\
	$(SYSINIT_KERNEL_OBJS)\
	$(SRCROOT)/kernel/dummy_mod.o\
	$(SRCROOT)/kernel/kprintf.o\
	$(SRCROOT)/kernel/kmain.o\
	$(SRCROOT)/kernel/pmm.o

TEST_OBJS=\
	$(SRCROOT)/kernel/run_tests.o

ifeq ($(ARCH),hosted)
	KERNEL_LIBS=
else
	KERNEL_LIBS=-nostdlib -lgcc
endif
KERNEL_CPP_FLAGS:=-I$(SRCROOT)/kernel/include $(ARCH_KERNEL_CPPFLAGS)
KERNEL_C_FLAGS:=$(ARCH_KERNEL_CFLAGS)

ifeq ($(ARCH),hosted)
	KERNEL_BUILD=$(CC) -o $@ $(CFLAGS) $(KERNEL_C_FLAGS) $(LDFLAGS) $(KERNEL_OBJS) $(KERNEL_LIBS)
else
	KERNEL_BUILD=$(CC) -T $(SRCROOT)/kernel/arch/$(ARCH)/linker.ld -o $@ $(CFLAGS) $(KERNEL_C_FLAGS) $(LDFLAGS) $(KERNEL_OBJS) $(KERNEL_LIBS)
endif


$(SYSROOT)/boot/kernel.elf: $(KERNEL_OBJS)
	mkdir -p $(SYSROOT)/boot
	$(KERNEL_BUILD)

$(SYSROOT)/boot/test-kernel.elf: $(KERNEL_OBJS) $(TEST_OBJS) 
	$(KERNEL_BUILD) $(TEST_OBJS)

%.o: %.c
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS) $(KERNEL_CPP_FLAGS)

%.o: %.s
	$(AS) -c $< -o $@	

