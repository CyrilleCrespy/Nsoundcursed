// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GLP-2.0-only
// Copyright (C) 2025 Cyrille Crespy

void help()
{
	showHelp() ;
	while(true)
	{
		int ch = getch() ;

		if (ch == configuration.quit[0])
		{
				clear() ;
				endwin() ;
				exit(0) ;
		}

		switch(ch)
		{
			case '1':
				firstSteps() ;
				break ;
			case '2':
				configureHowTo() ;
				break ;
			default:
				menu() ;
				break ;
		}
	}
}

void showHelp()
{
	clear() ;
	mvprintw(1,2, _("1) First steps\n")) ;
	mvprintw(2,2,_("2) Configuration\n")) ;

	wrefresh(win) ;
}

void firstSteps()
{
	clear() ;
	printw(_("The main menu can be managed with numeric keyboard (or more generally with numbers \
close the different choices. Playlist can be piloted from arrow keys to move the selected choice, \
or with shortcuts for choices numeroted from 1 to 9. 0 allow to go back to the main menu, 'q' makes \
the application quits.")) ;
}

void configureHowTo()
{
	clear() ;
	printw(_("The file located in ~/.config/nsoundlist.conf is the foundation of this tool. It relies \
on a simple syntax : option=value. The application reads it at launch time. \
- folder defines the working directory where sounds to launch are. \
1) default is automatically translated into ~/.config/nsoundconfig, by retrieving \
the $HOME value of the parent shell. \
2) it can also be defined on which the user as reading rights.")) ;
}