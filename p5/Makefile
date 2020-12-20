FLEXFILE = alfa.l
BISONFILE = alfa.y
TOKEN = tokens.h

CC = gcc
CFLAGS = -g -Wall
BISONFLAGS = -y -d -v -Wyacc

_DEBUG_ = _DEBUG_

INC = inc
DIR = alfa
OUT = out
OBJ = obj
SRC = src
INFO = info

COMPILED = alfa

CALFA = $(DIR)alfa.c
OALFA = $(OBJ)alfa.o

CYYLEX = $(SRC)lex.yy.c
OYYLEX = $(OBJ)lex.yy.o

CYYPARSE = $(SRC)y.tab.c
OYYPARSE = $(OBJ)y.tab.o

GENERATOR = $(SRC)generator.c
HASH = $(SRC)hash.c
TSYMBOLS = $(SRC)symbolsTable.c
SYMBOL = $(SRC)symbol.c

SOURCEFILES = $(OYYLEX) $(OYYPARSE) $(CALFA) $(TSYMBOLS) $(SYMBOL) $(HASH) $(GENERATOR)

default: clean $(OALFA) ## Equivalent to 'make all'
		@ echo "Compiling all..."
		@ $(CC) -I $(INC) $(CFLAGS) -o $(COMPILED) $(SOURCEFILES)
		@ # clear
		@ echo "Compiled."

help:	## This guide
		@@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

all: default ## Produces compiler

$(OALFA): $(OYYPARSE) $(OYYLEX)
		@echo "Generating alfa.o"
		@$(CC) -I $(INC) $(CFLAGS) -c $(CALFA)
		@mv alfa.o $(OBJ).

$(CYYLEX): $(CYYPARSE)
		@echo "Generating lex.yy.c"
		@flex $(DIR)$(FLEXFILE)
		@mv lex.yy.c $(SRC).

$(OYYLEX): $(CYYLEX)
		@echo "Generating lex.yy.o"
		@$(CC) -I $(INC) $(CFLAGS) -c $(CYYLEX)
		@mv lex.yy.o $(OBJ).

$(CYYPARSE):
		@echo "Generating y.tab.c"
		@bison $(BISONFLAGS) $(DIR)$(BISONFILE)
		@mv y.output $(INFO)
		@mv y.tab.h $(INC).
		@mv y.tab.c $(SRC).

$(OYYPARSE): $(CYYPARSE)
		@echo "Generating y.tab.o"
		@$(CC) -I $(INC) $(CFLAGS) -c $(CYYPARSE)
		@mv y.tab.o $(OBJ).

.PHONY: clean

clean: ## Cleans output files
		rm -rf $(INFO)/y.output
		rm -f $(OYYLEX)
		rm -f $(OYYPARSE)
		rm -f $(CYYLEX)
		rm -f $(CYYPARSE)
		rm -f $(INC)/y.tab.h 
		@echo "Data cleaned."
