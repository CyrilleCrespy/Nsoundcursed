// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

void soundlist()
{
	clear() ;
	wrefresh(win) ;
	keypad(stdscr, TRUE) ;

	if(strcmp(configuration.folder,"default") == 0)
	{
		snprintf(folder, sizeof(char) * FILENAME_MAX, "%s/.config/nsoundcursed", home) ;
	}
	else
	{
		snprintf(folder, sizeof(char) * FILENAME_MAX, "%s", configuration.folder) ;
	}
	
	mvprintw(1, 3, _("Sound list (press + to add)\n")) ;
	mvprintw(2, 3, _("Checked folder : \n")) ;
	mvprintw(2, 3, "%s.\n", folder) ;

   int i = -1 ;
	int nbFiles = 0 ;
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
                                int isAudio = checkIfaudio(dir_s) ;
				if (isAudio == 0) 
				{
					items = malloc(sizeof(files[nbFiles])) ;
                               	items[nbFiles] = new_item(files[nbFiles],files[nbFiles]) ;
                                	snprintf(files[nbFiles],sizeof(files[nbFiles]),dir_s->d_name) ;
                                	i ++ ;
					nbFiles ++ ;
				}
				else
				{
					i++ ;
					continue ;
				}
                        }
                }
        }
        else
        {
                printw(_("Folder does not exist / is not reachable : ")) ;
                printw("%s.\n", folder) ;
                refresh() ;
        }
        closedir(dir) ;


	printSoundlist(nbFiles,1) ;
	soundlistLoop(nbFiles) ;

	refresh() ;

	getch() ;
}

int checkIfaudio(struct dirent *dir_s)
{
	// We check what is the magic number of a file to determine its mime.
	// Then, we can decide wether to print it on the list or not.
	char *file ;
	file = malloc(sizeof(folder) + sizeof(dir_s->d_name) + sizeof(char)) ;
	snprintf(file, sizeof(folder) + sizeof(dir_s->d_name) + sizeof(char), "%s/%s", folder, dir_s->d_name) ;
	magic_t mime = magic_open(MAGIC_MIME_TYPE) ;
	int isLoadOK = magic_load(mime, NULL) ;
	if (isLoadOK != 0)
	{
		clear() ;
		endwin() ;
		printf(_("Loading the magic number failed.\n")) ;
		exit(0) ;
	}
	const char *type = magic_file(mime, file) ;
	if(mime == NULL)
	{
		clear() ;
		endwin() ;
		printf(_("No MIME type detected for the file : \n")) ;
		printf("%s .", file) ;
	}

	// MIME-mimes are retrieved as strings such like audio/mpeg.
	// We want to determine if the first part is audio.
	const char *separator = "/" ;
	const char *token ;

	token = strtok(type, separator) ;

	if (strcmp(token, "audio") == 0)
	{
		// This is an audio file (apparently). We tell that to the function that print the list.
		// Because we DO want audio files in the program, this is returned as no error.
		return 0 ;
	}
	else	
	{
		// Non-blocking error, we will just disregard that file.
		return 1 ;
	}
}

void soundlistLoop(int choices)
{
	int ch ;
	int selected = 1 ;
	while (true)
	{
		ch = getch() ;

		if (ch == KEY_UP)
		{
			if (selected == 1)
				{
					selected = choices ;
				}
				else
				{
					selected -- ;
				}
		}
		else if (ch == KEY_DOWN)
		{
			if (selected == choices)
			{
				selected = 1 ;
			}
			else
			{
				selected ++ ;
			}
		}		
		else if (ch == 10) // Enter key
		{
				playSound(selected - 1) ;
		}
		else if (ch == configuration.back[0]) // Return to main menu
		{
			endwin() ;
			clear() ;
			menu() ;
		}
		else if (ch == configuration.quit[0])
		{
			clear() ;
			endwin() ;
			exit(0) ;
		}
		else if (ch == configuration.erase[0])
		{
				eraseSound(choices, selected) ;
		}
		
		int i ;
		for (i = 0 ; i < 20 ; i++)
		{
			if (ch == configuration.playSound[i])
			{
				playSound(i) ;
			}
		}
		printSoundlist(choices, selected) ;	
	}
}

void printSoundlist(int choices, int selected)
{
	int i = 1 ;

	while (i <= choices)
	{
		move(i + 2,0) ;
		clrtoeol() ;
		if(i == selected) //Make the current selected choice visible.
		{
			attron(A_BOLD | A_UNDERLINE | A_DIM | A_REVERSE) ;
			mvprintw(i + 2, 3, "%d) %s Erase (e)", i, files[i - 1]) ;
		}
		else
		{
			attroff(A_BOLD | A_UNDERLINE | A_DIM | A_REVERSE) ;
			mvprintw(i + 2, 3, "%d) %s", i, files[i - 1]) ;
		}
		// The first lines are taken permanently so we need to draw the menu starting after that.
		refresh() ;
		i ++ ;
	}
	wrefresh(win) ;
}

void playSound(int selected)
{
	char *file ;
	pid_t proc = fork() ;

	if (proc < 0)
	{
		printf("Fork failed : %s.\n", strerror(errno)) ;
	}
	else if (proc == 0)
	{
		file = malloc(sizeof(folder) + sizeof(files[selected]) + 1) ;
		snprintf(file, 65792, "%s/%s", folder, files[selected]) ;
	
		int out = open("/dev/null", O_RDWR);
		dup2(out, 0) ;
		dup2(out, 1) ;
		dup2(out, 2) ;
		close(out) ;
		execlp("cvlc", "clvc", file, "--no-loop", "--play-and-exit", NULL) ;
		exit(0) ;
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
