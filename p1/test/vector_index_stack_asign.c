#include <stdio.h>
#include "generator.h"

int main (int argc, char ** argv)
{
/*
	int x[5];
  y = 8;
  x[2] = y
  print x[2]
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

	/* y=8; */

	escribir_operando(salida,"8",0);
	asignar(salida,"y",0);

	/* x[0] = y */

	escribir_operando(salida,"y",1);
  escribir_operando(salida,"2",0); // idx := 2
	escribir_elemento_vector(salida, "x", 5, 0);
  asignarDestinoEnPila(salida, 1);

	/* printf x[0]; */
  escribir_operando(salida, "2", 0);
  escribir_elemento_vector(salida, "x", 5, 0);
	escribir(salida,1,ENTERO);

	escribir_fin(salida);

	fclose(salida);
	return 0;


}
