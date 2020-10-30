CC = gcc
CFLAGS = -O -Wall -m64 -std=gnu11
LIBS = -lm

dining: myipc.h myipc.c Dining_philosopher.c
	$(CC) -g myipc.c myipc.h Dining_philosopher.c -o dining
clean:
	rm dining

