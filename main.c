// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

#include "main.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <locale.h>
#include <unistd.h>
#include <fcntl.h>
#include <magic.h>
#include <libintl.h>
#include <sys/stat.h>
#include "testSystem.c"
#include "configuration.c"
#include "soundlist.c"
#include "addSound.c"
#include "help.c"
#include "license.c"

int main()
{
	int test = testSystem() ;
	if (test != 0)
	{
		printf("%d \n", test) ;
		printf(_("Nsoundcursed will be closed : ")) ;
		printf("%s.\n", strerror(errno)) ;
		return -1 ;
	}
	noecho() ;
	cbreak() ;
	initscr() ;
	
	home = getenv("HOME") ;
	if (home == NULL)
	{
		home = "/root" ;
	}	
	
	parseConfig(home) ;
	myMenu = new_menu((ITEM **)items) ;
	win = newwin(LINES, COLS, 0, 0) ;
	box(win, 0, 0) ;
	noecho() ;
	wrefresh(win) ;
	keypad(stdscr, TRUE) ;
	
	if (strcmp(configuration.language, "default") == 0)
	{	
		setlocale (LC_ALL, "");
	}
	else 
	{
		setlocale (LC_ALL, configuration.language) ;
	}
	bindtextdomain ("nsoundcursed", "/usr/share/locale/");
	textdomain ("nsoundcursed");
		
	menu() ;
	return 0 ;	
}

void menu()
{
	clear() ;
	mvprintw(1, 3, _("Welcome to Nsoundcursed\n")) ;
	mvprintw(2, 3, _("1) Sound list\n")) ;
	mvprintw(3, 3, _("2) Help me\n")) ;
	mvprintw(4, 3, _("3) Licence\n")) ;

	wrefresh(win) ;

	while(true)
	{
		int ch = getch() ;

		if (ch == '1')
		{
			soundlist() ;
		}
		else if (ch == '2')
		{
			help() ;
		}
		else if (ch == '3')
		{
			license() ;
		}
		else if (ch == configuration.quit[0])
		{
			clear() ;
			endwin() ;
			exit(0) ;
		}
	}
	endwin() ;
}
