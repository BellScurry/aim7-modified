
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

#define FORK_TEST_REPEAT 10000

int fork_test() {
	
    int fval, status, n;

	n = FORK_TEST_REPEAT;
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
