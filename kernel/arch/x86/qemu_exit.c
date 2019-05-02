#include <yanix/x86/portio.h>

#define QEMU_EXIT_SUCCESS 0x00
#define QEMU_EXIT_FAILED  0x01
#define QEMU_EXIT_PORT    0x501

void qemu_exit_fail() {
	outb(QEMU_EXIT_PORT,QEMU_EXIT_FAILED);
}

void qemu_exit_ok() {
	outb(QEMU_EXIT_PORT,QEMU_EXIT_SUCCESS);
}
