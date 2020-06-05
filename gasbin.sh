#!/bin/bash
riscv64-unknown-elf-as -o $1.o $1
riscv64-unknown-elf-ld -Ttext 0x7C00 -o $1.elf $1.o
riscv64-unknown-elf-objcopy -O binary $1.elf $1.bin
riscv64-unknown-elf-objdump -D -b binary -m riscv $1.bin
