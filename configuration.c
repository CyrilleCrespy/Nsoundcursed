// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

void parseConfig(char *home)
{
	FILE *file = NULL ;
	char buffer[256] ;
	snprintf(configFile, sizeof(configFile) + sizeof(char) * 100, "%s/.config/nsoundcursed/nsoundcursed.conf", home) ;
	file = fopen(configFile, "r") ;

	configuration.folder = malloc(sizeof(char) * FILENAME_MAX) ;
	
	if(file == NULL)
	{
		configFromshare(configFile) ;
	}
	fseek(file,0,SEEK_SET) ;

	while (fgets(buffer, sizeof(buffer), file))
	{
		char varName[100] ;
		char value[FILENAME_MAX] ;
		const char  *separator = "=\n" ;
		char *token ;

		token = strtok(buffer, separator) ;
		strncpy(varName, token, sizeof(varName) - 1) ;

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
		snprintf(configuration.folder, sizeof(char) * FILENAME_MAX, value) ;
	}
	if(strcmp(varName, "back") == 0)
	{
		snprintf(&configuration.back, sizeof(char), value) ;
	}
	if(strcmp(varName, "quit") == 0)
	{
		snprintf(&configuration.quit, sizeof(char), value) ;
	}
	if(strcmp(varName, "erase") == 0)
	{
		snprintf(&configuration.erase, sizeof(char), value) ;
	}
	if(strcmp(varName, "sound_shortcuts") == 0)
	{
		snprintf(configuration.playSound, sizeof(char) * 20, value) ;
	}
}

void configFromshare(char config[FILENAME_MAX])
{
        FILE *fichier1, *fichier2 = NULL ;
        char ch ;

        fichier1 = fopen("/usr/share/nsoundcursed/nsoundcursed.conf", "r") ;
        fichier2 = fopen(config, "w+") ;
    
        while((ch = getc(fichier1)) != EOF)
        {
                putc(ch, fichier2) ;
        }
        fclose(fichier1) ;
        fclose(fichier2) ;
}