// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

void parseConfig(char *home)
{
	FILE *file = NULL ;
	char config[FILENAME_MAX] ;
	char buffer[256] ;
	//config = malloc(sizeof(char) * FILENAME_MAX) ;
	snprintf(config, sizeof(config) + sizeof(char) * 100, "%s/.config/nsoundboard/nsoundboard.conf", home) ;
	file = fopen(config, "r") ;
	if(file == NULL)
	{
		configFromshare(config) ;
	}
	fseek(file,0,SEEK_SET) ;

	while (fgets(buffer, sizeof(buffer), file))
	{
		char varName[100] ;
		char value[250] ;
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

int lineAnalyzer(char varName[100], char value[250])
{
	configuration.folder = malloc(sizeof(char) * 256) ;
	if(strcmp(varName,"folder") == 0)
	{
		snprintf(configuration.folder, sizeof(char) * FILENAME_MAX, value) ;
	}
	else
	{
		snprintf(configuration.folder, sizeof(char) * FILENAME_MAX, value) ;
	}
	return 0 ;
}

void configFromshare(char config[FILENAME_MAX])
{
        FILE *fichier1, *fichier2 = NULL ;
        char ch ;

        fichier1 = fopen("/usr/share/nsoundboard/nsoundboard.conf", "r") ;
        fichier2 = fopen(config, "w+") ;
    
        while((ch = getc(fichier1)) != EOF)
        {
                putc(ch, fichier2) ;
        }
        fclose(fichier1) ;
        fclose(fichier2) ;
}

void defaultConfig(char element) // In case the use is using the paramater default with any option,
				 // we wanna use a state that was defined at compile time.
				 // (compile time which also has default value, as you can see in Makefile)
{
}
