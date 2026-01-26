// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

void parseConfig(char *home)
{
	FILE *file = NULL ;
	char buffer[256] ;
	char folder[256] ;
	struct stat st = {0} ;
	snprintf(folder, sizeof(char) * 256, "%s/.config/nsoundcursed", home) ;

	if (stat(folder, &st) == -1)
	{
		mkdir(folder, 0755) ;
		sleep(2) ;
	}	
	
	configuration.language = malloc(sizeof(wchar_t) * 20) ;
	configuration.language = "default" ;

	snprintf(configFile, sizeof(configFile) + sizeof(char) * 100, "%s/.config/nsoundcursed/nsoundcursed.conf", home) ;
	file = fopen(configFile, "r") ;

	configuration.folder = malloc(sizeof(char) * FILENAME_MAX) ;

	if(file == NULL)
	{
		configFromshare(configFile) ;
		file = fopen(configFile, "r") ;
	}
	fseek(file, 0, SEEK_SET) ;

	while (fgets(buffer, sizeof(buffer), file))
	{
		char varName[100] ;
		char value[FILENAME_MAX] ;
		const char  *separator = "=\n" ;
		char *token ;

		token = strtok(buffer, separator) ;
		strncpy(varName, token, sizeof(varName) - 1) ;
		
		if (strcmp(varName, "") == 0)
		{
			continue ; //The line is empty, forget about it.
		}

		token = strtok(NULL, separator) ;
		if (token == NULL) //The line does not contain an equal sign, thus the data is incorrect.
		{
			continue ;
		}

		strncpy(value, token, sizeof(value) - 1) ;		
		
		lineAnalyzer(varName, value) ;
	}

	fclose(file) ; 
}

void lineAnalyzer(char varName[100], char value[FILENAME_MAX])
{
	if(strcmp(varName, "folder") == 0)
	{
		snprintf(configuration.folder, sizeof(wchar_t) * FILENAME_MAX, value) ;
	}
	else if(strcmp(varName, "back") == 0)
	{
		snprintf(configuration.back, sizeof(wchar_t), value) ;
	}
	else if(strcmp(varName, "quit") == 0)
	{
		snprintf(configuration.quit, sizeof(wchar_t), value) ;
	}
	else if(strcmp(varName, "erase") == 0)
	{
		snprintf(configuration.erase, sizeof(wchar_t), value) ;
	}
	else if(strcmp(varName, "sound_shortcuts") == 0)
	{
		configuration.playSound = malloc (sizeof(wchar_t) * 20) ;
		snprintf(configuration.playSound, sizeof(wchar_t) * 20, value) ;
	}
	else if(strcmp(varName, "language") == 0 && strcmp(value, "default") != 0)
	{
		configuration.language = malloc(sizeof(wchar_t) * 20) ;
		memset(configuration.language, 0, sizeof(wchar_t) * 20) ;
		snprintf(configuration.language, sizeof(wchar_t) * 20, value) ;
	}
}

void configFromshare(char config[FILENAME_MAX])
{
        FILE *file1, *file2 = NULL ;
        char ch ;

        file1 = fopen("/usr/share/nsoundcursed/nsoundcursed.conf", "r") ;
        file2 = fopen(config, "w") ;
    
        while((ch = getc(file1)) != EOF)
        {
                putc(ch, file2) ;
        }
        fclose(file1) ;
        fclose(file2) ;
}