/*
This code has been created for completing the requirements of the SecurityTube Linux Assembly Expert certification:
  	
http://securitytube-training.com/online-courses/securitytube-linux-assembly-expert/  

Student ID: SLAE-1537
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "rc4.h"

unsigned char * readFile(const char *File,long *fsize){

    unsigned char * data;
    long x;

    FILE * f = fopen (File,"rb");
    fseek (f,0,2);
    x =ftell(f);
    *fsize = x;
    fseek (f,0,0);
    data = (unsigned char *) calloc(*fsize+10,sizeof(unsigned char));
    memset (data,0,*fsize+10);
    fread(data,1,*fsize,f);
    fclose (f);
    return data;

}

//encrypt plaintext and store the result in the decrypted file
void encrypt(const char *plainTextFile, const char  *keyFile, const char *encryptedFile){

    unsigned char * data; // point to read data from the plaintext
    unsigned char * encrypted; // point to encrypted data
    unsigned char* key; //point to the key
    long pSize, kSize;

    //read plaintext file
    data = readFile(plainTextFile, &pSize);

    //allocate memory for encrypted data according to the paintext size
    encrypted = (unsigned char *) calloc(pSize+10,sizeof(unsigned char));
    memset (encrypted,0,pSize+10);

    //read key from key file
    key = readFile(keyFile, &kSize);

    if(kSize > 256) // in RC4 key must be less than or equal to 256 byte
    {
        printf("Key length in RC4 must be less than or equal to 256 byte\n");
        exit(0);
    }

    //call KSA function to generate the permutation array
    key_scheduling_algorithm(key, kSize);

    //call PRGA function to do the encryption
    pseudo_random_generation_algorithm(data,pSize,encrypted);


   //printing encryption result in hex
    for (int i = 0 ; i < pSize-1;i++)
    {
        printf("%02hhX",encrypted[i]);
    }
    printf("\n");
    
    //Write encrypted data to the encryptedFile 
    FILE *f = fopen(encryptedFile, "w");
    for(int i = 0; i < pSize-1; i++){
      fprintf(f, "%02hhX", encrypted[i]);
    }
    fclose(f);
    
    //free memory
    free (data);
    free (encrypted);
    free (key);

}


int main(int argc, const char * argv[]) {

    if(argc < 4)
    {
        printf("Usage: \n");
        printf("./encryptor path-to-plaintext-file path-to-key-file path-to-encrypted-file\n");
        return 0;
    }

    const char *plainTextFile = argv[1];
    const char *keyFile = argv[2];
    const char *encryptedFile = argv[3];

    encrypt(plainTextFile, keyFile, encryptedFile);
  
    return 0;
 
}
