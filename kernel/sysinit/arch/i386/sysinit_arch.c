#include <yanix/multiboot.h>
#include <yanix/kmain.h>
#include <yanix/memlayout.h>
#include <yanix/bootinfo.h>
#include <yanix/kprintf.h> // for snprintf etc

#define CHECK_FLAG(flags,mask)   ((flags) & mask)

extern char* _kernel_start;
extern char* _kernel_end;

void sysinit_arch(struct multiboot_info *mboot_ptr) {
	yanix_bootinfo_t bootinfo;
	if(CHECK_FLAG(mboot_ptr->flags, MULTIBOOT_INFO_CMDLINE)) {
		snprintf(bootinfo.cmdline,1024,"%s",(char*)(mboot_ptr->cmdline + KERN_BASE));
	} else {
		snprintf(bootinfo.cmdline,1024,"");
	}

	bootinfo.mem_pool      = (uintptr_t)&_kernel_end - KERN_BASE;
	bootinfo.mem_pool_size = (size_t)mboot_ptr->mem_upper - ((&_kernel_end - &_kernel_start) - KERN_BASE);
	
	kmain(bootinfo);
	for(;;) asm volatile("cli; hlt"); // loop forever
}
