segment .data
	_msg_div_err db 'err: division by 0',0
	_msg_segment_err db 'err: segment out of range',0
segment .bss
	_msg_fail_err resd 1
	__esp resd 1
	_b1 resd 1
	_x resd 1
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
	push dword _x
	call scan_int
	add esp, 4
	push dword _x
	push dword 3
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jg _jg_if_0
	jmp _jg_else_0
_jg_if_0:
	push dword 1
	jmp _jg_fi_0
_jg_else_0:
	push dword 0
_jg_fi_0:
	pop dword eax
	push dword eax
	call print_boolean
	call print_endofline
	add esp, 4
	push dword _x
	push dword 3
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jge _jge_if_1
	jmp _jge_else_1
_jge_if_1:
	push dword 1
	jmp _jge_fi_1
_jge_else_1:
	push dword 0
_jge_fi_1:
	pop dword eax
	push dword eax
	call print_boolean
	call print_endofline
	add esp, 4
	push dword _x
	push dword 3
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jl _jl_if_2
	jmp _jl_else_2
_jl_if_2:
	push dword 1
	jmp _jl_fi_2
_jl_else_2:
	push dword 0
_jl_fi_2:
	pop dword eax
	push dword eax
	call print_boolean
	call print_endofline
	add esp, 4
	push dword _x
	push dword 3
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jle _jle_if_3
	jmp _jle_else_3
_jle_if_3:
	push dword 1
	jmp _jle_fi_3
_jle_else_3:
	push dword 0
_jle_fi_3:
	pop dword eax
	push dword eax
	call print_boolean
	call print_endofline
	add esp, 4
	push dword _x
	push dword 3
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	je _je_if_4
	jmp _je_else_4
_je_if_4:
	push dword 1
	jmp _je_fi_4
_je_else_4:
	push dword 0
_je_fi_4:
	pop dword eax
	push dword eax
	call print_boolean
	call print_endofline
	add esp, 4
	push dword _x
	push dword 3
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jne _jne_if_5
	jmp _jne_else_5
_jne_if_5:
	push dword 1
	jmp _jne_fi_5
_jne_else_5:
	push dword 0
_jne_fi_5:
	pop dword eax
	push dword eax
	call print_boolean
	call print_endofline
	add esp, 4
	push dword _b1
	push dword 0
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	and eax, ebx
	push dword eax
	pop dword eax
	push dword eax
	call print_boolean
	call print_endofline
	add esp, 4
	push dword _b1
	push dword 1
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	or eax, ebx
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
	jl __idx_vector_ok
	mov edx, _msg_segment_err
	mov [_msg_fail_err], edx
	mov edx, 1
	jmp __check_idx_end
__idx_vector_ok:
	mov edx, 0
__check_idx_end:
	ret
