.PHONY: all clean run-qemu run-qemu-tests tests
.DEFAULT_GOAL := all
.SUFFIXES: .o .c .s .S

FILENAME:=$(lastword $(MAKEFILE_LIST))
SRCROOT:=$(realpath $(dir $(FILENAME)))
SYSROOT:=$(SRCROOT)/sysroot

ifndef $(CONFIG)
	CONFIG:=$(SRCROOT)/configs/i386-pc.conf
endif

include $(CONFIG)

include kernel/rules.mk

all: $(SYSROOT)/boot/kernel.elf

tests: all $(SYSROOT)/boot/test-kernel.elf

clean:
	find . -name *.o | xargs -n 1 rm
	find . -name *.elf | xargs -n 1 rm
	find . -name *.d | xargs -n 1 rm
	rm -rf sysroot

run-qemu: all
	$(QEMU_CMD) -kernel $(SYSROOT)/boot/kernel.elf 

run-qemu-tests: tests
	$(QEMU_CMD) $(QEMU_TEST_FLAGS) -kernel $(SYSROOT)/boot/test-kernel.elf;\
		if [ $$? -eq 1 ]; then \
			exit 0; \
		else \
			exit 1; \
		fi;
