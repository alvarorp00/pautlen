TARGET = main main_0_generacion main_2_generacion main_generacion

SRC = src/
INC = inc/
OBJ = obj/
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

default: $(TARGET)
all: default

.PHONY: clean
clean:
	# echo Cleaning files...
	rm -f $(OBJ)$(DISPOSABLE_OBJS)


main: $(OBJECTS)
	
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJECTS) $(LIBS)

main.o: $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) -c $@.c


.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<


compile:
	./compile.sh

exe:
	./out/generacion

.PRECIOUS: $(TARGET) $(OBJECTS)
