#include <stddef.h>
#include <stdint.h>
#include <yanix/kmain.h>
#include <yanix/memlayout.h>

extern uintptr_t __start;
extern uintptr_t __end;
void sysinit_arch(uint32_t r0, uint32_t r1, uint32_t atags) {
	yanix_bootinfo_t bootinfo;
	bootinfo.mem_pool=&__end;
	bootinfo.mem_pool_size=MAX_PHYS_RAM - (&__end - &__start);
	kmain(bootinfo);
}
