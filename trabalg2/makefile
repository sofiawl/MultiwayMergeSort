CC = gcc
CFLAGS = -Wall -O2
TARGET = main

OBJ = main.o auxiliar.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c auxiliar.h
	$(CC) $(CFLAGS) -c main.c

auxiliar.o: auxiliar.c auxiliar.h
	$(CC) $(CFLAGS) -c auxiliar.c

clean:
	rm -f $(TARGET) *.o run*.txt
