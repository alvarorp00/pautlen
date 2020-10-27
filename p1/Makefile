TARGET = main main_0_generacion main_2_generacion main_generacion

SRC = src/
INC = inc/
OBJ = obj/
OUT = out/
TEST = test/
LIB = lib/

LIBS = -lm
CC = gcc
INCLUDES = -I inc/
SOURCES = $(SRC)*.c
OBJECTS = $(OBJ)*.o $(LIB)*.o
HEADERS = $(INC)*.h
CFLAGS = -g -Wall -m32

VALGRIND = --leak-check=full --track-origins=yes

DISPOSABLE_OBJS = *.o
DISPOSABLE_OUTS = *

default: $(TARGET)
all: default

.PHONY: clean
clean:
	# echo Cleaning files...
	rm -f $(OBJ)$(DISPOSABLE_OBJS)
	rm -f $(OUT)$(DISPOSABLE_OUTS)

main: $(OBJECTS)
	
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJECTS) $(LIBS)

main.o: $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) -c $@.c


.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<


compile:
	./compile.sh


.PRECIOUS: $(TARGET) $(OBJECTS)
