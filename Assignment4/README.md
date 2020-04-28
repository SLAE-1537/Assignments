##Compiling
###To compile nasm file:
```
./compile.sh decoder
```

##Usage
- first extract the hex opcode of your shellcode and place it in the shellcode array in the encoder.py
- run the encoder.
- copy the decoded hex opcodes and place it in the shellcode section in the decoder.nasm file.
- compile decoder.nasm and run it.
