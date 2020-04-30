/*
This code has been created for completing the requirements of the SecurityTube Linux Assembly Expert certification:
  	
http://securitytube-training.com/online-courses/securitytube-linux-assembly-expert/  

Student ID: SLAE-1537
*/

#ifndef rc4_h
#define rc4_h
#include <stdio.h>

void key_scheduling_algorithm(unsigned char* key, long kLength);

void pseudo_random_generation_algorithm(unsigned char* data,long dLength,unsigned char* result);

#endif
