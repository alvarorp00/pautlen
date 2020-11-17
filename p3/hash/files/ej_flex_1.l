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

"main"
"array"
"int"
"if"
"else"
"while"

%%

int main()
{
  return yylex();
}