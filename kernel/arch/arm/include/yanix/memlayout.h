#pragma once

#define PAGESIZE 0x1000

#define MAX_PHYS_RAM 0x10000000  // 256mb

#define MAX_PAGES (MAX_PHYS_RAM/PAGESIZE)

#define KERN_BASE 0x0
