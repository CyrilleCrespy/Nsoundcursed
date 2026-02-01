// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2026 Cyrille Crespy

#define _(String) gettext (String)

#include <limits.h>
#include <ncurses.h>
#include <menu.h>
#include <dirent.h>

int testSystem() ;
void parseConfig(char *home) ;
void lineAnalyzer(wchar_t *varName, wchar_t *value) ;
void configFromshare(char config[FILENAME_MAX]) ;
void menu() ;
void eraseSound(int choices, int selected) ;
void soundlist() ;
void addSound() ;
void copyAudio(char *file) ;
int checkIfaudio(char *file) ;
void soundlistLoop(int choices) ;
void printSoundlist(int choices, int selected);
void playSound(int selected) ;
void help() ;
void showHelp() ;
void firstSteps() ;
void configureHowTo() ;
void config() ;
void help() ;
void license () ;

char files[256][NAME_MAX +1] ;
char folder[NAME_MAX + 1] ;
ITEM **items ;
WINDOW *win ;
MENU *myMenu ;
char *home ;
char configFile[FILENAME_MAX] ;

// We define a structure that will hold the values of the user's configuration,
// like desired shortcuts or used folder.

typedef struct
{
	wchar_t *folder ;
	wchar_t back[1] ;
	wchar_t quit[1] ;
	wchar_t erase[1] ;
	wchar_t *playSound ;
	wchar_t *language ;
} Configuration ;

int compt = 0 ;

Configuration configuration ;