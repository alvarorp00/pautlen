#ifndef GENERATOR_H
#define GENERATOR_H
#include <stdio.h>

#define FPASM_NAME            fpasm
#define FPASM                 FILE *FPASM_NAME

typedef enum {
  INTEGER=0,
  BOOLEAN=1
} _var_types;

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
#define __CHECK_IDX           "__check_idx"
#define __CHECK_IDX_END       "__check_idx_end"
#define __IDX_VECTOR_OK       "__idx_vector_ok"
#define __IDX_VECTOR_ERR      "__idx_vector_err"
#define __FAILED              "__failed"
#define __END                 "__end"

#define escribir_subseccion_data write_data_header
#define escribir_cabecera_bss write_bss_header
#define declarar_variable write_var_declaration
#define escribir_segmento_codigo write_code_segment
#define escribir_inicio_main write_main_begin
#define escribir_fin write_end
#define escribir_operando write_operand
#define asignar write_assignment
#define sumar write_sum
#define restar write_subtract
#define multiplicar write_mult
#define dividir write_div
#define o write_or
#define y write_and
#define cambiar_signo write_sign_change
#define no write_not
#define igual write_equal
#define distinto write_different
#define menor_igual write_lower_equal
#define mayor_igual write_greater_equal
#define menor write_lower
#define mayor write_greater
#define escribir write_writing
#define leer write_reading
#define escribir_elemento_vector write_index_vector

#define ENTERO INTEGER
#define BOOLEANO BOOLEAN

void write_double_pop( FPASM, const char *reg1, const char *reg2, int  is_var1, int is_var2 );

void write_bss_header(FPASM);

void write_data_header(FPASM);

void write_var_declaration(FPASM, char * name, int type, int size);

void write_code_segment(FPASM);
void write_main_begin(FPASM);

void write_end(FPASM);

void write_operand(FPASM, char* name, int is_var);
void write_assignment(FPASM, char* name, int is_var);


void write_sum(FPASM, int is_var1, int is_var2);
void write_subtract(FPASM, int is_var1, int is_var2);
void write_mult(FPASM, int is_var1, int is_var2);
void write_div(FPASM, int is_var1, int is_var2);
void write_or(FPASM, int is_var1, int is_var2);
void write_and(FPASM, int is_var1, int is_var2);
void write_sign_change(FPASM, int is_var);

void write_not(FPASM, int is_var, int cuantos_no);

void write_equal(FPASM, int is_var1, int is_var2, int label);
void write_different(FPASM, int is_var1, int is_var2, int label);
void write_lower_equal(FPASM, int is_var1, int is_var2, int label);
void write_greater_equal(FPASM, int is_var1, int is_var2, int label);
void write_lower(FPASM, int is_var1, int is_var2, int label);
void write_greater(FPASM, int is_var1, int is_var2, int label);

void write_reading(FPASM, char* name, int type);
void write_writing(FPASM, int is_var, int type);

void write_index_vector(FPASM, char* name, int max_size, int is_dir);

#endif