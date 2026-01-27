// Nsoundcursed, sound alert manager for Ncurses
// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2026 Cyrille Crespy

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
			printf(_("Either cvlc isn't available, either it's not in the PATH. \n\
Installing VLC in your packet manager may solve the problem.")) ;
			return -1 ;
		}
		return cvlc ;
	}
	else // The parent process will return something superior to 0, we catch that case so nsoundcursed doesn't catch it like an error.
	{
		return 0 ;
	}	
} 