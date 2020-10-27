segment .data
	_msg_div_err db 'err: division by 0',0
	_msg_segment_err db 'err: segment out of range',0
segment .bss
	_msg_fail_err resd 1
	__esp resd 1
	_x resd 5
	_y resd 1
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float
main:
	mov dword [__esp], esp
	push dword 8
	pop dword eax
	mov dword [_y], eax
	push dword _y
	push dword 2
	pop eax
	mov edx, 5
	call __check_idx
	cmp edx, 1
	je __failed
	mov edx, 4
	imul edx
	add eax, _x
	mov dword edx, dword eax
	push edx
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	mov dword [ebx], dword eax
	push dword 2
	pop eax
	mov edx, 5
	call __check_idx
	cmp edx, 1
	je __failed
	mov edx, 4
	imul edx
	add eax, _x
	mov dword edx, dword eax
	push edx
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
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
	jl __idx_vector_ok
	mov edx, _msg_segment_err
	mov [_msg_fail_err], edx
	mov edx, 1
	jmp __check_idx_end
__idx_vector_ok:
	mov edx, 0
__check_idx_end:
	ret
