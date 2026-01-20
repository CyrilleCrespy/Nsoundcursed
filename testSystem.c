// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2025 Cyrille Crespy

int testSystem()
{
	pid_t proc = fork() ;
	if (proc < 0)
	{
		printf("Fork failed : %s.\n", strerror(errno)) ;
		return -2 ;
	}
	else if (proc == 0)
	{
		int out = open("/dev/null", O_RDWR) ;
		dup2(out, 0) ;
		dup2(out, 1) ;
		dup2(out, 2) ;
		close(out) ;
		int cvlc = execlp("cvlc", "--quiet", NULL) ;
		
		if(cvlc != 0)
		{
			printf("Soit cvlc n'est pas disponible, soit il n'est pas présent dans le PATH.\n\
Installer VLC avec votre gestionnaire de paquets peut résoudre le problème.\n") ;
			return -1 ;
		}
		return cvlc ;
	}
	else // The parent process will return something superior to 0, we catch that case so nsoundcursed doesn't catch it like an error.
	{
		return 0 ;
	}	
} 