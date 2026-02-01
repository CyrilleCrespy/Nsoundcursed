// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2026 Cyrille Crespy

void parseConfig(char *home)
{
	FILE *file = NULL ;
	wchar_t buffer[256] ;
	char folder[256] ;
	struct stat st = {0} ;
	snprintf(folder, sizeof(char) * 256, "%s/.config/nsoundcursed", home) ;

	if (stat(folder, &st) == -1)
	{
		mkdir(folder, 0755) ;
		sleep(2) ;
	}	
	
	configuration.language = malloc(sizeof(wchar_t) * 20) ;
	configuration.language = L"default" ;

	snprintf(configFile, sizeof(configFile) + sizeof(char) * 100, "%s/.config/nsoundcursed/nsoundcursed.conf", home) ;
	file = fopen(configFile, "r") ;

	configuration.folder = malloc(sizeof(char) * FILENAME_MAX) ;

	if(file == NULL)
	{
		configFromshare(configFile) ;
		file = fopen(configFile, "r") ;
	}
	fseek(file, 0, SEEK_SET) ;

	while (fgetws(buffer, sizeof(buffer), file))
	{
		wchar_t *varName ;
		wchar_t *value ;
		const wchar_t  *separator = L"=\n" ;
		wchar_t *ptr ;
		wchar_t *token ;

		varName = malloc(sizeof(wchar_t) * FILENAME_MAX) ;
		value = malloc(sizeof(wchar_t) * FILENAME_MAX) ;
		token = wcstok(buffer, separator, &ptr) ;
		wcsncpy(varName, token, sizeof(varName)) ;
		
		if (wcscmp(varName, L"") == 0)
		{
			continue ; //The line is empty, forget about it.
		}

		token = wcstok(NULL, separator, &ptr) ;		
		
		if (token == NULL) //The line does not contain an equal sign, thus the data is incorrect.
		{
			continue ;
		}
				
		wcscpy(value, token) ;
		
		lineAnalyzer(varName, value) ;
	}

	fclose(file) ; 
}

void lineAnalyzer(wchar_t *varName, wchar_t *value)
{
	if(wcscmp(varName, L"folder") == 0)
	{
		swprintf(configuration.folder, sizeof(wchar_t) * FILENAME_MAX, value) ;
	}
	else if(wcscmp(varName, L"back") == 0)
	{
		swprintf(configuration.back, sizeof(wchar_t), value) ;
	}
	else if(wcscmp(varName, L"quit") == 0)
	{
		swprintf(configuration.quit, sizeof(wchar_t), value) ;
	}
	else if(wcscmp(varName, L"erase") == 0)
	{
		swprintf(configuration.erase, sizeof(wchar_t), value) ;
	}
	else if(wcscmp(varName, L"play") == 0)
	{
		configuration.playSound = malloc(sizeof(wchar_t) * 100) ;
		memset(configuration.playSound, 0, sizeof(wchar_t) * 100) ;
		swprintf(configuration.playSound, sizeof(wchar_t) * 100, value) ;
	}
	else if(wcscmp(varName, L"language") == 0 && wcscmp(value, L"default") != 0)
	{
		configuration.language = malloc(sizeof(wchar_t) * 20) ;
		memset(configuration.language, 0, sizeof(wchar_t) * 20) ;
		swprintf(configuration.language, sizeof(wchar_t) * 20, value) ;
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