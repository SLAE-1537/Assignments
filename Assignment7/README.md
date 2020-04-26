## Compilation
```
gcc rc4.c -o rc4.o -c
gcc encryptor.c -o encryptor.o -c
gcc decryptor.c -o decryptor.o -c

gcc encryptor.o rc4.o -o encryptor
gcc decryptor.o rc4.o -o decryptor

```

## Usage
### For encryption:
```
./encryptor shellcode.txt key.txt encrypted.txt

```
### For decryption:
```
./decryptor encrypted.txt key.txt decrypted.txt
```
