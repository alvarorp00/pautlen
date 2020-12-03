CC = gcc
CFLAGS = -g

_EXPLAIN_ = _EXPLAIN_

INC = inc/
SRC = src/
RESULTS = testresults/

TESTFILES = testfiles/

COMPILED = pruebaSintactico

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

all: ## Compile all. 
		@echo "Compiling all..."
		@$(CC) -I $(INC) $(CFLAGS) -o $(COMPILED) $(HASH) $(PHASH) $(TSYMBOLS) $(SYMBOL)

explain: ## Prints exec process in stdout
		@$(CC) -I $(INC) $(CFLAGS) -D $(_EXPLAIN_) -o $(COMPILED) $(HASH) $(PHASH) $(TSYMBOLS) $(SYMBOL)

test: ## Executes test and compares result
		@echo "Executing test..."
		./$(COMPILED) $(TESTFILEIN) $(TESTRESULT)
		@./testverify.sh $(TESTFILEOUT) $(TESTRESULT)

.PHONY: clean

clean: ## Cleans output files
		@rm -rf $(RESULTS)*
		@rm -rf $(COMPILED)
		@echo "Data cleaned."