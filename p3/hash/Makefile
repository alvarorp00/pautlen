FILE = alfa.l
TOKEN = tokens.h

CC = gcc
CFLAGS = -Wall -g

INC = inc/
DIR = alfa/
OUT = out/
SRC = src/

TEST = testfiles/
RESULTS = testresults/

SYMBOLS = $(SRC)symbols.txt

TESTFILE1 = $(TEST)entrada1.txt
TESTFILE2 = $(TEST)entrada2.txt
TESTFILE3 = $(TEST)entrada3.txt

OUTPUT1 = $(TEST)salida1.txt
OUTPUT2 = $(TEST)salida2.txt
OUTPUT3 = $(TEST)salida3.txt

TESTOUTPUT1 = $(RESULTS)testoutput1.txt
TESTOUTPUT2 = $(RESULTS)testoutput2.txt
TESTOUTPUT3 = $(RESULTS)testoutput3.txt

ALFA = $(OUT)alfa

CYYLEX = lex.yy.c
OYYLEX = lex.yy.o

CALFA = $(DIR)alfa.c
OALFA = $(DIR)alfa.o

TEST_VERIFY = ./testverify.sh

default: all

all: clean $(OYYLEX) 
		$(CC) -I $(INC) $(CFLAGS) -o $(ALFA) $(OYYLEX) $(DIR)alfa.c $(SRC)hash.c


$(CYYLEX): $(INC)$(TOKEN)
		flex $(DIR)$(FILE)

$(OYYLEX): $(CYYLEX) $(INC)$(TOKEN)
		$(CC) -I $(INC) $(CFLAGS) -c $(CYYLEX)

exe:
		./$(ALFA)

hash:
		$(CC) -I $(INC) -o $(OUT)hash_test $(SRC)hash.c $(SRC)hash_test.c

hash_test: hash
		./$(OUT)hash_test

test: first_test second_test third_test

first_test:
		@ echo "\nExecuting first test"
		@ ./$(ALFA) $(TESTFILE1) $(TESTOUTPUT1)
		@ $(TEST_VERIFY) $(OUTPUT1) $(TESTOUTPUT1)

second_test:
		@ echo "\nExecuting second test"
		@ ./$(ALFA) $(TESTFILE2) $(TESTOUTPUT2)
		@ $(TEST_VERIFY) $(OUTPUT2) $(TESTOUTPUT2)

third_test:
		@ echo "\nExecuting third test"
		@ ./$(ALFA) $(TESTFILE3) $(TESTOUTPUT3)
		@ $(TEST_VERIFY) $(OUTPUT3) $(TESTOUTPUT3)

.PHONY: clean

clean:
		rm -rf $(CYYLEX)
		rm -rf $(OYYLEX)
		rm -rf $(OUT)*
		rm -rf $(RESULTS)*