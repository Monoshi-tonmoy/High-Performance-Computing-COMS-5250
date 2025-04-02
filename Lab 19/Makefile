CC = gcc
CFLAGS = -Wall -O3 -std=c99 -fopenmp
LDFLAGS = -lgomp -lm
TARGET = normalize.exe

all: $(TARGET)

$(TARGET): normalize.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean