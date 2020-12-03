/**
 * 
 * HEADER
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "symbolsTable.h"

#define PRINT_RESPONSE(response, name, mode) \
            TO_STDOUT("SCOPE: %s @-->%s of %s<--- %s",st_getScope(st) == GLOBAL ? "GLOBAL" : "LOCAL" ,mode, name, response == true ? "Success" : "Failure")

#define PRINT_HELP(fname) \
            TO_STDOUT("Args err --> ./%s FILE_IN FILE_OUT", fname)

#define _EXPLAIN_

void doParse(FILE *f_in, FILE *f_out);
void processLine(String line);
void searchSymbol(String identifier);
void insertSymbol(String identifier, int value);
void formatString(String str);
void copySubstring(String dest, String src, uint32_t from, uint32_t to);

static SymbolsTable *st; /* Global */
bool response;

int main(int argc, char const *argv[])
{
  FILE *f_in, *f_out;

  
  if(argc != 3)
    PRINT_HELP(argv[0]);
  f_in = READ(argv[1]);
  if(!f_in)
    TO_STDERR("ERROR OPENING F_IN");
  f_out = WRITE(argv[2]);
  if(!f_out)
    TO_STDERR("ERROR OPENING F_OUT");

  doParse(f_in, f_out);

  fclose(f_in);
  fclose(f_out);

  return 0;
}

/* ************ TEST FUNCTION ************** */

void doParse(FILE *f_in, FILE *f_out)
{  
  char line[BUFF];

  st = symbolsTableInit();
  if(!st)
    return;

  while (fgets(line, sizeof(line), f_in) != NULL)
  {
    processLine(line);
  }
}

void processLine(String line)
{
  char identifier[MAX_LEN];
  char c_value[32];
  size_t i, j;
  int i_value;
  
  if(!line)
    return;

  for(i = 0; line[i] != '\t' && line[i] != '\0' && line[i] != '\n'; i++);

  if(line[i] != '\t')
  {
    strncpy(identifier, line, i);
    formatString(identifier);
    searchSymbol(identifier);
  }
  else
  {
    strncpy(identifier, line, i);

    for(j = i; line[j] != '\0' && line[j] != '\n'; j++);

    copySubstring(c_value, line, i+1, j);
    i_value = atoi(c_value);
    formatString(identifier);
    insertSymbol(identifier, i_value);
  }
  
}

void searchSymbol(String identifier)
{
  if(!identifier)
    return;
  
  /* TODO */
  if(strcmp(identifier, "cierre") == 0) //search reserved word for closing local scope
  {
   return; // ¿What should we do here? 
  }

  if(st_getScope(st) == LOCAL)
      response = localUse(st, identifier);
  else
    response = globalUse(st, identifier);
  #ifdef _EXPLAIN_
  PRINT_RESPONSE(response, identifier, "Search");
  #endif
}

void insertSymbol(String identifier, int value)
{
  if(!identifier)
    return;

  if (strcmp(identifier, "cierre") == 0 && value < 0)
  {
    /* Scope GLOBAL again */
    response = stopLocalScope(st);
    #ifdef _EXPLAIN_
    PRINT_RESPONSE(response, identifier, "Local Scope Closed");
    #endif
    return;
  }
  
  if(value < 0)
  {
    response = declareFunction(st, identifier, value);
    #ifdef _EXPLAIN_
    PRINT_RESPONSE(response, identifier, "Local Scope Opened");
    #endif
  }
  else
  {
    if(st_getScope(st) == GLOBAL)
    {
      response = declareGlobal(st, identifier, value);
      #ifdef _EXPLAIN_
      PRINT_RESPONSE(response, identifier, "Insertion");
      #endif
    }
    else
    {
      response = declareLocal(st, identifier, value);
      #ifdef _EXPLAIN_
      PRINT_RESPONSE(response, identifier, "Insertion");
      #endif
    }
  }
}

void formatString(String str)
{
  const char* format = str;
  do {
      while (*format == ' ' || *format == 1) {
          ++format;
      }
  } while (*str++ = *format++);
}

void copySubstring(String dest, String src, uint32_t from, uint32_t to)
{
  uint32_t i, j;

  i = 0;
  j = from;

  while (j <= to)
  {
    dest[i++] = src[j++];
  }
  dest[i] = '\0';
}