	push dword 3
segment .data
	_msg_div_err db 'err: division by 0',0
	_msg_segment_err db 'err: segment out of range',0
segment .bss
	_msg_fail_err resd 1
	__esp resd 1
	_vector1 resd 3
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float
main:
	mov dword [__esp], esp
	push dword 0
	pop eax
	mov edx, 3
	call __check_idx
	cmp edx, 1
	je __failed
	mov edx, 4
	imul edx
	add eax, _vector1
	mov dword edx, dword eax
	push edx
	push dword 10
	pop dword eax
	pop dword ebx
	mov dword [ebx], dword eax
	push dword 1
	pop eax
	mov edx, 3
	call __check_idx
	cmp edx, 1
	je __failed
	mov edx, 4
	imul edx
	add eax, _vector1
	mov dword edx, dword eax
	push edx
	push dword 20
	pop dword eax
	pop dword ebx
	mov dword [ebx], dword eax
	push dword 2
	pop eax
	mov edx, 3
	call __check_idx
	cmp edx, 1
	je __failed
	mov edx, 4
	imul edx
	add eax, _vector1
	mov dword edx, dword eax
	push edx
	push dword 30
	pop dword eax
	pop dword ebx
	mov dword [ebx], dword eax
	push dword 0
	pop eax
	mov edx, 3
	call __check_idx
	cmp edx, 1
	je __failed
	mov edx, 4
	imul edx
	add eax, _vector1
	mov dword edx, dword eax
	push edx
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	call print_endofline
	add esp, 4
	push dword 1
	pop eax
	mov edx, 3
	call __check_idx
	cmp edx, 1
	je __failed
	mov edx, 4
	imul edx
	add eax, _vector1
	mov dword edx, dword eax
	push edx
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	call print_endofline
	add esp, 4
	push dword 2
	pop eax
	mov edx, 3
	call __check_idx
	cmp edx, 1
	je __failed
	mov edx, 4
	imul edx
	add eax, _vector1
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
__check_div:
	cmp ecx, 0
	jne __div_ok
	mov ebx, _msg_div_err
	mov [_msg_fail_err], ebx
	mov ebx, 1
	jmp __check_div_end
__div_ok:
	mov ebx, 0
__check_div_end:
	ret
__check_idx:
	cmp eax, edx
	jl __idx_vector_p_ok
__idx_vector_err:
	mov edx, _msg_segment_err
	mov [_msg_fail_err], edx
	mov edx, 1
	jmp __check_idx_end
__idx_vector_p_ok:
	cmp eax, 0
	jl __idx_vector_err
	mov edx, 0
__check_idx_end:
	ret
