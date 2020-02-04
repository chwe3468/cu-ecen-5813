# Name: makefile
# Description: makefile for project 1 for ECEN 5813 Principle of Embedded System Software
# Toolchain: gcc compiler version 7.4.0


XCC = gcc # Compiler
LD  = ld  # Linker
CFLAGS  = # Compiler Flags
LDFLAGS = -lc # Linker Flags

DEPS = # header files
OBJ1 = program_1.o
OBJ2 = program_2.o
OBJ3 = program_3.o

all: program_2 program_3 


program_1: $(OBJ1)
	$(XCC) -o $@ $^ $(CFLAGS)
program_1.o: program_1.c $(DEPS)
	$(XCC) 	-c -o $@ $<  $(CFLAGS)


program_2: $(OBJ2)
	$(XCC) -o $@ $^ $(CFLAGS)
program_2.o: program_2.c $(DEPS)
	$(XCC) 	-c -o $@ $<  $(CFLAGS)



program_3: $(OBJ3)
	$(XCC) -o $@ $^ $(CFLAGS)
program_3.o: program_3.c $(DEPS)
	$(XCC) 	-c -o $@ $<  $(CFLAGS)


clean:
	-rm -f program_3 *.o *.s