segment .data
	_msg_div_err db 'err: division by 0',0
	_msg_segment_err db 'err: segment out of range',0
segment .bss
	_msg_fail_err resd 1
	__esp resd 1
	_b1 resd 1
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float
main:
	mov dword [__esp], esp
	push dword _b1
	call scan_boolean
	add esp, 4
	push dword _b1
	pop dword eax
	mov dword eax, [eax]
	sub eax, 1
	neg eax
	push dword eax
	pop dword eax
	push dword eax
	call print_boolean
	call print_endofline
	add esp, 4
	push dword _b1
	pop dword eax
	mov dword eax, [eax]
	sub eax, 1
	neg eax
	push dword eax
	pop dword eax
	sub eax, 1
	neg eax
	push dword eax
	pop dword eax
	push dword eax
	call print_boolean
	call print_endofline
	add esp, 4
__end:
	mov dword esp, [__esp]
	ret
__failed:
	push dword [_msg_fail_err]
	call print_string
	add esp, 4
	call print_endofline
	jmp __end
__check_idx:
	cmp eax, edx
	jb __idx_vector_ok
	mov edx, _msg_div_err
	mov [_msg_segment_err], edx
	mov edx, 1
	jmp __check_idx_end
__idx_vector_ok:
	mov edx, 0
__check_idx_end:
	ret
