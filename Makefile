CC=gcc
CFLAGS=-Wall -Werror=all -pedantic -O3 -g -lcurses -lmenu

nsoundboard: main.c
	$(CC) main.c -o nsoundboard $(CFLAGS)

install : nsoundboard
	install -m755 nsoundboard /usr/bin
	mkdir -p /usr/share/nsoundboard
	install -m644 nsoundboard.conf /usr/share/nsoundboard/nsoundboard.conf
