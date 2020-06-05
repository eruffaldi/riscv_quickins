set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv)

#set(CMAKE_SYSROOT /home/devel/rasp-pi-rootfs)
#set(CMAKE_STAGING_PREFIX /home/devel/stage)
set(triple rsicv-unknown-elf)

set(ENV{PATH} ENV{PATH} /usr/local/Cellar/riscv-gnu-toolchain/gnu/lib)
set(tools /usr/local/Cellar/riscv-gnu-toolchain/gnu)
set(CMAKE_C_COMPILER ${tools}/bin/riscv64-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/riscv64-unknown-elf-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)