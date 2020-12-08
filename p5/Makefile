FLEXFILE = alfa.l
BISONFILE = alfa.y
TOKEN = tokens.h

CC = gcc
CFLAGS = -g -Wall
BISONFLAGS = -y -d -v -Wyacc
YACCFLAGS = 

_STD_ = _STD_

_EXPLAIN_ = _EXPLAIN_

INC = inc/
DIR = alfa/
OUT = out/
OBJ = obj/
SRC = src/
INFO = info/

RESULTS = testresults/
TESTFILES = testfiles/

COMPILED = program

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

TESTFILEIN = $(TESTFILES)pruebaTS.txt
TESTFILEOUT = $(TESTFILES)expectedResTS.txt

TESTRESULT = $(RESULTS)testresult.txt

default: clean semantic_manual ## Equivalent to 'make all'
		@# clear

help:	## This guide
		@@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

test: default ## Executes test and compares result
		@echo "Executing test..."
		./$(COMPILED) $(TESTFILEIN) $(TESTRESULT)
		@./testverify.sh $(TESTFILEOUT) $(TESTRESULT)

semantic: $(OALFA)
		@echo "Compiling all..."
		@$(CC) -I $(INC) $(CFLAGS) -o $(COMPILED) $(SOURCEFILES)

semantic_manual: $(OALFA)
		@echo "Compiling all..."
		@$(CC) -I $(INC) $(CFLAGS) -D $(_STD_) -o $(COMPILED) $(SOURCEFILES)

manual:
		@clear
		@echo "Parsing from terminal..."
		./$(COMPILED)

auto:
		./$(COMPILED) samples/ejemplo17.alf outputsamples/ejemploalfa17.txt

hash_test: ## Test hash
	 	@$(CC) -I $(INC) -o run_hash_test $(SRC)hashTest.c $(SYMBOL) $(HASH)
		./run_hash_test

syntactic_test: all
		@ echo "\nExecuting first test"
		@ ./$(ALFA) $(TESTFILE1) $(TESTOUTPUT1)
		@ $(TEST_VERIFY) $(OUTPUT1) $(TESTOUTPUT1)

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
		@echo "Data cleaned."
