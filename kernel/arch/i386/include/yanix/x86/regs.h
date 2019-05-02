#pragma once

typedef struct x86_regs_t {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t interrupt_num, error_code;
  uint32_t eip, cs, eflags, useresp, ss;
} x86_regs_t;

typedef struct x86_regs_t regs_t;
