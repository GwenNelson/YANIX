.global gdt_flush

gdt_flush:
	movl 4(%esp), %eax
	lgdt (%eax)        // Load the new GDT pointer

	mov $0x10, %ax      // 0x10 is the offset in the GDT to our data segment
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	jmp $0x08,$.flush

.flush:
   ret
