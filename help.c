// Nsoundboard, sound alert manager for Ncurses
// SPDX-License-Identifier: GLP-2.0-only
// Copyright (C) 2025 Cyrille Crespy

void help()
{
	showHelp() ;
	while(true)
	{
		int ch = getch() ;

		switch(ch)
		{
			case '1':
				firstSteps() ;
				break ;
			case '2':
				configureHowTo() ;
				break ;
			case 'q':
				clear() ;
				endwin() ;
				exit(0) ;
				break ;
			default:
				menu() ;
				break ;
		}
	}
}

void showHelp()
{
	clear() ;
	mvprintw(1,2,"1) Premiers pas\n") ;
	mvprintw(2,2,"2) Configuration\n") ;

	wrefresh(win) ;
}

void firstSteps()
{
	clear() ;
	printw("Le menu principal se pilote avec le pavé numérique (ou plus globalement les \
chiffres qui juxtent les différentes possibilités. La liste de lecture \
peut être pilotée avec les flèches directionnelles pour naviguer dans la liste, \
ou avec les raccourcis claviers pour les choix numérotés de 1 à 9. 0 permet \
de revenir au menu principal et 'q' de quitter l'application.") ;
}

void configureHowTo()
{
	clear() ;
	printw("Le fichier situé dans ~/.config/nsoundlist/nsoundlist.conf sert de base à la configuration. \
de l'outil. Le fichier repose sur un style simple : option=valeur. Il est lu à chaque \
fois que l'application est lancée. \
— folder définit le dossier de travail où sont cherchés les sons à lancer \
1) default est traduit automatiquement par ~/.config/nsoundconfig, en récupérant \
la valeur d'environnement $HOME du shell parent. Il peut aussi être défini \
au chemin absolu d'un répertoire dont l'utilisateur a les droits de lecture.") ;
}
