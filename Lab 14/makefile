CC = gcc
CFLAGS = -Wall -g
TARGET = main

# Listing all .c files except main.c
SRCS = add_matrix.c dot_mult_matrix.c matrix_mult_vector.c mult_matrix.c new_vector.c print_vector.c sub_matrix.c transpose_matrix.c add_vector.c dot_mult_vector.c new_matrix.c print_matrix.c solve.c sub_vector.c

# Generate object files from source files
OBJS = $(SRCS:.c=.o) main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Rule to compile .c files into .o files
%.o: %.c matrix.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run