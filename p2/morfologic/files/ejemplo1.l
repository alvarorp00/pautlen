%{
/* C delimiters */

/* Author(s):
*
* Álvaro Rodríguez Palacios
* Javier Romera Llave
* Víctor Perea Riquelme
*/

#include <stdio.h>
#include <stdlib.h>

%}
%option noyywrap



%%
INICIO { printf("reconocido INICIO\n"); }
FIN { printf("reconocido FIN\n"); }
VECTOR { printf("reconocido VECTOR\n"); }
ENTERO { printf("reconocido ENTERO\n"); }
LOGICO { printf("reconocido LOGICO\n"); }
"\\" { printf("READ\n"); }
%%

int main()
{
  return yylex();  
}