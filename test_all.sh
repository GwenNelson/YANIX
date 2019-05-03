#!/bin/sh
make clean && \
make CONFIG=configs/hosted.conf && \
./sysroot/boot/kernel.elf && \
make clean && \
make CONFIG=configs/i386-pc.conf run-qemu-tests && \
make clean && \
make CONFIG=configs/raspi2.conf run-qemu-tests
