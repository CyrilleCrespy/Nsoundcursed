CC=gcc
CFLAGS=-Wall -Werror=all -pedantic -O3 -g -lncursesw -lmenu -lmagic

nsoundcursed: main.c
	$(CC) main.c -o nsoundcursed $(CFLAGS)
	msgfmt --output-file=locale/fr/fr.mo locale/fr/fr.po

install : nsoundcursed
	install -m755 nsoundcursed /usr/bin
	mkdir -p /usr/share/nsoundcursed
	install -m644 nsoundcursed.conf /usr/share/nsoundcursed/nsoundcursed.conf
	mkdir -p /usr/share/locale/fr/LC_MESSAGES
	install -m644 locale/fr/fr.mo /usr/share/locale/fr/LC_MESSAGES/nsoundcursed.mo

