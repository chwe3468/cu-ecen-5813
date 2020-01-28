# Name: makefile
# Description: makefile for project 1 for ECEN 5813 Principle of Embedded System Software
# Toolchain: gcc compiler version 7.4.0


XCC = gcc # Compiler
LD  = ld  # Linker
CFLAGS  = # Compiler Flags
LDFLAGS = -lc # Linker Flags

DEPS = # header files
OBJ = program_3.o

%.o: %.c $(DEPS)
	$(XCC) 	-c -o $@ $<  $(CFLAGS)

program_3: $(OBJ)
	$(XCC) -o $@ $^ $(CFLAGS)

clean:
	-rm -f program_3 *.o *.s