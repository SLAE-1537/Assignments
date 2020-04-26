/*
This code has been created for completing the requirements of the x86 Assembly Language and Shellcoding course.

Student ID: SLAE-1537
*/
#include "rc4.h"


unsigned char S[256];  //A permutation of all 256 possible bytes

// This function used to generate the permutation array S
void key_scheduling_algorithm(unsigned char* key, long kLength){

    unsigned char  tmp;    //for swaping
    int j = 0;
   
    // initialize the permutation array (S)
    for(int i = 0 ; i < 256 ; i++)
    {
        S[i] = i;

    }
    // process S for 256 iterations
    for(int i = 0 ; i < 256; i++)
    {
        j = ( j + S[i] + key[i % kLength] ) % 256;
        
        //Swap S[i] & S[j]
        tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
    }

}

void pseudo_random_generation_algorithm(unsigned char* data,long dLength,unsigned char* result){

    unsigned char  tmp;    //for swaping
    int i = 0, j = 0, k = 0; 

    for(int x = 0 ; x< dLength ; x++)
    {
        i = (i + 1) % 256; 
        j = (j + S[i]) % 256; 
        
        //Swap S[i] & S[j]
        tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
        
        k = (S[i] + S[j]) % 256;

        result[x]= data[x]^S[k];
    }
}

    

