segment .data
	_err_msg_runtime db "Error en tiempo de ejecucion",0
	_err_msg_div db "Intento de división por 0",0
segment .bss
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
	mov dword [_x], dword eax
	mov dword eax, dword _y
	push dword eax
	call scan_int
	add esp, 4
	push dword _y
	push dword _x
	pop dword ebx
	mov ebx, [ebx]
	pop dword eax
	mov eax, [eax]
	add eax, ebx
	push dword eax
	pop dword eax
	mov dword [_z], dword eax
	push dword _z
	pop dword eax
	mov eax, [eax]
	push dword eax
	call print_int
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
