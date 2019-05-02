#include <stddef.h>
#include <stdint.h>
#include <yanix/kmain.h>

void sysinit_arch(uint32_t r0, uint32_t r1, uint32_t atags) {
	yanix_bootinfo_t bootinfo;
	kmain(bootinfo);
}
