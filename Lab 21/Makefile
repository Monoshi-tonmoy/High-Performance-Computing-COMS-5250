CC = mpicc
CFLAGS = -O3 -Wall -std=c99
LDFLAGS = -lm 
TARGET = trap_mpi.exe

all: $(TARGET)

$(TARGET): trap_mpi.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean