/** MODIFIED    **/

/****************************************************************
**                                                             **
**    Copyright (c) 1996 - 2001 Caldera International, Inc.    **
**                    All Rights Reserved.                     **
**                                                             **
** This program is free software; you can redistribute it      **
** and/or modify it under the terms of the GNU General Public  **
** License as published by the Free Software Foundation;       **
** either version 2 of the License, or (at your option) any    **
** later version.                                              **
**                                                             **
** This program is distributed in the hope that it will be     **
** useful, but WITHOUT ANY WARRANTY; without even the implied  **
** warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR     **
** PURPOSE. See the GNU General Public License for more        **
** details.                                                    **
**                                                             **
** You should have received a copy of the GNU General Public   **
** License along with this program; if not, write to the Free  **
** Software Foundation, Inc., 59 Temple Place, Suite 330,      **
** Boston, MA  02111-1307  USA                                 **
**                                                             **
****************************************************************/

/* #define COUNT */
#include <stdio.h>			/* enable sprintf(), etc. */
#include <stdlib.h>			/* for wait(), etc. */
#include <unistd.h>			/* enable close(), pause(), etc. */
#include <sys/types.h>			/* types */
#include <sys/wait.h>			/* wait */
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>			/* for use in link_test */
#include <signal.h>			/* for signal test */
#include <setjmp.h>			/* for setjump() and longjmp() */

#include <stdint.h>         /** for uintptr_t   **/
#include "aim7.h"

#define CREAT_MODE (S_IRWXU | S_IRWXG | S_IRWXO)	/* 0777 permissions */
#define THE_LINK_MAX 8

/*
 * Signal Test
 *
 * This test repeatedly sends itself a SIGUSR2 and catches it.
 * The signal hander simply increments 'sigcount' after making sure
 * that the signal it received is SIGUSR2. (If the signal isn't
 * SIGUSR2, a message is printed and 'error' is set to 1 which
 * will terminate the test.
 */
static int sigcount;			/* count of signals */
static int error;			/* no errors now */
static void sighandler(int sig) {					/* trap handler */
	signal(SIGUSR2, sighandler);	/* install the signal hander */
	if (sig != SIGUSR2) {		/* if not our signal */
		fprintf(stderr, "sighandler(): received signal %d not SIGUSR2 (%d)\n",	/* error here */
			sig, SIGUSR2);
		error = 1;		/* tell caller to stop */
	}
	sigcount++;			/* bump the count and return */
}

int signal_test() {

    int status;			/* result of kill() */
	pid_t mypid;			/* our PID */
	error =	0;			/* clear the error flag */
	sigcount = 0;		/* clear the count */
	mypid = getpid();		/* get our pid */
	signal(SIGUSR2, sighandler);	/* install the signal hander */
	
    while (sigcount < SIGNAL_TEST_REP) {	/* do the loop */
		status = kill(mypid, SIGUSR2);	/* send the signal */
		if (status == -1) {	/* error? */
			perror("\nkill(signal_test)");	/* tell more info */
			fprintf(stderr, "signal_test(): unable to send kill(%d, SIGUSR2).\n", mypid);	/* if so talk to human */
			return -1;	/* die */
		}
		if (error == 1) {	/* handle sig hande error */
			fprintf(stderr, "signal_test(): signal handler discovered an error.\n");	/* talk to human (again) */
			return -1;	/* die */
		}
	}				/* loop */
	return 0;			/* return success */
}

/*
 * Jump Test:
 * 
 * This test exercises the setjmp() and longjmp() functions in the standard
 * library. Since these functions are used extensively in some programs (including
 * the most popular portable threads implementations), it is reasonable to talk about
 * their timings.
 *
 * This test repeatedly performs a setjmp() followed by a longjmp().
 */
static void
dummy_function(jmp_buf buf,
	       int count)
{
	if (count == 0)
		longjmp(buf, 1);
	dummy_function(buf, --count);	/* go for kernel trap, max out register windows */
}

int jmp_test() {
	static int			/* static so they'll survive */
	  result,			/* result of setjmp */
	  i;				/* loop count */

	jmp_buf buf;			/* the context */
	for (i = 0; i < JMP_TEST_REP; i++) {	/* loop a bunch of times */
		result = setjmp(buf);	/* save the context */
		switch (result) {	/* look at the result */
		case 0:
			dummy_function(buf, 10);	/* different stack frame */
		case 1:
			break;		/* we must have just longjmp()ed so loop */
		default:
			return -1;	/* something must have happened so error */
		}			/* end of switch */
	}				/* end of loop */
	return 0;			/* return success */
}

int link_test() {
     /*
      * This test creates a file in the current directory and then 
      * adds 7 additional links to it. (POSIX spec says that LINK_MAX's 
      * smallest legal value is 8 so 1 + 7 == 8.) The links are then
      * removed and then reattached in a round-robin fashion. For some
      * vendors, this involves sync directory updates, others it doesn't.
      * Anyway, we've seen some POSIX wannabes claim to be POSIX compliant
      * with values of less than 8 for LINK_MAX so we just use 8 anyway.
      * If they aren't compliant, then they can't run this test anyway.
      * And they shouldn't be claiming POSIX compliance since it'll break
      * lots of applications.
      */

	int
	  i,				/* misc loop variable */
	  status,			/* OS function status return */
	  fd,				/* file discriptor */
	  n;				/* loop variable */

	static char
	  buffer0[1024],		/* filename buffers */
	 
		buffer1[1024],
		buffer2[1024],
		buffer3[1024],
		buffer4[1024],
		buffer5[1024],
		buffer6[1024],
		buffer7[1024],
		*fns[THE_LINK_MAX] =
		{ buffer0, buffer1, buffer2, buffer3, buffer4, buffer5,
	       buffer6, buffer7 };
	/*
	 * Step 1: create unique filenames
	 */
	for (i = 0; i < THE_LINK_MAX; i++) {	/* for filenames 0..7 */
		
        sprintf(fns[i], "DISKS/linkXXXXXXXXXX");	/* put value into string */
		aim_mktemp(fns[i]);	/* force it to be unique (use our function) */
	}
	/*
	 * Step 2: create the first file
	 */
	fd = creat(fns[0], CREAT_MODE);	/* create the file */
	if (fd < 0) {			/* check for errors */
		fprintf(stderr, "link_test(): unable to create file %s\n",
			fns[0]);
		perror("link_test(): ");
		return (-1);
	}
	/*
	 * Step 3: Create the links
	 */
	for (i = 1; i < THE_LINK_MAX; i++) {	/* create the links for 1..7 */
		status = link(fns[0], fns[i]);	/* link them */
		if (status != 0) {	/* error here? */
			if (errno == EMLINK)
				fprintf(stderr,
					"Link_test: POSIX Violation detected.\n");
			else
				fprintf(stderr,
					"link_test: Unable to create link to file %s\n",
					fns[i]);
			perror("link_test(): ");
			return (-1);
		}
	}
	/*
	 * Step 4: the loop
	 */
	n = LINK_TEST_REP;			/* establish loop count */
	while (n--) {			/* while looping */
		for (i = 1; i < THE_LINK_MAX; i++) {	/* try each one in turn */
			status = unlink(fns[i]);	/* unlink it */
			if (status != 0) {	/* check for errors */
				fprintf(stderr, "link_test: Unable to unlink file %s\n", fns[i]);	/* talk to human */
				perror("link_test(): ");
				return (-1);
			}
			status = link(fns[0], fns[i]);	/* link them back */
			if (status != 0) {	/* error here? */
				if (errno == EMLINK)	/* Some non-UNIX POSIX claimants aren't compliant */
					fprintf(stderr,
						"Link_test: POSIX Violation detected.\n");
				else	/* else just an error here */
					fprintf(stderr,
						"link_test: Unable to create link to file %s\n",
						fns[i]);
				perror("link_test(): ");
				return (-1);	/* die anyway */
			}		/* end of error */
		}			/* end of for */
	}				/* end of while */
	/*
	 * Step 5: clean up
	 */
	for (i = 0; i < THE_LINK_MAX; i++) {
		status = unlink(fns[i]);	/* unlink it */
		if (status != 0) {
			perror("link_test(): ");
			fprintf(stderr,
				"link_test: Unable to unlink file %s\n",
				fns[i]);
			return (-1);
		}
	}
	close(fd);			/* make file go away (its already unlinked) */
	/*
	 * Step 6: we're done
	 */
	return 0;
}

int page_test() {
	
    int i,				/* loop variable */
	  j,				/* dirty page pointer */
	  n,				/* iteration count */
	  brk();			/* system call */

	void
	 *oldbrk,			/* old top of memory */
	 *newbrk,			/* new top of memory */
	 *sbrk();			/* system call */
    
	char *cp;			/* pointer to new memory region */
	/*
	 * Step 2: Get old memory top, move top higher
	 */
	oldbrk = sbrk(0);		/* get current break value */
	newbrk = sbrk(1024 * 1024);	/* move up 1 megabyte */
	if ((int)(uintptr_t)newbrk == -1) {
		perror("\npage_test");	/* tell more info */
		fprintf(stderr, "page_test: Unable to do initial sbrk.\n");
		return (-1);
	}
	/*
	 * Step 3: The loop
	 */
	n = PAGE_TEST_REP;
	while (n--) {			/* while not done */
		newbrk = sbrk(-4096 * 16);	/* deallocate some space */
		for (i = 0; i < 16; i++) {	/* now get it back in pieces */
			newbrk = sbrk(4096);	/* Get pointer to new space */
	        if ((int)(uintptr_t)newbrk == -1) {
				perror("\npage_test");	/* tell more info */
				fprintf(stderr,
					"page_test: Unable to do sbrk.\n");
				return (-1);
			}
			cp = (char *)newbrk;	/* prepare to dirty it so pages into memory */
			for (j = 0; j < 4096; j += 128) {	/* loop through new region */
				cp[j] = ' ';	/* dirty the page */
			}		/* end for */
		}			/* end for */
	}				/* end while */
	/*
	 * Step 4: Clean up by moving break back to old value
	 */
	brk(oldbrk);
	return 0;
}

int brk_test() {
	
    int i, n, i32, brk();
	void *oldbrk, *newbrk, *sbrk();

    /*
	 * Step 2: get old memory top, move top higher
	 */
	oldbrk = sbrk(0);		/* get old break value */
	newbrk = sbrk(1024 * 1024);	/* move up 1 megabyte */
	if ((int)(uintptr_t)newbrk == -1) {
		perror("\nbrk_test");	/* tell more info */
		fprintf(stderr, "brk_test: Unable to do initial sbrk.\n");
		return (-1);
	}
	/*
	 * Step 3: The loop
	 */
	n = BRK_TEST_REP;
	while (n--) {			/* while not done */
		newbrk = sbrk(-4096 * 16);	/* deallocate some space */
		for (i = 0; i < 16; i++) {	/* allocate it back */
			newbrk = sbrk(4096);	/* 4k at a time (should be ~ 1 page) */
	        if ((int)(uintptr_t)newbrk == -1) {
				perror("\nbrk_test");	/* tell more info */
				fprintf(stderr,
					"brk_test: Unable to do sbrk.\n");
				return (-1);
			}
		}
	}
	/*
	 * Step 4: clean up
	 */
	brk(oldbrk);
	return 0;
}

int exec_test() {
	
    int fval, status, n;
	n = EXEC_TEST_REP;
	while (n--) {
		fval = fork();		/* fork the task off */
		if (fval == 0) {	/* we're the child */
			status = execl("./true", "true", NULL);
			perror("\nexec_test");	/* tell more info */
			fprintf(stderr,
				"Cannot execute `./true' (status = %d)\n",
				status);
			exit(-1);	/* quit painlessly */
		} else {
			while (1) {	/* now wait for done */
				if (wait(&status) > 0) {	/* if one has completed OK */
					if ((status & 0377) == 0177)	/* child proc stopped */
						(void)fprintf(stderr,
							      "\nChild process stopped by signal #%d\n",
							      ((status >> 8) &
							       0377));
					else if ((status & 0377) != 0) {	/* child term by sig */
						if ((status & 0377) & 0200) {
							(void)fprintf(stderr,
								      "\ncore dumped\n");
							(void)fprintf(stderr,
								      "\nChild terminated by signal #%d\n",
								      (status &
								       0177));
						}
					} else {	/* child exit()ed */
						if (((status >> 8) & 0377))	/* isolate status */
							(void)fprintf(stderr,
								      "\nChild process called exit(), status = %d\n",
								      ((status
									>> 8) &
								       0377));
					}
				} else if (errno == ECHILD)
					break;
				else if (errno == EINTR)
					continue;
			}
		}
	}
	return 0;
}

int fork_test() {
	
    int fval, status, n;
	
    n = FORK_TEST_REP;
	while (n--) {
		fval = fork();		/* fork the task off */
		if (fval == 0) {	/* we're the child */
			exit(0);	/* quit painlessly */
		} else {
			while (1) {	/* now wait for done */
				if (wait(&status) > 0) {	/* if one has completed OK */
					if ((status & 0377) == 0177)	/* child proc stopped */
						(void)fprintf(stderr,
							      "\nChild process stopped by signal #%d\n",
							      ((status >> 8) &
							       0377));
					else if ((status & 0377) != 0) {	/* child term by sig */
						if ((status & 0377) & 0200) {
							(void)fprintf(stderr,
								      "\ncore dumped\n");
							(void)fprintf(stderr,
								      "\nChild terminated by signal #%d\n",
								      (status &
								       0177));
						}
					} else {	/* child exit()ed */
						if (((status >> 8) & 0377))	/* isolate status */
							(void)fprintf(stderr,
								      "\nChild process called exit(), status = %d\n",
								      ((status
									>> 8) &
								       0377));
					}
				} else if (errno == ECHILD)
					break;
				else if (errno == EINTR)
					continue;
			}
		}
	}
	return 0;
}

int creat_clo() {
	
    int n,				/* loop counter */
	    j;				/* status value */
	char fn4[FILENAME_MAX];		/* file name buffer */

#ifdef COUNT
	int count = 0;
#endif

	n = CREAT_CLO_REP;			/* initialize loop count */
	j = 0;				/* make gcc happy */
	sprintf(fn4, "./DISKS/%s", TMPFILE2);
	aim_mktemp(fn4);		/* create unique string */
	
    while (n--) {			/* loop a set number of times */
		if ((j = creat(fn4, CREAT_MODE)) < 0) {	/* if can't creat */
			fprintf(stderr, "creat error\n");	/* error */
			perror("creat-clo(): can't creat");
			return (-1);
		} /* end of error */
		else if (close(j) < 0) {	/* if can't close */
			fprintf(stderr, "close error\n");	/* error */
			perror("creat-clo(): can't close");
			return (-1);
		}			/* end of error */
#ifdef COUNT
		count++;
#endif
	}				/* end of loop */
	unlink(fn4);			/* unlink the file */
#ifdef COUNT
	printf("creat_clo: %d\n", count);
#endif
	return (j);			/* return last file handle */
}					/* the end */
