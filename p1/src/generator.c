#include "generator.h"

// macro utils
#define STRINGIFY( x )        #x

#define _ASML( str, ... )     \
  fprintf( FPASM_NAME, "\t" str, ##__VA_ARGS__ ) 

#define _ASM( str, ... )      \
  _ASML( str"\n", ##__VA_ARGS__ )

#define _LABEL( str, ... )    \
  fprintf( FPASM_NAME, str ":\n", ##__VA_ARGS__ )

#define _COMMENT( str, ... )   \
  fprintf( FPASM_NAME, "\t; " str "\n", ##__VA_ARGS__ )

#define _SEGMENT( str, ... )    \
  fprintf( FPASM_NAME, "segment ." str "\n", ##__VA_ARGS__ )

#define _IF_      "_%s_if_%d"
#define _ELSE_    "_%s_else_%d"
#define _FI_      "_%s_fi_%d"

/* err control routines */

/**
 * 
 * Writes a subroutine which checks
 * index var access is allowed
 * and no overflow occur
 */
void write_index_check_function(FPASM) {
  _LABEL(__CHECK_IDX);
  
  _ASM("cmp eax, edx");
  _ASM("jb %s", __IDX_VECTOR_OK);

  _ASM("mov edx, %s", _MSG_DIV_ERR );
  _ASM("mov [%s], edx", _MSG_SEGMENT_ERR );
  _ASM("mov edx, 1");
  _ASM("jmp %s", __CHECK_IDX_END);
  
  _LABEL(__IDX_VECTOR_OK);
  _ASM("mov edx, 0");
  
  _LABEL(__CHECK_IDX_END);
  
  _ASM("ret");
}

// ¿Same for the division?

/* required routines */

void write_double_pop( FPASM, const char *reg1, const char *reg2, int  is_var1, int is_var2 ) {

  _ASM( "pop dword %s", reg2 );
  _ASM( "pop dword %s", reg1 );

  if ( is_var1 ) {
    _ASM( "mov dword %s, [%s]", reg1, reg1 );
  }

  if ( is_var2 ) {
    _ASM( "mov dword %s, [%s]", reg2, reg2 );
  }

}

void write_data_header( FPASM ) {

  _SEGMENT( "data" );
  _ASM( "%s db 'err: division by 0',0", _MSG_DIV_ERR );
  _ASM( "%s db 'err: segment out of range',0", _MSG_SEGMENT_ERR );

}

void write_bss_header( FPASM ) {  
  _SEGMENT( "bss" );
  _ASM("%s resd 1", _MSG_FAIL_ERR );
  _ASM("__esp resd 1" );
}

void write_var_declaration(FPASM, char * name, int type, int size) {
  _ASM( "_%s resd %d", name, size );
}

void write_code_segment(FPASM) {
  _SEGMENT( "text" );

  _ASM( "global main" );
  _ASM( "extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean" );
  _ASM( "extern print_endofline, print_blank, print_string" );
  _ASM( "extern alfa_malloc, alfa_free, ld_float" );

}

void write_main_begin( FPASM ) {
  _LABEL("main");
  _ASM( "mov dword [__esp], esp" );
}

void write_end(FPASM) {

  _LABEL( __END );

  _ASM( "mov dword esp, [__esp]" ); 
  _ASM( "ret" );

  _LABEL( __FAILED );

  _ASM( "push dword [%s]", _MSG_FAIL_ERR ); 
  _ASM( "call print_string" );
  _ASM( "add esp, 4" );
  _ASM( "call print_endofline" );
  _ASM( "jmp %s", __END );

  write_index_check_function(FPASM_NAME);

}

void write_operand(FPASM, char* name, int is_var) {
  if ( is_var ) {
    _ASM( "push dword _%s", name );
  } else {
    _ASM( "push dword %s", name );
  }
}

void write_assignment(FPASM, char* name, int is_var) {
  
  _ASM( "pop dword eax" );

  if ( is_var ) {
    _ASM( "mov dword eax, [eax]" );
  }

  _ASM( "mov dword [_%s], eax", name );

}

void write_reading(FPASM, char* name, int type) {

  // push into the stack the offset of the variable
  _ASM( "push dword _%s", name );

  if ( type == BOOLEAN ) {
    _ASM( "call scan_boolean" );
  } else if ( type == INTEGER ) {
    _ASM( "call scan_int" );
  }

  _ASM( "add esp, 4" );

}

void write_writing(FPASM, int is_var, int type) {

  _ASM( "pop dword eax" );

  if ( is_var ) {
    _ASM( "mov dword eax, [eax]" );
  }

  _ASM( "push dword eax" );

  if ( type == BOOLEAN ) {
    _ASM( "call print_boolean" );
  } else if ( type == INTEGER ) {
    _ASM( "call print_int" );
  }

  _ASM( "call print_endofline" );

  _ASM( "add esp, 4" );

}

/* Operations */

void write_sum(FPASM, int is_var1, int is_var2) {
  write_double_pop( FPASM_NAME, EAX, EBX, is_var1, is_var2 );
  _ASM( "add eax, ebx" );
  _ASM( "push dword eax" );
}

void write_subtract(FPASM, int is_var1, int is_var2) {
  write_double_pop( FPASM_NAME, EAX, EBX, is_var1, is_var2 );
  _ASM( "sub eax, ebx" );
  _ASM( "push dword eax" ); 
}

void write_mult(FPASM, int is_var1, int is_var2) {
  write_double_pop( FPASM_NAME, EAX, EBX, is_var1, is_var2 );
  _ASM( "imul eax, ebx" );
  _ASM( "push dowrd eax" );
}

void write_div( FPASM, int is_var1, int is_var2 ) {

  write_double_pop( FPASM_NAME, EAX, ECX, is_var1, is_var2 );

  _ASM( "cmp ecx, 0" );
  _ASM( "jne _do_div" );

  _ASM( "mov eax, %s", _MSG_DIV_ERR );
  _ASM( "mov [%s], eax", _MSG_FAIL_ERR );
  _ASM( "jmp %s", __FAILED );

  // do div
  _LABEL( "_do_div" );
  _ASM( "mov edx, 0" );
  _ASM( "idiv ecx" );
  _ASM( "push dword eax" );

}


void write_or( FPASM, int is_var1, int is_var2 ) {
  write_double_pop( FPASM_NAME, EAX, EBX, is_var1, is_var2 );
  _ASM( "or eax, ebx" );
  _ASM( "push dword eax" );
}

void write_and( FPASM, int is_var1, int is_var2 ) {
  write_double_pop( FPASM_NAME, EAX, EBX, is_var1, is_var2 );
  _ASM( "and eax, ebx" );
  _ASM( "push dword eax" );
}

void write_sign_change( FPASM, int is_var ) {

  _ASM( "pop dword eax" );

  if ( is_var ) {
    _ASM( "mov dword eax, [eax]" );
  }

  _ASM( "neg eax" );
  _ASM( "push dword eax" );

}

/**
 * 
 * @param nno parameter is ignored becouse it is not
 * necessary
 */
void write_not( FPASM, int is_var, int nno ) {

  _ASM( "pop dword eax" );

  if ( is_var ) {
    _ASM( "mov dword eax, [eax]" );
  }

  // 0-1 = -1 => 1
  // 1-1 = 0 => 0
  _ASM( "sub eax, 1");
  _ASM( "neg eax" );

  _ASM( "push dword eax" );

}

/* Compare */

void write_comparator( FPASM, const char *jf, int is_var1, int is_var2, int id ) {

  write_double_pop( FPASM_NAME, EAX, EBX, is_var1, is_var2 );
  
  _ASM( "cmp eax, ebx" );  
  _ASM( "%s "_IF_, jf, jf, id );
  _ASM( "jmp "_ELSE_, jf, id );

  _LABEL( _IF_, jf, id );
  _ASM( "push dword 1");
  _ASM( "jmp "_FI_, jf, id );

  _LABEL( _ELSE_, jf, id );
  _ASM( "push dword 0");

  _LABEL( _FI_, jf, id );

}

void write_equal( FPASM, int is_var1, int is_var2, int id ) {
  write_comparator( FPASM_NAME, "je", is_var1, is_var2, id );
}

void write_different( FPASM, int is_var1, int is_var2, int id ) {
  write_comparator( FPASM_NAME, "jne", is_var1, is_var2, id );
}

void write_lower_equal( FPASM, int is_var1, int is_var2, int id ) {
  write_comparator( FPASM_NAME, "jle", is_var1, is_var2, id );
}

void write_greater_equal( FPASM, int is_var1, int is_var2, int id ) {
  write_comparator( FPASM_NAME, "jge", is_var1, is_var2, id );
}

void write_lower( FPASM, int is_var1, int is_var2, int id ) {
  write_comparator( FPASM_NAME, "jl", is_var1, is_var2, id );
}

void write_greater( FPASM, int is_var1, int is_var2, int id ) {
  write_comparator( FPASM_NAME, "jg", is_var1, is_var2, id );
}

/* IF METHODS GOES HERE */

/* WHILE PART GOES HERE */

/* Index Vector */

void write_index_vector(FPASM, char* name, int max_size, int is_dir) {
  _ASM("pop eax"); // eax := index

  if(is_dir)
    _ASM("mov dword eax, dword [eax]");
  
  _ASM("mov edx, %d", max_size); // edx := max_size
  _ASM("call %s", __CHECK_IDX); // call subroutine
  _ASM("cmp edx, 1"); // ¿ edx == err ?
  _ASM("je %s", __FAILED); // edx == err

  _ASM("mov edx, 4"); // edx = 4
  _ASM("imul edx"); // edx := ¿?; eax := array + eax*4 -> dword == 4B
  _ASM("add eax, %s", name);
  _ASM("mov dword edx, dword eax"); // edx := array[idx]; idx == eax*4 (dword, resd == 4B)
  _ASM("push edx"); // edx in stack
}

/* Function Part */

void function_declare(FPASM, char* name, int local_vars) {

}

void function_return(FPASM, int* is_var) {
  
}

void function_call(FPASM, char* name, int argc) {

}

/* Params Part */

void write_param(FPASM, int index, int total_params) {

}

void write_local_var(FPASM, int index) {
  
}

/* Stack Part */

void stack_asign_dest(FPASM, int is_var) {
  write_double_pop(FPASM_NAME, EAX, EBX, is_var, 0); // ebx := offset; eax:=value

  _ASM("mov dword ebx, dword eax");
}

void stack_optoarg(FPASM, int is_var) {
  _ASM("pop dword eax");

  if(is_var)
    _ASM("mov dword eax, dword [eax] ");
  
  _ASM("push eax");
}

void stack_clean(FPASM, int argc) {
  _ASM("mov eax, %d", argc);
  _ASM("mov ebx, 4");
  _ASM("imul ebx");
  _ASM("add esp, eax");
}