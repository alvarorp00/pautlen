#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdbool.h>

#define FPASM_NAME            fpasm
#define FPASM                 FILE *FPASM_NAME

#define DB  "db"
#define DW  "dw"
#define DD  "dd"

#define RESB "resb"
#define RESW "resw"
#define RESD "resd"

#define EAX  "eax"
#define EBX  "ebx"
#define ECX  "ecx"
#define EDX  "edx"


#define __EQ "_eq"
#define __LT "_eq"

// reserved variable names
#define _MSG_FAIL_ERR        "_msg_fail_err"
#define _MSG_SEGMENT_ERR     "_msg_segment_err"
#define _MSG_DIV_ERR         "_msg_div_err"

// reserved labels
#define __CHECK_DIV           "__check_div"
#define __CHECK_DIV_END       "__check_div_end"
#define __DIV_OK              "__div_ok"
#define __DIV_ERR             "__div_err"
#define __CHECK_IDX           "__check_idx"
#define __CHECK_IDX_END       "__check_idx_end"
#define __IDX_VECTOR_OK       "__idx_vector_ok"
#define __IDX_VECTOR_P_OK     "__idx_vector_p_ok"
#define __IDX_VECTOR_ERR      "__idx_vector_err"
#define __FAILED              "__failed"
#define __END                 "__end"

void write_double_pop( FPASM, const char *reg1, const char *reg2, int  is_var1, bool is_var2 );

void write_bss_header(FPASM);

void write_data_header(FPASM);

void write_var_declaration(FPASM, char * name, int type, int size);

void write_code_segment(FPASM);
void write_main_begin(FPASM);

void write_end(FPASM);

void write_operand(FPASM, char* name, bool is_var);
void write_assignment(FPASM, char* name, bool is_var);


void write_sum(FPASM, bool is_var1, bool is_var2);
void write_subtract(FPASM, bool is_var1, bool is_var2);
void write_mult(FPASM, bool is_var1, bool is_var2);
void write_div(FPASM, bool is_var1, bool is_var2);
void write_or(FPASM, bool is_var1, bool is_var2);
void write_and(FPASM, bool is_var1, bool is_var2);
void write_sign_change(FPASM, bool is_var);

void write_not(FPASM, bool is_var);

void write_equal(FPASM, bool is_var1, bool is_var2, int label);
void write_different(FPASM, bool is_var1, bool is_var2, int label);
void write_lower_equal(FPASM, bool is_var1, bool is_var2, int label);
void write_greater_equal(FPASM, bool is_var1, bool is_var2, int label);
void write_lower(FPASM, bool is_var1, bool is_var2, int label);
void write_greater(FPASM, bool is_var1, bool is_var2, int label);

void write_reading(FPASM, char* name, int type);
void write_writing(FPASM, bool is_var, int type);

/**
 * IF-THEN-ELSE
 */
void write_ifthen_begin( FPASM, bool is_var, int label );
void write_ifthen_end( FPASM, int label );
void write_ifthenelse_begin( FPASM, bool is_var, int label );
void write_ifthenelse_middle( FPASM, int label );
void write_ifthenelse_end( FPASM, int label );


/**
 * Bucles
 */
void write_while_begin( FPASM, int label );
void write_while_exp( FPASM, bool is_var, int label );
void write_while_end( FPASM, int label );

/* ****** */
void write_index_vector(FPASM, char* name, int max_size, bool is_var);

void write_function_declare(FPASM, char* name, int local_vars);
void write_function_return(FPASM, bool is_var);
void write_function_call(FPASM, char* name, int argc);

void write_param(FPASM, int index, int total_params);
void write_local_var(FPASM, int index);

void write_stack_assign_dest(FPASM, bool is_var);
void write_inv_stack_assign_dest(FPASM, bool is_var);
void write_stack_optoarg(FPASM, bool is_var);
void write_stack_clean(FPASM, int argc);

#endif