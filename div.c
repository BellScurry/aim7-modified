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
#include <stdlib.h>			/* declare exit(), etc. */

#include "aim7.h"
#define OPS_PER_LOOP 12


/*
 *      div_double
 */
int div_double() {
	
    int n,				/* internal loop variable */
	  loop_cnt;			/* internal loop count */

	double d1,				/* copy of arg 1 */
	  d2,				/* copy of arg 2 */
	  d;				/* result goes here */
	
    d1 = 4.0;			/* use register variables */
	d2 = 1.0/4.0;
	loop_cnt = 250000;

	d = 1.0;
	/*
	 * Variable Values 
	 */
	/*
	 * d    d1    d2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    1    x     1/x  - initial value */
		d /= d1;		/*    1/x  x     1/x  */
		d2 /= d;		/*    1/x  x     1    */
		d1 /= d2;		/*    1/x  x     1    */
		d2 /= d1;		/*    1/x  x     1/x  */
		d /= d2;		/*    1    x     1/x  */
		d2 /= d;		/*    1    x     1/x  */
		d /= d1;		/*    1/x  x     1/x  */
		d2 /= d;		/*    1/x  x     1    */
		d1 /= d2;		/*    1/x  x     1    */
		d2 /= d1;		/*    1/x  x     1/x  */
		d /= d2;		/*    1    x     1/x  */
		d2 /= d;		/*    1    x     1/x  */
	}
	return (0);
}

/*
 *      div_float
 */
int div_float() {
	
    int n,				/* loop variable */
	  loop_cnt;			/* internal loop count */

	float f1,				/* copy of arg 1 */
	  f2,				/* copy of arg 2 */
	  f;				/* result goes here */
	
    f1 = 4.0;			/* use register variables */
	f2 = 1.0/4.0;
	loop_cnt = 250000;

	f = 1.0;
	/*
	 * Variable Values 
	 */
	/*
	 * f    f1    f2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    1    x     1/x  - initial value */
		f /= f1;		/*    1/x  x     1/x  */
		f2 /= f;		/*    1/x  x     1    */
		f1 /= f2;		/*    1/x  x     1    */
		f2 /= f1;		/*    1/x  x     1/x  */
		f /= f2;		/*    1    x     1/x  */
		f2 /= f;		/*    1    x     1/x  */
		f /= f1;		/*    1/x  x     1/x  */
		f2 /= f;		/*    1/x  x     1    */
		f1 /= f2;		/*    1/x  x     1    */
		f2 /= f1;		/*    1/x  x     1/x  */
		f /= f2;		/*    1    x     1/x  */
		f2 /= f;		/*    1    x     1/x  */
	}
	return (0);			/* return success */
}

/*
 *      div_long 
 */
int div_long() {
	
    int n,				/* inside loop variable */
	  loop_cnt;			/* internal loop count */

	long l1,				/* copy of arg 1 */
	  l2,				/* copy of arg 2 */
	  l;				/* result goes here */
	
    l1 = 1;			/* use register variables */
	l2 = 1;
	loop_cnt = 75000;

	l = 1234578;
	/*
	 * Variable Values 
	 */
	/*
	 * l    l1    l2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    x    1     1    - initial value */
		l /= l1;		/*    x    1     1    */
		l /= l2;		/*    x    1     1    */
		l1 /= l2;		/*    x    1     1    */
		l2 /= l1;		/*    x    1     1    */
		l /= l1;		/*    x    1     1    */
		l /= l2;		/*    x    1     1    */
		l1 /= l2;		/*    x    1     1    */
		l2 /= l1;		/*    x    1     1    */
		l /= l1;		/*    x    1     1    */
		l /= l2;		/*    x    1     1    */
		l1 /= l2;		/*    x    1     1    */
		l2 /= l1;		/*    x    1     1    */
	}
	return (0);			/* return success */
}

/*
 *      div_int
 */
int div_int() {
	
    int n,				/* inside loop variable */
	  loop_cnt;			/* internal loop count */

	int i1,				/* copy of arg 1 */
	  i2,				/* copy of arg 2 */
	  i;				/* result goes here */

    i1 = 1;			/* use register variables */
	i2 = 1;
	loop_cnt = 75000;

	i = 1234578;
	/*
	 * Variable Values 
	 */
	/*
	 * i    i1    i2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    x    1     1    - initial value */
		i /= i1;		/*    x    1     1    */
		i /= i2;		/*    x    1     1    */
		i1 /= i2;		/*    x    1     1    */
		i2 /= i1;		/*    x    1     1    */
		i /= i1;		/*    x    1     1    */
		i /= i2;		/*    x    1     1    */
		i1 /= i2;		/*    x    1     1    */
		i2 /= i1;		/*    x    1     1    */
		i /= i1;		/*    x    1     1    */
		i /= i2;		/*    x    1     1    */
		i1 /= i2;		/*    x    1     1    */
		i2 /= i1;		/*    x    1     1    */
	}
	return (0);			/* return success */
}

/*
 *      div_short
 */
int div_short() {
	
    int n,				/* internal loop counter */
	  loop_cnt;			/* internal loop count */

	short s1,				/* copy of arg 1 */
	  s2,				/* copy of arg 2 */
	  s;				/* result goes here */
	
    s1 = 1;			/* use register variables */
	s2 = 1;
	loop_cnt = 75000;

	s = 1234;
	/*
	 * Variable Values 
	 */
	/*
	 * s    s1    s2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    x    1     1    - initial value */
		s /= s1;		/*    x    1     1    */
		s /= s2;		/*    x    1     1    */
		s1 /= s2;		/*    x    1     1    */
		s2 /= s1;		/*    x    1     1    */
		s /= s1;		/*    x    1     1    */
		s /= s2;		/*    x    1     1    */
		s1 /= s2;		/*    x    1     1    */
		s2 /= s1;		/*    x    1     1    */
		s /= s1;		/*    x    1     1    */
		s /= s2;		/*    x    1     1    */
		s1 /= s2;		/*    x    1     1    */
		s2 /= s1;		/*    x    1     1    */
	}
	return (0);			/* return success */
}
