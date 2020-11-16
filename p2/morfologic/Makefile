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

TEST_VERIFY = ./testverify.sh

default: all

all: $(CYYLEX)
		$(CC) -I $(INC) $(FLAGS) $(ALFA) $(CYYLEX)


$(CYYLEX): $(INC)$(TOKEN)
		flex $(DIR)$(FILE)

exe:
		./$(ALFA)

test1:
		./$(ALFA) $(TESTFILE1) $(TESTOUTPUT1)
		$(TEST_VERIFY) $(OUTPUT1) $(TESTOUTPUT1)

test2:
		./$(ALFA) $(TESTFILE2) $(TESTOUTPUT2)
		$(TEST_VERIFY) $(OUTPU2) $(TESTOUTPUT2)

test3:
		./$(ALFA) $(TESTFILE3) $(TESTOUTPUT3)
		$(TEST_VERIFY) $(OUTPU3) $(TESTOUTPUT3)

clean:
		rm -rf $(CYYLEX)
		rm -rf $(OUT)$(OUT_NAME)