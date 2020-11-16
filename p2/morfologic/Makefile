FILE = ejemplo1_b.l
TOKEN = tokens.h

CC = gcc
FLAGS = -Wall -o

INC = inc/
DIR = files/
OUT = out/

TEST = flex/testfiles/
TESTFILE = $(TEST)test.txt

OUT_NAME = $(OUT)parser
CYYLEX = lex.yy.c

default: all

all: $(CYYLEX)
		$(CC) -I $(INC) $(FLAGS) $(OUT_NAME) $(CYYLEX)


$(CYYLEX): $(INC)$(TOKEN)
		flex $(DIR)$(FILE)

exe:
		./$(OUT_NAME)

test:
		./$(OUT_NAME) $(TESTFILE)

clean:
		rm -rf $(CYYLEX)
		rm -rf $(OUT)$(OUT_NAME)