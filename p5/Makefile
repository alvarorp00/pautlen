FLEXFILE = alfa.l
BISONFILE = alfa.y
TOKEN = tokens.h

CC = gcc
CFLAGS = -g
BISONFLAGS = -d -y -v

_STD_ = _STD_

_EXPLAIN_ = _EXPLAIN_

INC = inc/
DIR = alfa/
OUT = out/
OBJ = obj/
SRC = src/

RESULTS = testresults/
TESTFILES = testfiles/

COMPILED = program

CALFA = $(DIR)alfa.c
OALFA = $(OBJ)alfa.o

CYYLEX = $(SRC)lex.yy.c
OYYLEX = $(OBJ)lex.yy.o

CYYPARSE = $(SRC)y.tab.c
OYYPARSE = $(OBJ)y.tab.o

PHASH = $(SRC)pruebaTS.c
HASH = $(SRC)hash.c
TSYMBOLS = $(SRC)symbolsTable.c
SYMBOL = $(SRC)symbol.c

TESTFILEIN = $(TESTFILES)pruebaTS.txt
TESTFILEOUT = $(TESTFILES)expectedResTS.txt

TESTRESULT = $(RESULTS)testresult.txt

default: all ## Equivalent to 'make all'

help:	## This guide
		@@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

hash: ## Compile hash. 
		@echo "Compiling all..."
		@$(CC) -I $(INC) $(CFLAGS) -o $(COMPILED) $(HASH) $(PHASH) $(TSYMBOLS) $(SYMBOL)

explain: ## Prints exec process in stdout
		@$(CC) -I $(INC) $(CFLAGS) -D $(_EXPLAIN_) -o $(COMPILED) $(HASH) $(PHASH) $(TSYMBOLS) $(SYMBOL)

test: ## Executes test and compares result
		@echo "Executing test..."
		./$(COMPILED) $(TESTFILEIN) $(TESTRESULT)
		@./testverify.sh $(TESTFILEOUT) $(TESTRESULT)

syntactic: $(OALFA)
		@echo "Compiling all..."
		@$(CC) -I $(INC) $(CFLAGS) -D $(_STD_) -o $(COMPILED) $(OYYLEX) $(OYYPARSE) $(OALFA)

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

.PHONY: clean

clean: ## Cleans output files
		@rm -rf $(RESULTS)*
		@rm -rf $(COMPILED)
		@rm $(OYYLEX)
		@rm $(OYYPARSE)
		@rm $(CYYLEX)
		@rm $(CYYPARSE)
		@echo "Data cleaned."