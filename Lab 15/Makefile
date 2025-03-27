CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lm  # linking is required

# List of source files
SRCS = main.c matrix.c trimatrix.c Hessenberg.c QRA.c QRdecomp.c FindZero.c GetShift.c
OBJS = $(SRCS:.c=.o)

# Target name
TARGET = main

# Default rule to build the target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)  

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean