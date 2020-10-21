segment .data
	_err_msg_runtime db "Error en tiempo de ejecucion",0
	_err_msg_div db "Intento de división por 0",0
segment .bss
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
	mov eax, [eax]
	cmp eax, 0
	je _no_else_st0
	sub eax, 1
	jmp _no_endif_st0
_no_else_st0:
	inc eax
_no_endif_st0:
	push dword eax
	pop dword eax
	push dword eax
	call print_boolean
	add esp, 4
	call print_endofline
	push dword _b1
	pop dword eax
	mov eax, [eax]
	cmp eax, 0
	je _no_else_st1
	sub eax, 1
	jmp _no_endif_st1
_no_else_st1:
	inc eax
_no_endif_st1:
	push dword eax
	pop dword eax
	cmp eax, 0
	je _no_else_st2
	sub eax, 1
	jmp _no_endif_st2
_no_else_st2:
	inc eax
_no_endif_st2:
	push dword eax
	pop dword eax
	push dword eax
	call print_boolean
	add esp, 4
	call print_endofline
_end:
	mov dword esp, [__esp]
	ret
_runtime_err:
	push dword [_err_msg_runtime]
	call print_string
	add esp, 4
	call print_endofline
	jmp _end
