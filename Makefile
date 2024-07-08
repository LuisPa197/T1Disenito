CC=g++
CFLAGS= -std=c++17 
BINS= explicito gap_coding huffman
OBJ=buscadores.o generadores.o

all: clean $(BINS)

buscadores.o: buscadores.cpp
	$(CC) $(CFLAGS) -c buscadores.cpp
generadores.o: generadores.cpp
	$(CC) $(CFLAGS) -c generadores.cpp
explicito: $(OBJ) explicito.cpp
	$(CC) $(CFLAGS) -o explicito explicito.cpp $(OBJ) 
gap_coding: $(OBJ) gap_coding.cpp
	$(CC) $(CFLAGS) -o gap_coding gap_coding.cpp $(OBJ) 
huffman: $(OBJ) huffman.cpp
	$(CC) $(CFLAGS) -o huffman huffman.cpp $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS) $(OBJ)
