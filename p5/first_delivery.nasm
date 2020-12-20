segment .data
	_msg_div_err db 'err: division by 0',0
	_msg_segment_err db 'err: segment out of range',0
segment .bss
	_msg_fail_err resd 1
	__esp resd 1
	_x resd 1
	_resultado resd 1
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float
_fibonacci:
	push ebp
	mov ebp, esp
	sub esp, 8
	mov edx, 1
	sub edx, 0
	inc edx
	lea eax, [ebp + edx*4]
	push dword eax
	push dword 0
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	je _je_if_0
	jmp _je_else_0
_je_if_0:
	push dword 1
	jmp _je_fi_0
_je_else_0:
	push dword 0
_je_fi_0:
	pop dword eax
	cmp eax, 0
	je near _else_1
	push dword 0
	pop eax
	mov esp, ebp
	pop ebp
	ret
	jmp near _fi_1
_else_1:
_fi_1:
	mov edx, 1
	sub edx, 0
	inc edx
	lea eax, [ebp + edx*4]
	push dword eax
	push dword 1
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	je _je_if_2
	jmp _je_else_2
_je_if_2:
	push dword 1
	jmp _je_fi_2
_je_else_2:
	push dword 0
_je_fi_2:
	pop dword eax
	cmp eax, 0
	je near _else_3
	push dword 1
	pop eax
	mov esp, ebp
	pop ebp
	ret
	jmp near _fi_3
_else_3:
_fi_3:
	mov edx, 1
	sub edx, 0
	inc edx
	lea eax, [ebp + edx*4]
	push dword eax
	push dword 1
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	sub eax, ebx
	push dword eax
	call _fibonacci
	add esp, 4
	push dword eax
	lea eax, [ebp - 4]
	push dword eax
	pop dword ebx
	pop dword eax
	mov dword [ebx], dword eax
	mov edx, 1
	sub edx, 0
	inc edx
	lea eax, [ebp + edx*4]
	push dword eax
	push dword 2
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	sub eax, ebx
	push dword eax
	call _fibonacci
	add esp, 4
	push dword eax
	lea eax, [ebp - 8]
	push dword eax
	pop dword ebx
	pop dword eax
	mov dword [ebx], dword eax
	lea eax, [ebp - 4]
	push dword eax
	lea eax, [ebp - 8]
	push dword eax
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	mov dword ebx, [ebx]
	add eax, ebx
	push dword eax
	pop eax
	mov esp, ebp
	pop ebp
	ret
main:
	mov dword [__esp], esp
	push dword _x
	call scan_int
	add esp, 4
	push dword _x
	pop dword eax
	mov dword eax, dword [eax] 
	push eax
	call _fibonacci
	add esp, 4
	push dword eax
	pop dword eax
	mov dword [_resultado], eax
	push dword _resultado
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
