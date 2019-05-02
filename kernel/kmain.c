#include <yanix/plat_init.h>
#include <yanix/arch_init.h>
#include <yanix/bootinfo.h>
#include <yanix/kprintf.h>

void kmain(yanix_bootinfo_t bootinfo) {
	arch_init();
	plat_init();
	kprintf("kmain: cmdline=%s\n", bootinfo.cmdline);
	kprintf("kmain: mem_pool at %p, %dkb\n", bootinfo.mem_pool, bootinfo.mem_pool_size/1024);
}
