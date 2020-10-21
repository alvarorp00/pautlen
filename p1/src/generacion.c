#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generacion.h"

#define __END__ "_end"
#define __RUNTIME_ERR__ "_runtime_err"
#define __NO_DIV_ERR__ "_no_div_err"
#define __NO_LOOP_STARTS__ "_no_loop_starts"
#define __NO_IF_ST__ "_no_if_st"
#define __NO_ELSE_ST__ "_no_else_st"
#define __NO_ENDIF_ST__ "_no_endif_st"
#define __NO_LOOP_ENDS__ "_no_loop_ends"

static void op_init(FILE* fpasm, int es_variable1, int es_variable2);


void escribir_cabecera_bss(FILE* fpasm){
    fprintf(fpasm, "segment .bss\n");
    fprintf(fpasm, "\t__esp resd 1\n");
}


void escribir_subseccion_data(FILE* fpasm){
    fprintf(fpasm, "segment .data\n");
    fprintf(fpasm, "\t_err_msg_runtime db \"Error en tiempo de ejecucion\",%d\n", 0);
    fprintf(fpasm, "\t_err_msg_div db \"Intento de división por 0\",%d\n", 0);
}


void declarar_variable(FILE* fpasm, char * nombre, int tipo, int tamano){
    tipo == BOOLEANO ? fprintf(fpasm, "\t_%s resd %d\n", nombre, tamano) : fprintf(fpasm, "\t_%s resd %d\n", nombre, tamano);
}


void escribir_segmento_codigo(FILE* fpasm){
    fprintf(fpasm, "segment .text\n");
    fprintf(fpasm, "\tglobal main\n");
    fprintf(fpasm, "\textern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean\n");
    fprintf(fpasm, "\textern print_endofline, print_blank, print_string\n");
    fprintf(fpasm, "\textern alfa_malloc, alfa_free, ld_float\n");
}


void escribir_inicio_main(FILE* fpasm){
    fprintf(fpasm, "main:\n");
    fprintf(fpasm, "\tmov dword [__esp], esp\n");
}


void escribir_fin(FILE* fpasm){
    fprintf(fpasm, "%s:\n", __END__);
    fprintf(fpasm, "\tmov dword esp, [__esp]\n");
    fprintf(fpasm, "\tret\n");
    fprintf(fpasm, "%s:\n", __RUNTIME_ERR__);
    fprintf(fpasm, "\tpush dword [_err_msg_runtime]\n");
    fprintf(fpasm, "\tcall print_string\n");
    fprintf(fpasm, "\tadd esp, 4\n"); /* podría ahorrarse ya que estamos acabando la ejecución */
    fprintf(fpasm, "\tcall print_endofline\n");
    fprintf(fpasm, "\tjmp %s\n", __END__);
}

void escribir_operando(FILE* fpasm, char* nombre, int es_variable){
    fprintf(fpasm, "\tpush dword %s%s\n", es_variable ? "_" : "", nombre);
}


void asignar(FILE* fpasm, char* nombre, int es_variable){
    fprintf(fpasm, "\tpop dword eax\n");
    if(es_variable)
        fprintf(fpasm, "\tmov eax, [eax]\n");
    fprintf(fpasm, "\tmov dword [_%s], dword eax\n", nombre);
}



/* ARITHMETIC FUNCTIONS */


void sumar(FILE* fpasm, int es_variable1, int es_variable2){
    op_init(fpasm, es_variable1, es_variable2);

    fprintf(fpasm, "\tadd eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
}


void restar(FILE* fpasm, int es_variable1, int es_variable2){
    op_init(fpasm, es_variable1, es_variable2);

    fprintf(fpasm, "\tsub eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
}


void multiplicar(FILE* fpasm, int es_variable1, int es_variable2){
    op_init(fpasm, es_variable1, es_variable2);

    fprintf(fpasm, "\tmov edx, 0\n");
    fprintf(fpasm, "\timul ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
}

/* 
    we don't call op_init like on the others
    as we're treating this one on a different way
*/
void dividir(FILE* fpasm, int es_variable1, int es_variable2){
    fprintf(fpasm, "\tpop dword ecx\n");
    if(es_variable1)
        fprintf(fpasm, "\tmov ecx, [ecx]\n");

    fprintf(fpasm, "\tpop dword eax\n");
    if(es_variable2)
        fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tmov edx, 0\n");

    fprintf(fpasm, "\tcmp ecx, 0\n");
    fprintf(fpasm, "\tjne %s\n", __NO_DIV_ERR__);

    fprintf(fpasm, "\tpush dword [_err_msg_div]\n");
    fprintf(fpasm, "\tcall print_string\n");
    fprintf(fpasm, "\tadd esp, 4\n");
    fprintf(fpasm, "\tcall print_endofline\n");
    fprintf(fpasm, "\tjmp %s\n", __END__);

    fprintf(fpasm, "%s:\n", __NO_DIV_ERR__);
    fprintf(fpasm, "\tcdq\n");
    fprintf(fpasm, "\tidiv ecx\n");
    fprintf(fpasm, "\tpush dword eax");
}


void o(FILE* fpasm, int es_variable1, int es_variable2){
    op_init(fpasm, es_variable1, es_variable2);

    fprintf(fpasm, "\tor eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
}


void y(FILE* fpasm, int es_variable1, int es_variable2){
    op_init(fpasm, es_variable1, es_variable2);

    fprintf(fpasm, "\tand eax, ebx\n");
    fprintf(fpasm, "\tpush dword eax\n");
}

/* ----- */

void cambiar_signo(FILE* fpasm, int es_variable){
    fprintf(fpasm, "\tpop dword eax\n");
    if(es_variable)
        fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tneg eax\n");
}

//sería preferible olvidarnos de cuantos_no y usar una variable estática
void no(FILE* fpasm, int es_variable, int cuantos_no){
    fprintf(fpasm, "\tpop dword eax\n"); /* eax == stack_top (numeric) */
    if(es_variable)
        fprintf(fpasm, "\tmov eax, [eax]\n");

    fprintf(fpasm, "\tcmp eax, 0\n"); // ¿eax == 0?
    fprintf(fpasm, "\tje %s%d\n", __NO_ELSE_ST__, cuantos_no); // eax == 0

    fprintf(fpasm, "\tsub eax, 1\n"); // eax <= 1
    fprintf(fpasm, "\tjmp %s%d\n", __NO_ENDIF_ST__, cuantos_no);

    fprintf(fpasm, "%s%d:\n", __NO_ELSE_ST__, cuantos_no); // eax == 0
    fprintf(fpasm, "\tinc eax\n"); // eax <= 1

    fprintf(fpasm, "%s%d:\n", __NO_ENDIF_ST__, cuantos_no);

    fprintf(fpasm, "\tpush dword eax\n");
}


/* COMPARATIVE FUNCTIONS */

void igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    op_init(fpasm, es_variable1, es_variable2);
    
    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tje _%d", etiqueta);
}


void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    op_init(fpasm, es_variable1, es_variable2);
    
    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjne _%d", etiqueta);
}


void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    op_init(fpasm, es_variable1, es_variable2);
    
    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjle _%d", etiqueta);
}


void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    op_init(fpasm, es_variable1, es_variable2);
    
    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjge _%d", etiqueta);
}


void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    op_init(fpasm, es_variable1, es_variable2);
    
    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjl _%d", etiqueta);
}


void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
    op_init(fpasm, es_variable1, es_variable2);
    
    fprintf(fpasm, "\tcmp eax, ebx\n");
    fprintf(fpasm, "\tjg _%d", etiqueta);
}


/* READ & WRITE INSTRUCTIONS */

void leer(FILE* fpasm, char* nombre, int tipo){
    fprintf(fpasm, "\tpush dword _%s\n", nombre);
    fprintf(fpasm, "\t%s\n", tipo == BOOLEANO ? "call scan_boolean" : "call scan_int");
    fprintf(fpasm, "\tadd esp, 4\n");
}

void escribir(FILE* fpasm, int es_variable, int tipo){
    fprintf(fpasm, "\tpop dword eax\n");
    if(es_variable)
        fprintf(fpasm, "\tmov eax, [eax]\n");
    
    fprintf(fpasm, "\tpush dword eax\n");
    fprintf(fpasm, "\t%s\n", tipo == BOOLEANO ? "call print_boolean" : "call print_int");
    fprintf(fpasm, "\tadd esp, 4\n");
    fprintf(fpasm, "\tcall print_endofline\n");
}


/* ***************************** */

/* 
    static function -> just visible for same file(translation unit)
    helps us while initializing arithmetic functions & register's values
*/
static void op_init(FILE* fpasm, int es_variable1, int es_variable2){
    fprintf(fpasm, "\tpop dword ebx\n");
    if(es_variable1)
        fprintf(fpasm, "\tmov ebx, [ebx]\n");

    fprintf(fpasm, "\tpop dword eax\n");
    if(es_variable2)
        fprintf(fpasm, "\tmov eax, [eax]\n");
}