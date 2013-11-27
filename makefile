CFLAGS= -g -Wall --pedantic -std=c++0x
EXEC=main
SRC=$(wildcard src/*.cpp)
OBJ1=$(SRC:.cpp=.o)
OBJ = ManejadorArchivos.o LectorDirectorios.o PreProcesarDatos.o VerificadorStopWords.o Porter.o Punto.o Clasificador.o Arista.o Cluster.o Clustering.o KMeans.o
CC=g++
CC2=gcc


all: $(EXEC)

src/Porter.o: src/Porter.c src/Porter.h
	$(CC2) $(CFLAGS) -c src/Porter.c

src/%.o: src/%.cpp src/%.h
	$(CC) $(CFLAGS) -c $<

$(EXEC): $(OBJ1) src/Porter.o main.cpp
	$(CC) $(CFLAGS) $(OBJ) main.cpp -o $(EXEC)

clean: 
		rm -f *.o  $(EXEC)

