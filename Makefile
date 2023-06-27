CFLAGS += -lsqlite3

PHONY+=all
all: install

ctf: main.c
	@$(CC) $(CFLAGS) -o $@ $^

PHONY+=install
install: ctf
	@echo "Attempting to install to path..."
	@echo "This requires sudo privlieges. You will be asked to enter your password in the following input"
	@sudo cp ctf /usr/local/bin

PHONY+=clean
clean:
	@rm -rf ctf

.PHONY: $(PHONY)
