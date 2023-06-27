all: ctf

ctf: main.c
	gcc -o $@ $^
