#!/bin/bash
find . -name "*.o" -type f -delete #clean
find . -name "*.bin" -type f -delete

cd ./kernel
CFiles=`find . -name "*.c" -type f` #get all c files

cd ../boot #compile asm files
nasm main.asm -f bin -o ../boot_sect.bin

cd ../kernel #compile kernel files
for eachfile in $CFiles
do
    gcc -m32 -masm=intel -fno-pie -ffreestanding -c $eachfile -o $eachfile.o
done

OFiles=`find . -name "*.o" -type f` #get all o files
OFiles=${OFiles/"./kernel.c.o"/}
OFiles="./kernel.c.o ${OFiles}" #force kernek.c.o to be first

ld -m elf_i386 -o ../kernel.bin -Ttext 0x1000 $OFiles --oformat binary #link

cd ..
cat boot_sect.bin kernel.bin > os-image # make image

find . -name "*.o" -type f -delete #clean
find . -name "*.bin" -type f -delete