FILE = ejemplo1.l
TOKEN = tokens.h
CC = gcc

INC = inc/
DIR = files/
SRC = 
OUT = out/

OUT_NAME = parser
CYYLEX = $(SRC)lex.yy.c

default: all

all: $(CYYLEX) $(INC)$(TOKEN)
		$(CC) -I $(INC) -Wall -o $(OUT)$(OUT_NAME) $(CYYLEX)


$(CYYLEX): $(INC)$(TOKEN)
		flex $(DIR)$(FILE)
		mv $(CYYLEX) $(SRC)

exe:
		./$(OUT)$(OUT_NAME)

clean:
		rm -rf $(SRC)$(CYYLEX)
		rm -rf $(OUT)$(OUT_NAME)