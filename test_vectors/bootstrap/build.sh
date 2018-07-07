riscv64-unknown-elf-gcc -march=rv64imafd -mcmodel=medany -fomit-frame-pointer -fno-strict-aliasing -fno-builtin -c -o output.o output.s
riscv64-unknown-elf-ld output.o -T link.ld -o output.riscv
