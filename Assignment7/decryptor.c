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
    x = ftell(f);
    *fsize = x;
    fseek (f,0,0);
    data = (unsigned char *) calloc(*fsize+10,sizeof(unsigned char));
    memset (data,0,*fsize+10);
    fread(data,1,*fsize,f);
    fclose (f);
    return data;

}


unsigned char * readEncryptedFile(const char *File,long *fsize)
{
    unsigned char * data;
    long x;

    FILE * f = fopen (File,"rb");
    fseek (f,0,2);
    x =ftell(f);
    *fsize = x;
    fseek (f,0,0);
    data = (unsigned char *) calloc(*fsize+10,sizeof(unsigned char));
    memset (data,0,*fsize+10);
    //fread(data,1,*fsize,f);
    for(int i = 0; i < *fsize-1; i++){
      fscanf(f, "%02hhX", data+i);
    }
    fclose (f);
    return data;
}


void decrypt(const char *encryptedFile, const char  *keyFile, const char *decryptedFile){

    unsigned char * encrypted; // point to read data from the encrypted file
    unsigned char * decrypted; // point to decrypted data
    unsigned char* key; //point to the key
    long eSize, kSize;

    //read plaintext file
    encrypted = readEncryptedFile(encryptedFile, &eSize);

    //allocate memory for encrypted data according to the paintext size
    decrypted = (unsigned char *) calloc(eSize+10,sizeof(unsigned char));
    memset (decrypted,0,eSize+10);

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
    pseudo_random_generation_algorithm(encrypted,eSize/2,decrypted);
    
    //printing decrypted data on console
    printf("%s\n",decrypted);

    //Write data to the file 
    FILE *f = fopen(decryptedFile, "w");
    fwrite(decrypted, 1, eSize/2, f);
    fclose(f);

    //free memory
    free(decrypted);
    free(encrypted);
    free(key);


}


int main(int argc, const char * argv[]) {

    if(argc < 4)
    {
        printf("Usage: \n");
        printf("./decryptor path-to-encrypted-file path-to-key-file path-to-decrypted-file\n");
        return 0;
    }

    const char *encryptedFile = argv[1];
    const char *keyFile = argv[2];
    const char *decryptedFile = argv[3];

    decrypt(encryptedFile, keyFile, decryptedFile);
  
    return 0;
 
}



