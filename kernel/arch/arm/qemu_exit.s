.global qemu_exit_ok
.global qemu_exit_fail

qemu_exit_fail:
	mov r0, #0x18		// ADP
	ldr r1, =0x20026 	// ADP_Stopped_ApplicationExit
	svc #0x123456

qemu_exit_ok:
	mov r0, #0x18
	ldr r1, =0x1337
	svc #0x123456
