CFLAGS += -lsqlite3

all: ctf

ctf: main.c
	$(CC) $(CFLAGS) -o $@ $^
