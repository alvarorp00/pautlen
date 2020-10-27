#include <stdio.h>
#include "generator.h"

int main (int argc, char ** argv)
{
/*
	int x[5];
  y = 8;
  	
*/
	FILE * salida;

	if (argc != 2) {fprintf (stdout, "ERROR POCOS ARGUMENTOS\n"); return -1;}
	

	salida = fopen(argv[1],"w");


	escribir_subseccion_data(salida);
	escribir_cabecera_bss(salida);


	declarar_variable(salida, "x", ENTERO, 5);
  declarar_variable(salida, "y", ENTERO, 1);


	escribir_segmento_codigo(salida);
	escribir_inicio_main(salida);



	escribir_fin(salida);

	fclose(salida);
	return 0;


}
