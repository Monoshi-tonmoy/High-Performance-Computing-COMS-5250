CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = stack_program
TARGET_EXE = main.exe
SRCS = main.c DeleteStack.c DisplayOptions.c DisplayStack.c GetStackSize.c Option.c Peek.c Pop.c Push.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET) $(TARGET_EXE)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TARGET_EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET_EXE) $(OBJS)

%.o: %.c stack.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(TARGET_EXE) $(OBJS)
