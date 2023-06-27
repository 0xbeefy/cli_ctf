CFLAGS += -lsqlite3

PHONY+=all
all: ctf

ctf: main.c
	$(CC) $(CFLAGS) -o $@ $^

PHONY+=clean
clean:
	rm ctf

.PHONY: $(PHONY)
