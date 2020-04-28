##Compilation
###To compile nasm file
```
nasm -f elf32 -o $1.o $1.nasm
ld -m elf_i386 -s -o $1 $1.o
```

###To compile c file:
#### before compiling the c file, read the usage section
```
gcc -m32 -fno-stack-protector -z execstack egghunter.c -o egghunter
```

##Usage
- Extract the hex opcodes from the egghunter using the following command:
```
objdump -d ./egghunter|grep '[0-9a-f]:'|grep -v 'file'|cut -f2 -d:|cut -f1-6 -d' '|tr -s ' '|tr '\t' ' '|sed 's/ $//g'|sed 's/ /\\x/g'|paste -d '' -s |sed 's/^/"/'|sed 's/$/"/g'
```
- Place the extracted hex in the egghunter array of the c file.
- Choose your shellcode and extract its hex opcodes and place it in the egg_code array of the c file
- After compiling the c file run:
```
./egghunter
```
.
