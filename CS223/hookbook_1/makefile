CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

HookBook: hookbook.o pirate_list.o pirate.o
	$(CC) -o $@ $(CFLAGS) $^

hookbook.o: hookbook.c pirate_list.h pirate.h

pirate_list.o: pirate_list.c pirate_list.h pirate.h

pirate.o: pirate.h pirate.c

