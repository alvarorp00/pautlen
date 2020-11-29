FLEXFILE = alfa.l
BISONFILE = alfa.y
TOKEN = tokens.h

CC = gcc
CFLAGS = -Wall -g
BISONFLAGS = -d -y -v

_STD_ = _STD_

INC = inc/
DIR = alfa/
OUT = out/
OBJ = obj/
SRC = src/
OTHER = other/

TEST = testfiles/
RESULTS = testresults/

SYMBOLS = $(SRC)symbols.txt

TESTFILE1 = $(TEST)entrada_sin_1.txt
TESTFILE2 = $(TEST)entrada_sin_2.txt
TESTFILE3 = $(TEST)entrada_sin_3.txt

OUTPUT1 = $(TEST)salida_sin_1.txt
OUTPUT2 = $(TEST)salida_sin_2.txt
OUTPUT3 = $(TEST)salida_sin_3.txt

TESTOUTPUT1 = $(RESULTS)testoutput_sin_1.txt
TESTOUTPUT2 = $(RESULTS)testoutput_sin_2.txt
TESTOUTPUT3 = $(RESULTS)testoutput_sin_3.txt

ALFA = $(OUT)pruebaMorfo

CALFA = $(DIR)alfa.c
OALFA = $(OBJ)alfa.o

CYYLEX = $(SRC)lex.yy.c
OYYLEX = $(OBJ)lex.yy.o

CYYPARSE = $(SRC)y.tab.c
OYYPARSE = $(OBJ)y.tab.o

TEST_VERIFY = ./testverify.sh

default: all ## Equivalent to 'make all'

help:	## This guide
		@@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

all: clean $(OALFA) ## Compile all. 
		@echo "Compiling all..."
		@$(CC) -I $(INC) $(CFLAGS) -o $(ALFA) $(OYYLEX) $(OYYPARSE) $(OALFA)

exe_manual: clean $(OYYLEX) $(OYYPARSE) ## Executes with yyin as stdin & yyout as stdout.
		@$(CC) -I $(INC) $(CFLAGS) -D $(_STD_) -o $(ALFA) $(OYYLEX) $(OYYPARSE) $(DIR)alfa.c
		@clear
		@echo "Executing no input nor output file. Using stdin & stdout."
		@./$(ALFA)

manual: ## Same as exe_manual without recompiling
		@./$(ALFA)

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
		@mv y.tab.h $(INC).
		@mv y.tab.c $(SRC).

$(OYYPARSE): $(CYYPARSE)
		@echo "Generating y.tab.o"
		@$(CC) -I $(INC) $(CFLAGS) -c $(CYYPARSE)
		@mv y.tab.o $(OBJ).

test_all: all test_first test_second test_third ## Executes all tests
test_first: all ## Executes first test
		@ echo "\nExecuting first test"
		@ ./$(ALFA) $(TESTFILE1) $(TESTOUTPUT1)
		@ $(TEST_VERIFY) $(OUTPUT1) $(TESTOUTPUT1)

test_second: all ## Executes second test
		@ echo "\nExecuting second test"
		@ ./$(ALFA) $(TESTFILE2) $(TESTOUTPUT2)
		@ $(TEST_VERIFY) $(OUTPUT2) $(TESTOUTPUT2)

test_third: all ## Executes third test
		@ echo "\nExecuting third test"
		@ ./$(ALFA) $(TESTFILE3) $(TESTOUTPUT3)
		@ $(TEST_VERIFY) $(OUTPUT3) $(TESTOUTPUT3)

.PHONY: clean

clean: ## Cleans output files
		@rm -rf $(CYYLEX)
		@rm -rf $(CYYPARSE)
		@rm -rf $(INC)y.tab.h
		@rm -rf $(OUT)*
		@rm -rf $(OBJ)*
		@rm -rf $(RESULTS)*
		@rm -rf y.output
		@echo "Data cleaned."
