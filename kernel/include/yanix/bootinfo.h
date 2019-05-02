#pragma once

#include <stddef.h>
#include <stdint.h>

// this struct is filled out by sysinit before being passed to kmain
typedef struct yanix_bootinfo_t {
	char cmdline[1024];
	uintptr_t mem_pool;   // a pointer to the start of free physical memory
	size_t mem_pool_size; // the size of free memory
} yanix_bootinfo_t;
