CFLAGS= -g -Wall --pedantic   
EXEC=main
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
CC=g++-4.5



all: $(EXEC)
%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(EXEC): $(OBJ) main.cpp
	$(CC) $(CFLAGS) $(OBJ) main.cpp -o $(EXEC)

clean: rm *.o
