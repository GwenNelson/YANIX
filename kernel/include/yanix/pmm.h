#pragma once

#include <stddef.h>
#include <stdint.h>

#include <yanix/memlayout.h>

void init_pmm(uintptr_t mem_pool_start, size_t mem_pool_size);
size_t get_free_mem();
uintptr_t alloc_page();
void free_page(uintptr_t p);
