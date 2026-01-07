// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

void soundlist()
{
	clear() ;
	wrefresh(win) ;
	keypad(stdscr, TRUE) ;

	char *home = getenv("HOME") ;
	if (home == NULL)
	{
		home = "/root" ;
	}

	parseConfig(home) ;
	
	//We default to the .config folder in the $HOME of the user.
	if(strcmp(configuration.folder,"default") == 0)
	{
		snprintf(folder, sizeof(char) * FILENAME_MAX, "%s/.config/nsoundboard", home) ;
	}
	else
	{
		snprintf(folder, sizeof(char) * FILENAME_MAX, "%s", configuration.folder) ;
	}
	
	mvprintw(1,2,"Liste des sons (+ pour ajouter)\n") ;
	mvprintw(2,2,"Répertoire analysé : %s\n", folder) ;

        int i = -1 ;
        DIR *dir ;
        struct dirent *dir_s ;

	dir = opendir(folder) ;

        if (dir)
        {
                while ((dir_s = readdir(dir)) != NULL)
                {
                        if (i <= 0) //Ignore . and ..
                        {
                                i ++ ;
                        }
                        else
                        {
                                items = malloc(sizeof(files[i-1])) ;
                                items[i-1] = new_item(files[i-1],files[i-1]) ;
                                snprintf(files[i-1],sizeof(files[i-1]),dir_s->d_name) ;
                                i ++ ;
                        }
                }
        }
        else
        {
                printw("Dossier %s introuvable ou inaccessible.\n", folder) ;
                refresh() ;
        }
        closedir(dir) ;


	printSoundlist(i,1) ;
	soundlistLoop(i) ;

	refresh() ;

	getch() ;
}

void soundlistLoop(int choices)
{
	int ch ;
	int selected = 1 ;
	while (true)
	{
		ch = getch() ;

		switch(ch)
		{
			case KEY_UP :
				if (selected == 1)
				{
					selected = choices - 1 ;
				}
				else
				{
					selected -- ;
				}
				break ;
			case KEY_DOWN :
				if (selected == choices - 1)
				{
					selected = 1 ;
				}
				else
				{
					selected ++ ;
				}
				break ;
			case '1' :
				playSound(1) ;
				break ;
			case '2' :
				playSound(2) ;
				break ;
			case '3' :
				playSound(3) ;
				break ;
			case '4' :
				playSound(4) ;
				break ;
			case '5' :
				playSound(5) ;
				break ;
			case '6' :
				playSound(6) ;
				break ;
			case '7' :
				playSound(7) ;
				break ;
			case '8' :
				playSound(8) ;
				break ;
			case '9' :
				playSound(9) ;
				break ;
			case 10 : //Enter key
				playSound(selected) ;
				break ;
			case '0' :
				endwin() ;
				clear() ;
				menu() ;
				break ;
			case 'q' :
				clear() ;
				endwin() ;
				exit(0) ;
				break ;
			case 'e' :
				eraseSound(choices, selected) ;
				break ;
		}
		printSoundlist(choices, selected) ;
	}
}

void printSoundlist(int choices, int selected)
{
	int i = 1 ;

	while (i < choices)
	{
		move(i + 2,0) ;
		clrtoeol() ;
		if(i == selected) //Make the current selected choice visible.
		{
			attron(A_BOLD | A_UNDERLINE | A_DIM | A_REVERSE) ;
			mvprintw(i + 2, 2, "%d) %s Erase (e)", i, files[i - 1]) ;
		}
		else
		{
			attroff(A_BOLD | A_UNDERLINE | A_DIM | A_REVERSE) ;
			mvprintw(i + 2, 2, "%d) %s", i, files[i - 1]) ;
		}
		//The first lines are taken permanently so we need to draw the menu starting after that.
		refresh() ;
		i ++ ;
	}
	wrefresh(win) ;
}

void playSound(int selected)
{
	char *file ;
	pid_t proc = fork() ;
	char *audioTool ;

	audioTool = malloc(sizeof(char) * 50) ;
	sprintf(audioTool, "mpg123") ;

	if (proc == -1)
	{
		perror("Fork failed.\n") ;
		exit(0) ;
	}
	else if (proc == 0)
	{
		setsid() ;
		file = malloc(sizeof(folder) + sizeof(files[selected - 1]) + 1) ;
		sprintf(file, "%s/%s", folder, files[selected - 1]) ;
	
		int out = open("/dev/null", O_RDWR);
		dup2(out, 0) ;
		dup2(out, 1) ;
		dup2(out, 2) ;
		close(out) ;
		execlp(audioTool, audioTool, file, (char *)NULL) ;	
	}
}

void eraseSound(int choices, int selected)
{
	char *file ;
	file = malloc(sizeof(folder)+sizeof(files[selected - 1])) ;
	sprintf(file, "%s/%s", folder, files[selected - 1]) ;
	remove(file) ;
	attroff(A_BOLD | A_UNDERLINE | A_DIM | A_REVERSE) ;
	soundlist() ;
}
