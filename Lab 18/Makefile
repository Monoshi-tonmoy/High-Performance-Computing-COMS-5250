CC = gcc
CFLAGS = -Wall -O3 -std=c99 -fopenmp
LDFLAGS = -lgomp -lm
TARGET = simpson.exe

all: $(TARGET)

$(TARGET): simpson.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean