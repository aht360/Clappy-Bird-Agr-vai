section .text
global bzzr

bzzr:
	enter 0, 0
	mov eax, 101
	mov ebx, 0x42
	mov ecx, 0x20
	mov edx, 3
	int 0x80

	mov al, 182 
	out 43h, al

	mov eax, [ebp + 8]
	cmp eax, 0
	je .end
	out 42h, al
	mov al, ah
	out 42h, al

	in al,61h
	or al, 00000011b
	out 61h, al

	mov bx, 500

	.pause1:
		mov cx, 65535
	.pause2:
		dec cx
		jne .pause2
		dec bx
		jne .pause1
		in al, 61h;
		and al, 11111100b
		out 61h, al

	.end:
	leave
	ret