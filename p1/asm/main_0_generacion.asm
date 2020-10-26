segment .data
	_msg_div_err db 'err: division by 0',0
	_msg_segment_err db 'err: segment out of range',0
segment .bss
	_msg_fail_err resd 1
	__esp resd 1
	_x resd 1
	_y resd 1
	_z resd 1
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float
main:
	mov dword [__esp], esp
	push dword 8
	pop dword eax
	mov dword [_x], eax
	push dword _y
	call scan_int
	add esp, 4
	push dword _y
	push dword _x
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	mov dword ebx, [ebx]
	add eax, ebx
	push dword eax
	pop dword eax
	mov dword [_z], eax
	push dword _z
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	call print_endofline
	add esp, 4
	jmp __end
__failed:
	push dword [_msg_fail_err]
	call print_string
	add esp, 4
	call print_endofline
__end:
	mov dword esp, [__esp]
	ret
