FILE = alfa.l
TOKEN = tokens.h

CC = gcc
FLAGS = -Wall -o

INC = inc/
DIR = alfa/
OUT = out/

TEST = flex/testfiles/

TESTFILE1 = $(TEST)entrada1.txt
TESTFILE2 = $(TEST)entrada2.txt
TESTFILE3 = $(TEST)entrada3.txt

TESTOUTPUT1 = $(TEST)testoutput1.txt
TESTOUTPUT2 = $(TEST)testoutput2.txt
TESTOUTPUT3 = $(TEST)testoutput3.txt

OUTPUT1 = $(TEST)salida1.txt
OUTPUT2 = $(TEST)salida2.txt
OUTPUT3 = $(TEST)salida3.txt

ALFA = $(OUT)alfa
CYYLEX = lex.yy.c

default: all

all: $(CYYLEX)
		$(CC) -I $(INC) $(FLAGS) $(ALFA) $(CYYLEX)


$(CYYLEX): $(INC)$(TOKEN)
		flex $(DIR)$(FILE)

exe:
		./$(ALFA)

test1:
		./$(ALFA) $(TESTFILE1) $(TESTOUTPUT1)
		cmp --silent $(OUTPUT1) $(TESTOUTPUT1) || echo "test1 failure"

test2:
		./$(ALFA) $(TESTFILE2) $(TESTOUTPUT2)
		cmp --silent $(OUTPUT2) $(TESTOUTPUT2) || echo "test2 failure"

test3:
		./$(ALFA) $(TESTFILE3) $(TESTOUTPUT3)
		cmp --silent $(OUTPUT3) $(TESTOUTPUT3) || echo "test3 failure"

clean:
		rm -rf $(CYYLEX)
		rm -rf $(OUT)$(OUT_NAME)