#!/bin/bash

echo '[+] Assembling with Nasm ... '
nasm -f elf32 -F dwarf -g -o $1.o $1.nasm

echo '[+] Linking ...'
#ld -z execstack -o $1 $1.o
#ld -m elf_i386 -s -o execve2-stack execve2-stack.o
ld -N -m elf_i386 -z execstack -o $1 $1.o

echo '[+] Done!'



