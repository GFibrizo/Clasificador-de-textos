CFLAGS= -g -Wall --pedantic   
EXEC=main
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
CC=g++-4.5
CC2=gcc


all: $(EXEC)


%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $<
Porter.o: src/Porter.c
	$(CC2) $(CFLAGS) -c src/Porter.c


$(EXEC): $(OBJ) main.cpp
	$(CC) $(CFLAGS) $(OBJ) main.cpp -o $(EXEC)

clean: rm src/*.o
	   rm *.o
