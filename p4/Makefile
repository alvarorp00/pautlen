FLEXFILE = alfa.l
BISONFILE = alfa.y
TOKEN = tokens.h

CC = gcc
CFLAGS = -g
BISONFLAGS = -d -y -v

_EXPLAIN_ = _EXPLAIN_

INC = inc/
DIR = alfa/
OUT = out/
OBJ = obj/
SRC = src/
OTHER = other/

SYMBOLS = $(SRC)symbols.txt

COMPILED = $(OUT)pruebaSintactico

PHASH = $(SRC)pruebaTS.c
HASH = $(SRC)hash.c
TSYMBOLS = $(SRC)symbolsTable.c
SYMBOL = $(SRC)symbol.c

default: all ## Equivalent to 'make all'

help:	## This guide
		@@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

all: ## Compile all. 
		@echo "Compiling all..."
		@$(CC) -I $(INC) $(CFLAGS) -o pruebaSintactico $(HASH) $(PHASH) $(TSYMBOLS) $(SYMBOL)

explain:
		@$(CC) -I $(INC) $(CFLAGS) -D $(_EXPLAIN_) -o pruebaSintactico $(HASH) $(PHASH) $(TSYMBOLS) $(SYMBOL)

hash:
		$(CC) -I $(INC) $(CFLAGS) -o pruebaSintactico $(HASH) $(PHASH) $(TSYMBOLS) $(SYMBOL)

.PHONY: clean

# clean: ## Cleans output files
# 		@rm -rf $(CYYLEX)
# 		@rm -rf $(CYYPARSE)
# 		@rm -rf $(INC)y.tab.h
# 		@rm -rf $(OUT)*
# 		@rm -rf $(OBJ)*
# 		@rm -rf $(RESULTS)*
# 		@rm -rf y.output
# 		@echo "Data cleaned.