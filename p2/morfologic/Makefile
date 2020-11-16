FILE = ejemplo1.l
TOKEN = tokens.h
CC = gcc

INC = inc/
DIR = files/
OUT = out/

OUT_NAME = parser
CYYLEX = lex.yy.c

default: $(CYYLEX)

all: $(CYYLEX)
		$(CC) -I $(INC) -Wall -o $(OUT)$(OUT_NAME) $(CYYLEX)


$(CYYLEX): $(INC)$(TOKEN)
		flex $(DIR)$(FILE)

exe:
		./$(OUT)$(OUT_NAME)

clean:
		rm -rf $(SRC)$(CYYLEX)
		rm -rf $(OUT)$(OUT_NAME)