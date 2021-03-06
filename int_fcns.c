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

#include <stdio.h>			/* declare sscanf(), etc. */
#include <stdlib.h>			/* for malloc(), etc. */
#include <string.h>			/* for memset(), etc. */

#include "aim7.h"

#define PRIME (1)
#define NONPRIME (0)
#define MAX (1000000)               /*  10^6    */
#define TOTAL_PRIMES (78500)		/* total # primes from 0 to 1000000 */

int sieve() {
	
    int iter,				/* number of times to repeat the test */
	  n,				/* outside loop count */
	  i,				/* internal loop variable */
	  prime_count;			/* count primes when done */

	char *left,				/* points to next factor */
	 *right,			/* points to next non-prime */
	 *table;			/* holds data to be manipulated */

	COUNT_START;

	/*
	 * Step 2: Allocate space
	 */
	table = (char *)malloc(MAX);	/* allocate lots of space */
	if (table == NULL) {
		fprintf(stderr,
			"sieve(): Unable to allocate %d bytes of memory.\n",
			MAX);
		return (-1);
	}
	/*
	 * Step 3: Initialize and run sieve in loop.
	 */
	for (iter = 0; iter < SIEVE_REP; iter++) {
		memset((void *)table, PRIME, (size_t) MAX);	/* init all to PRIME */
		for (n = 2; n < MAX; n++) {	/* ignore 0 & 1, known */
			left = &table[n];	/* point to next factor */
			if (*left != PRIME)
				continue;	/* if it isn't prime, skip it */
			right = left + n;	/* point to the table */
			for (i = n + n; i < MAX; i += n) {	/* look for all multiples of *left */
				*right = NONPRIME;	/* mark this one as not prime */
				right += n;	/* move to next pointer */
			}		/* and loop */
		}			/* next time through */
	}				/* end of test */
	prime_count = 0;
	for (n = 0; n < MAX; n++)	/* check answer */
		if (table[n] == PRIME)
			prime_count++;
	if (prime_count != TOTAL_PRIMES) {
		fprintf(stderr, "sieve(): Problem calculating primes.\n");
		return (-1);
	}
	free(table);			/* return the memory */
	return 0;
}
