// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

#define _(String) gettext (String)

#include <limits.h>
#include <curses.h>
#include <menu.h>
#include <dirent.h>

int testSystem() ;
void parseConfig(char *home) ;
int lineAnalyzer(char varName[100], char value[250]) ;
void configFromshare(char config[FILENAME_MAX]) ;
void menu() ;
void eraseSound(int choices, int selected) ;
void soundlist() ;
int checkIfaudio(struct dirent *dir_s) ;
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

char files[256][NAME_MAX+1] ;
char folder[NAME_MAX + 1] ;
ITEM **items ;
WINDOW *win ;
MENU *myMenu ;
char *home ;
char configFile[FILENAME_MAX] ;

typedef struct
{
	char *folder ;
	char playSound[10] ;
	char goBack[1] ;
} Configuration ;

Configuration configuration ;