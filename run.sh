#!/bin/bash
find . -name "*.o" -type f -delete #clean
find . -name "*.bin" -type f -delete
find . -name "*.tmp" -type f -delete

CFiles=`find . -name "*.c" -type f` #get all c files inside kernel

cd ./boot/ #compile asm files
nasm main.asm -f bin -o ../boot_sect.bin

cd .. #compile kernel files
for eachfile in $CFiles
do
    gcc -m32 -w -masm=intel -fno-pie -ffreestanding -c -mgeneral-regs-only $eachfile -o $eachfile.o
done

OFiles=`find . -name "*.o" -type f` #get all o files
OFiles=${OFiles/"./kernel/kernel.c.o"/}
OFiles="./kernel/kernel.c.o ${OFiles}" #force kernel.c.o to be first

ld -m elf_i386 -o ./kernel.bin -Ttext 0xd000 $OFiles --oformat binary #link
cat boot_sect.bin kernel.bin > os-image # make image
echo "the image file size is(in KB. max is ≈64KB):"
stat -c "%s\n" os-image | awk '{ printf "%.2f\n", $1 / 1024 }'
truncate -s 16M os-image #force the image to have enouh bytes, so the read-disk instruction will not overflow.

find . -name "*.o" -type f -delete #clean
find . -name "*.bin" -type f -delete
find . -name "*.tmp" -type f -delete
find . -name "log.txt" -type f -delete
