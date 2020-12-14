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

#define IF_       "_if_%d"
#define ELSE_     "_else_%d"
#define FI_       "_fi_%d"

#define WHILE_    "while_%d"
#define WHILE_END_ "_while_end_%d"

/* err control routines */


/**
 *
 * Writes a subroutine which
 * checks division is not by 0
 * ==> ecx != 0
 * on error: ebx := 1
 * on ok: ebx := 0
 */

void write_division_check(FPASM) {
  _LABEL(__CHECK_DIV);

  _ASM("cmp ecx, 0");
  _ASM("jne %s", __DIV_OK);

  _ASM("mov ebx, %s", _MSG_DIV_ERR);
  _ASM("mov [%s], ebx", _MSG_FAIL_ERR);
  _ASM("mov ebx, 1");
  _ASM("jmp %s", __CHECK_DIV_END);

  _LABEL(__DIV_OK);
  _ASM("mov ebx, 0");

  _LABEL(__CHECK_DIV_END);
  _ASM("ret");
}


/**
 *
 * Writes a subroutine which checks
 * index var access is allowed
 * and no overflow occur
 * ==> eax < edx  ===== idx < size
 * on error: ebx := 1
 * on ok: ebx := 0
 */

void write_index_check(FPASM) {
  _LABEL(__CHECK_IDX);

  _ASM("cmp eax, edx");
  _ASM("jl %s", __IDX_VECTOR_OK);

  _ASM("mov edx, %s", _MSG_SEGMENT_ERR);
  _ASM("mov [%s], edx", _MSG_FAIL_ERR);
  _ASM("mov edx, 1");
  _ASM("jmp %s", __CHECK_IDX_END);

  _LABEL(__IDX_VECTOR_OK);
  _ASM("mov edx, 0");

  _LABEL(__CHECK_IDX_END);

  _ASM("ret");
}

/* required routines */

void write_double_pop( FPASM, const char *reg1, const char *reg2, int  is_var1, bool is_var2 ) {

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

  write_division_check(FPASM_NAME);
  write_index_check(FPASM_NAME);

}

void write_operand(FPASM, char* name, bool is_var) {
  if ( is_var ) {
    _ASM( "push dword _%s", name );
  } else {
    _ASM( "push dword %s", name );
  }
}

void write_assignment(FPASM, char* name, bool is_var) {

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
  } else if ( type == INT ) {
    _ASM( "call scan_int" );
  }

  _ASM( "add esp, 4" );

}

void write_writing(FPASM, bool is_var, int type) {

  _ASM( "pop dword eax" );

  if ( is_var ) {
    _ASM( "mov dword eax, [eax]" );
  }

  _ASM( "push dword eax" );

  if ( type == BOOLEAN ) {
    _ASM( "call print_boolean" );
  } else if ( type == INT ) {
    _ASM( "call print_int" );
  }

  _ASM( "call print_endofline" );

  _ASM( "add esp, 4" );

}

/* Operations */

void write_sum(FPASM, bool is_var1, bool is_var2) {
  write_double_pop( FPASM_NAME, EAX, EBX, is_var1, is_var2 );
  _ASM( "add eax, ebx" );
  _ASM( "push dword eax" );
}

void write_subtract(FPASM, bool is_var1, bool is_var2) {
  write_double_pop( FPASM_NAME, EAX, EBX, is_var1, is_var2 );
  _ASM( "sub eax, ebx" );
  _ASM( "push dword eax" );
}

void write_mult(FPASM, bool is_var1, bool is_var2) {
  write_double_pop( FPASM_NAME, EAX, EBX, is_var1, is_var2 );
  _ASM( "imul ebx" );
  _ASM( "push dword eax" );
}

void write_div( FPASM, bool is_var1, bool is_var2 ) {

  write_double_pop( FPASM_NAME, EAX, ECX, is_var1, is_var2 );

  _ASM("call %s", __CHECK_DIV);
  _ASM("cmp ebx, 1");
  _ASM("je %s", __FAILED);

  _ASM( "mov edx, 0" );
  _ASM( "idiv ecx" );
  _ASM( "push dword eax" );

}


void write_or( FPASM, bool is_var1, bool is_var2 ) {
  write_double_pop( FPASM_NAME, EAX, EBX, is_var1, is_var2 );
  _ASM( "or eax, ebx" );
  _ASM( "push dword eax" );
}

void write_and( FPASM, bool is_var1, bool is_var2 ) {
  write_double_pop( FPASM_NAME, EAX, EBX, is_var1, is_var2 );
  _ASM( "and eax, ebx" );
  _ASM( "push dword eax" );
}

void write_sign_change( FPASM, bool is_var ) {

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
void write_not( FPASM, bool is_var, int nno ) {

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

void write_comparator( FPASM, const char *jf, bool is_var1, bool is_var2, int id ) {

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

void write_equal( FPASM, bool is_var1, bool is_var2, int id ) {
  write_comparator( FPASM_NAME, "je", is_var1, is_var2, id );
}

void write_different( FPASM, bool is_var1, bool is_var2, int id ) {
  write_comparator( FPASM_NAME, "jne", is_var1, is_var2, id );
}

void write_lower_equal( FPASM, bool is_var1, bool is_var2, int id ) {
  write_comparator( FPASM_NAME, "jle", is_var1, is_var2, id );
}

void write_greater_equal( FPASM, bool is_var1, bool is_var2, int id ) {
  write_comparator( FPASM_NAME, "jge", is_var1, is_var2, id );
}

void write_lower( FPASM, bool is_var1, bool is_var2, int id ) {
  write_comparator( FPASM_NAME, "jl", is_var1, is_var2, id );
}

void write_greater( FPASM, bool is_var1, bool is_var2, int id ) {
  write_comparator( FPASM_NAME, "jg", is_var1, is_var2, id );
}

/* Conditionals */

void write_ifthen_begin( FPASM, bool is_var, int label ) {

  _ASM( "pop dword eax" );
  
  if ( is_var ) {
    _ASM( "mov eax, [eax]" );
  }

  _ASM( "cmp eax, 0" );
  _ASM( "je near "FI_, label );
  
}

void write_ifthen_end( FPASM, int label ) {
  _LABEL( FI_, label ); 
}

void write_ifthenelse_begin( FPASM, bool is_var, int label ) {

  _ASM( "pop dword eax" );
  
  if ( is_var ) {
    _ASM( "mov eax, [eax]" );
  }

  _ASM( "cmp eax, 0" );
  _ASM( "je near "ELSE_, label );
  
}

void write_ifthenelse_middle( FPASM, int label ) {
  _ASM( "jmp near "FI_, label );
  _LABEL( ELSE_, label );
}

void write_ifthenelse_end( FPASM, int label ) {
  _LABEL( FI_, label );
}

/* Loops */

void write_while_begin( FPASM, int label ) {
  _LABEL( WHILE_, label );
}

void write_while_exp( FPASM, bool is_var, int label ) {
  _ASM( "pop dword eax" );
  if ( is_var ) {
    _ASM( "mov eax, [eax]" );
  }
  _ASM( "cmp eax, 0" );
  _ASM( "je near "WHILE_END_, label );
}

void write_while_end( FPASM, int label ) {
  _ASM( "jmp "WHILE_, label );
  _LABEL( WHILE_END_, label );
}

/* Index Vector */

void write_index_vector(FPASM, char* name, int max_size, bool is_var) {
  _ASM("pop eax"); // eax := index

  if(is_var)
    _ASM("mov dword eax, dword [eax]");

  _ASM("mov edx, %d", max_size); // edx := max_size
  _ASM("call %s", __CHECK_IDX); // call subroutine

  _ASM("cmp edx, 1"); // ¿ edx == err ?
  _ASM("je %s", __FAILED); // edx == err

  _ASM("mov edx, 4"); // edx = 4
  _ASM("imul edx"); // edx := XXXX; eax := array + eax*4 -> dword == 4B
  _ASM("add eax, _%s", name);
  _ASM("mov dword edx, dword eax"); // edx := array[idx]; idx == eax*4 (dword, resd == 4B)
  _ASM("push edx"); // edx in stack
}

/* Function Part */

void write_function_declare(FPASM, char* name, int local_vars) {
  
  _LABEL("_%s", name);
  
  /* 
  * save base pointer -> then save esp to ebp
  * in order to use esp as much as 
  * as local_vars we'll have
  */
  _ASM("push ebp");
  _ASM("mov ebp, esp");
  
  // alloc 4*local_vars Bytes == x(local_vars) times variables
  _ASM("sub esp, %d", 4*local_vars); //4 == resd, 4Bytes
}

void write_function_return(FPASM, bool is_var) {
  _ASM("pop eax");

  if(is_var){
    _ASM("mov dword eax, [eax]");
  }
  
  // restore stack pointer
  _ASM("mov esp, ebp");

  // restore base pointer
  _ASM("pop ebp");

  // return
  _ASM("ret");
}

void write_function_call(FPASM, char* name, int argc) {
  // call function
  _ASM("call _%s", name);

  // clean stack
  write_stack_clean(FPASM_NAME, argc);

  // once args cleaned, push function return in eax by agreement
  _ASM("push dword eax");
}

/* Params Part */

void write_param(FPASM, int index, int total_params) {
  // starting on params[0] 
  _ASM("mov edx, %d", total_params);
  _ASM("sub edx, %d", index);
  _ASM("inc edx"); // idx := vector start direction

  // ebp := esp, as we are inside a function
  _ASM("lea eax, [ebp + edx*4]"); // eax := indexed element direction

  _ASM("push dword eax");
}

void write_local_var(FPASM, int index) {
  // starting on vars[1] so we don't increase eax by 1 and then multiply by 4
  _ASM("lea eax, [ebp - %d]", 4*index); // eax := address
  _ASM("push dword eax");
}

/* Stack Part */

void write_stack_asign_dest(FPASM, bool is_var) {
  write_double_pop(FPASM_NAME, EAX, EBX, is_var, 0); // ebx := offset; eax:=value
  _ASM("mov dword [ebx], dword eax");
}

void write_stack_optoarg(FPASM, bool is_var) {
  if(!is_var)
    return;
  
  _ASM("pop dword eax");
  _ASM("mov dword eax, dword [eax] ");
  _ASM("push eax");
}

void write_stack_clean(FPASM, int argc) {
  _ASM("add esp, %d", 4*argc); // add x(local_vars) times variables -> clean stack
}
