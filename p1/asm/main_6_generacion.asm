segment .data
	_msg_div_err db 'err: division by 0',0
	_msg_segment_err db 'err: segment out of range',0
segment .bss
	_msg_fail_err resd 1
	__esp resd 1
	_m resd 1
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float
main:
	mov dword [__esp], esp
	push dword 0
	pop dword eax
	mov dword [_m], eax
	push dword _m
	push dword 5
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jg _jg_if_1
	jmp _jg_else_1
_jg_if_1:
	push dword 1
	jmp _jg_fi_1
_jg_else_1:
	push dword 0
_jg_fi_1:
	pop dword eax
	cmp eax, 0
	je near _else_1
	push dword 2
	pop dword eax
	push dword eax
	call print_int
	call print_endofline
	add esp, 4
	jmp near _fi_1
_else_1:
	push dword 3
	pop dword eax
	push dword eax
	call print_int
	call print_endofline
	add esp, 4
_fi_1:
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
	jl __idx_vector_ok
	mov edx, _msg_segment_err
	mov [_msg_fail_err], edx
	mov edx, 1
	jmp __check_idx_end
__idx_vector_ok:
	mov edx, 0
__check_idx_end:
	ret
