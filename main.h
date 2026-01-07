// Nsoundboard, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

#include <limits.h>
#include <curses.h>
#include <menu.h>

void parseConfig(char *home) ;
int lineAnalyzer(char varName[100], char value[250]) ;
void configFromshare(char config[FILENAME_MAX]) ;
void menu() ;
void eraseSound(int choices, int selected) ;
void soundlist() ;
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

typedef struct
{
	char *folder ;
} Configuration ;

Configuration configuration ;
