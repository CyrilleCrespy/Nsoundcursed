// Nsoundboard, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <locale.h>
#include <unistd.h>
#include <fcntl.h>
#include "configuration.c"
#include "soundlist.c"
#include "help.c"
#include "license.c"

int main()
{
	noecho() ;
	cbreak() ;
	initscr() ;
	setlocale(LC_ALL, "fr_FR.UTF8") ;
	myMenu = new_menu((ITEM **)items) ;
	win = newwin(LINES,COLS,0,0) ;
	box(win,0,0) ;
	noecho() ;
	wrefresh(win) ;
	keypad(stdscr, TRUE) ;
	menu() ;
	return 0 ;	
}

void menu()
{
	clear() ;
	mvprintw(1,2,"Bienvenue dans Nsoundboard\n") ;
	mvprintw(2,2,"1) Liste des sons\n") ;
	mvprintw(3,2,"2) Aide\n") ;
	mvprintw(4,2,"3) License\n") ;

	wrefresh(win) ;

	while(true)
	{
		int ch = getch() ;

		switch(ch)
		{
			case '1':
				soundlist() ;
				break ;
			case '2':
				help() ;
				break ;
			case '3':
				license() ;
				break ;
			case 'q':
				clear() ;
				endwin() ;
				exit(0) ;
				break ;
		}
	}

	endwin() ;
}
