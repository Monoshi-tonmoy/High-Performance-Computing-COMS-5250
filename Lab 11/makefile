#using macros

CC = gcc
CFLAGS = -O3 -Wall
OBJECTS = main.o GenerateList.o Print.o GetKey.o SearchList.o DeleteList.o GetNumberOfNodes.o

.PHONY: clean

main.exe: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) main.exe