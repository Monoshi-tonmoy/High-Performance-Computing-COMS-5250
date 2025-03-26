CC = gcc
CFLAGS = -Wall -O3 -std=c99 -fopenmp
LFLAGS = -lgomp -lm
SRC = main.c
EXE = main.exe

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE) $(LFLAGS)

clean:
	rm -f *.o $(EXE)

.PHONY: all clean
