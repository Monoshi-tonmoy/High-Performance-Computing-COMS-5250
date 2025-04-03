CC = gcc
CFLAGS = -Wall -O3 -std=c99 -fopenmp
LDFLAGS = -lgomp -lm
TARGET = adaptive.exe

all: $(TARGET)

$(TARGET): adaptive.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean