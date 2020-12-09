FLEXFILE = alfa.l
BISONFILE = alfa.y
TOKEN = tokens.h

CC = gcc
CFLAGS = -g -Wall
BISONFLAGS = -y -d -v -Wyacc

_STD_ = _STD_
_EXPLAIN_ = _EXPLAIN_
_SYNTACTIC_ = _SYNTACTIC_

INC = inc/
DIR = alfa/
OUT = out/
OBJ = obj/
SRC = src/
INFO = info/

TESTFILES = testfiles/
RESULTS = testresults/

COMPILED = compiler

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
		@ clear
		@ echo "Compiled."

help:	## This guide
		@@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

all: default ## Produces nasm file
	./$(COMPILED) samples/first_delivery.alf first_delivery.nasm

nasm: all ## Compiles nasm file
	./nasm_to_exec.sh first_delivery.nasm prg1
	@echo "Success. Program --> prg1"

manual:
		@clear
		@echo "Parsing from terminal..."
		./$(COMPILED)

hash_test: ## Test hash
	 	@$(CC) -I $(INC) -o run_hash_test $(SRC)hashTest.c $(SYMBOL) $(HASH)
		./run_hash_test

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
		rm -rf $(RESULTS)*
		rm -rf $(INFO)/y.output
		rm -f $(COMPILED)
		rm -f $(OYYLEX)
		rm -f $(OYYPARSE)
		rm -f $(CYYLEX)
		rm -f $(CYYPARSE)
		rm -f $(INC)/y.tab.h 
		rm -f run_hash_test
		rm -f prg1
		@echo "Data cleaned."
