# Name: makefile
# Description: makefile for project 1 for ECEN 5013 AESD
# Toolchain: gcc compiler version 7.4.0

CC = gcc # Compiler
LD  = ld  # Linker
CFLAGS  = -Werror -Wall # Compiler Flags
LDFLAGS = -lc # Linker Flags
CROSS_COMPILE = # Cross compile option for arm-unknown-linux-gnueabi-

DEPS = timer.h log.h # header files
OBJ = timer.o PES_Project_2.o

all:  PES_Project_2 timer

PES_Project_2: $(OBJ)
	$(CROSS_COMPILE)$(CC) -o $@ $^ $(CFLAGS)

timer: $(OBJ)
	$(CROSS_COMPILE)$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	$(CROSS_COMPILE)$(CC) 	-c -o $@ $<  $(CFLAGS)

clean:
	-rm -f PES_Project_2 timer *.o *.s