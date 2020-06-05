
# Making Instructions

int add and float add


# Usage

## macOS

brew tap riscv/riscv
brew install riscv-tools
brew install libisl
export PATH=$PATH:/usr/local/Cellar/riscv-gnu-toolchain/gnu/lib
cmake -DCMAKE_TOOLCHAIN_FILE=cmake_brew_riscv.cmake .

### Fix issue libisl

install_name_tool -change '/usr/local/opt/isl/lib/libisl.19.dylib' /usr/local/opt/isl/lib/libisl.dylib /usr/local/Cellar/riscv-gnu-toolchain/gnu/libexec/gcc/riscv64-unknown-elf/8.2.0/cc1
install_name_tool -change '/usr/local/opt/isl/lib/libisl.19.dylib' /usr/local/opt/isl/lib/libisl.dylib /usr/local/Cellar/riscv-gnu-toolchain/gnu/libexec/gcc/riscv64-unknown-elf/8.2.0/cc1plus

# Build TinyEMU
## Download

https://github.com/fernandotcl/TinyEMU

https://bellard.org/tinyemu/diskimage-linux-riscv-2018-09-23.tar.gz

## Patch

## Build

modify Makefile

## Run

https://bellard.org/jslinux/buildroot-riscv64.cfg

# Extra

encode_riscv.py encodes instruction in Python

gasbin.sh emits bin from tools
	requires in the path: riscv64-unknown-elf-*
	e.g. macOS /usr/local/Cellar/riscv-gnu-toolchain/gnu/bin/

# Resources 

https://content.riscv.org/wp-content/uploads/2019/06/riscv-spec.pdf
https://github.com/riscv/riscv-opcodes


# New Instruction (TBD)

We add Quad (see 13.3 Quad-Precision Convert and Move Instructions) and https://github.com/riscv/riscv-opcodes/blob/master/opcodes-rv64q

fcvt.w.s  rd rs1 24..20=0 31..27=0x18 rm       26..25=0 6..2=0x14 1..0=3
fcvt.l.q  rd rs1 24..20=2 31..27=0x18 rm       26..25=3 6..2=0x14 1..0=3
...

Typical location of rs2 is bit2 

opcode is = (0x14<<2)|3 = 0x53

## Patching TinyEmu

FP (0x53) is managed in riscv_cpu_fp_template.h with decoding
	imm = insn >> 25;
	rm = (insn >> 12) & 7;  // rounding mode, tinyemu supports 0..4 7

The inm is ored with the size in 25..26 (0=32,1=64,3=128), so we look for 0x18

Then rs2 contains the type and we can add #6

