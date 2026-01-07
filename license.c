// Nsoundboard, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

void license()
{
	clear() ;
	printw("Cette application est soumise à la licence GPLv2.0 et uniquement à cette version. \
Il est possible de consulter le texte en consultant le fichier COPYING, qui doit être fourni \
lors de la transmission de ce logiciel, que ce soit sous forme binaire ou en code source. \
Pressez une touche pour revenir au menu.") ;
	wrefresh(win) ;
	getch() ;
	menu() ;
}
