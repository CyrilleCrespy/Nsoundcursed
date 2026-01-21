// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

void license()
{
	clear() ;
	printw(_("Licence GPLv2.0, and only thio particular version, applies to this application. \
It is possible to read the text in its full extent by consulting the file COPYING, which must be provided \
when sharing this software, either as binary or as source code. Press any key to go back to main menu.")) ;
	wrefresh(win) ;
	getch() ;
	menu() ;
}
