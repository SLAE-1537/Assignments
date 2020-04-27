## Compilation
### to compile nasm file, use the following command
```
./compile.sh bind-shell
```

### to compile the c file, use the following command
```
gcc -m32 -fno-stack-protector -z execstack bind-tcp-shell.c -o bind-tcp-shell
```

## Usage
### for compiled nasm file:
 ```
 ./bin-shell
 ```
 
 ### for compiled c file
 ```
 ./bind-tcp-shell port-number
 ```
