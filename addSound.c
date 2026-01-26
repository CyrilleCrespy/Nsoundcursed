// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

void addSound()
{
	// User provides (or should provide) a file (regular or directory).	
	char *file ;
	mvprintw(1, 3, _("Type (or paste) the absolute path of the file you want to add, or the directory whose audio files you want to copy in the nsoundcursed configuration.\n")) ;
	echo() ;
	file = malloc (sizeof(wchar_t) * FILENAME_MAX) ;
	getstr(file) ;
	
	// Then we do test if the input makes sense.
	
	struct stat st = {0} ;
	
	int exist = stat(file, &st) ;
	
	if (exist == -1)
	{
		clear() ;
		mvprintw(1, 3, _("Error using stat on the required file or directory : ")) ;
		mvprintw(2, 1, strerror(errno)) ;
		endwin() ;
		soundlist() ;
	}
	
	// The file exists. Is it a regular file ?
	
	if (S_ISDIR(st.st_mode) != 0) // The file is directory, we need to treat each file to see which one we can copy.
	{
		struct dirent *dir_s ;
		DIR *dir ;

		dir = opendir(file) ;
		
		// This is a dirty way of consuming . and ..
		readdir(dir) ;
		readdir(dir) ;
		
		while ((dir_s = readdir(dir)) != NULL)
		{
			char *source ;
			source = malloc(sizeof(file) + sizeof(dir_s->d_name) + sizeof(char)) ;
			snprintf(source, sizeof(file) + sizeof(dir_s->d_name) + sizeof(char), "%s/%s", file, dir_s->d_name) ;
      	int isAudio = checkIfaudio(source) ;
      	if (isAudio == 0)
      	{
      		copyAudio(source) ;
      	}
      	endwin() ;
      	soundlist() ;
      }
	}
	
	else if (S_ISREG(st.st_mode) != 0)
	{
		int isAudio = checkIfaudio(file) ;
		if (isAudio == 0)
		{
			copyAudio(file) ;
			endwin() ;
			soundlist() ;
		}
	}
	else 
	{
		mvprintw(3, 3, _("The file is NOT a regular file.\n")) ;
		getch() ;
		endwin() ;
		soundlist() ;
	}
}

void copyAudio(char *file)
{	
	FILE *file1, *file2 = NULL ;
   char ch ;
   char *target ;
   char *filename ;
   filename = malloc(sizeof(wchar_t) * FILENAME_MAX) ;
	filename = basename(file) ;
        	
	target = malloc(sizeof(wchar_t) * FILENAME_MAX) ;
   snprintf(target, (sizeof(wchar_t) * FILENAME_MAX), "%s/%s", folder, filename) ;
	
   file1 = fopen(file, "rb") ;
   file2 = fopen(target, "wb") ;
   
	while(!feof(file1))
   {
   	ch = fgetc(file1) ;
   	fputc(ch, file2) ;
   }
   fclose(file1) ;
   fclose(file2) ;	
}