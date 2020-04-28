
##Compilation
2
###To compile nasm file:
3
```
4
​nasm -f elf32 -o $1.o $1.nasm
ld -m elf_i386 -s -o $1 $1.o
5
```
6
​
7
###To compile c file:
#### before compiling the c file, read the usage section
8
```
9
​gcc -m32 -fno-stack-protector -z execstack egghunter.c -o egghunter
10
```
11
​
12
##Usage
13
- Extract the hex opcodes from the egghunter using the following command:
14
```
15
objdump -d ./egghunter|grep '[0-9a-f]:'|grep -v 'file'|cut -f2 -d:|cut -f1-6 -d' '|tr -s ' '|tr '\t' ' '|sed 's/ $//g'|sed 's/ /\\x/g'|paste -d '' -s |sed 's/^/"/'|sed 's/$/"/g'
16
```
17
- Place the extracted hex in the egghunter array of the c file.
18
- Choose your shellcode and extract its hex opcodes and place it in the egg_code array of the c file
19
- After compiling the c file run:
20
```
21
./egghunter
22
```
