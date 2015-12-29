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
#include <stdio.h>			/* enable scanf(), etc. */
#include <stdlib.h>			/* enable exit(), etc. */
#include <string.h>

#include "aim7.h"


static int
  sizes[] = {				/* determines how much to copy */
	1, 2, 3, 4, 5, 6,
	7, 7, 7, 7, 7, 7,
	8, 9, 11, 17, 33, 63,
	7, 7, 7, 7, 7, 7,
	1, 2, 3, 4, 5, 6,
	7, 7, 7, 7, 7, 7,
	127, 256, 1001, 1200, 1492, 1500,
	1024, 2048, 3172, 4096, 8192, 512,
	7, 7, 7, 7, 7, 7,
	1, 2, 3, 4, 5, 6,
	7, 7, 7, 7, 7, 7,
	8, 9, 11, 17, 33, 63,
	7, 7, 7, 7, 7, 7,
	1, 2, 3, 4, 5, 6,
	7, 7, 7, 7, 7, 7,
};

static char
  a[8192 + sizeof (double)],		/* source */
  b[8192 + sizeof (double)];		/* destination */

    /*
     * +sizeof(double) because we will be writing 8192 bytes to offset sizeof(double) at some time 
     */

/* Copy data to and from ram at different offsets.  Assume memory alignments between 0 and sizeof(double) */
int ram_copy() {
	
    int n;

	for (n = 0; n < RAM_COPY_REP; n++) {
		void			/* vary offsets with each call */
		 *src = (void *)&b[n % sizeof (double)],	/* try all src & dest double word offsets */

		 *dst = (void *)&a[(n / sizeof (double)) % sizeof (double)];	/* insure offset always from 0 to sizeof(double) */
		int
		  count = sizes[n % Members(sizes)];	/* vary copy sizes by table above */

		memcpy(src, dst, count);	/* memcpy() can never fail */
	}
	return (0);
}
