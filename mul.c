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
#include <stdio.h>			/* allow sscanf(), fprintf(), etc. */
#include <stdlib.h>			/* allow exit(), etc. */

#include "aim7.h"

#define PI (3.14159)
#define ONE_OVER_PI (1.0/3.14159)
#define OPS_PER_LOOP 12

/*
 *      mul_double
 */
int mul_double() {
	
    int n,				/* internal loop variable */
	  loop_cnt;			/* internal loop count */

	double d1,				/* copy of arg 1 */
	  d2,				/* copy of arg 2 */
	  td1, td2,			/* temp copy of args */
	  d;				/* result goes here */

	d1 = PI;			/* use register variables */
	d2 = ONE_OVER_PI;
	loop_cnt = 1000000;

	d = 1.0;
	/*
	 * Variable Values 
	 */
	/*
	 * d    d1    d2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    1    x     1/x  - initial value */
		d *= d1;		/*    x    x     1/x */
		d1 *= d2;		/*    x    1     1/x */
		d1 *= d2;		/*    x    1/x   1/x */
		d2 *= d;		/*    x    1/x   1   */
		d2 *= d;		/*    x    1/x   x   */
		d *= d1;		/*    1    1/x   x   */
		d *= d1;		/*    1/x  1/x   x   */
		d1 *= d2;		/*    1/x  1     x   */
		d1 *= d2;		/*    1/x  x     x   */
		d2 *= d;		/*    1/x  x     1   */
		d2 *= d;		/*    1/x  x     1/x */
		d *= d1;		/*    1    x     1/x */
		/*
		 * Note that at loop end, d1 = 1/d2 
		 */
		/*
		 * which is as we started.  Thus, 
		 */
		/*
		 * the values in the loop are stable 
		 */
	}
	return (0);
}

/*
 *      mul_float
 */
int mul_float() {
	
    int n,				/* internal loop variable */
	  loop_cnt;			/* internal loop count */

	float
	  f1,				/* copy of arg 1 */
	  f2,				/* copy of arg 2 */
	  f;				/* result goes here */

	f1 = 4.0;			/* use register variables */
	f2 = 1.0/4.0;
	loop_cnt = 1000000;

	f = 1.0;
	/*
	 * Variable Values 
	 */
	/*
	 * f    f1    f2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    1    x     1/x  - initial value */
		f *= f1;		/*    x    x     1/x */
		f1 *= f2;		/*    x    1     1/x */
		f1 *= f2;		/*    x    1/x   1/x */
		f2 *= f;		/*    x    1/x   1   */
		f2 *= f;		/*    x    1/x   x   */
		f *= f1;		/*    1    1/x   x   */
		f *= f1;		/*    1/x  1/x   x   */
		f1 *= f2;		/*    1/x  1     x   */
		f1 *= f2;		/*    1/x  x     x   */
		f2 *= f;		/*    1/x  x     1   */
		f2 *= f;		/*    1/x  x     1/x */
		f *= f1;		/*    1    x     1/x */
		/*
		 * Note that at loop end, f1 = 1/f2 
		 */
		/*
		 * which is as we started.  Thus, 
		 */
		/*
		 * the values in the loop are stable 
		 */
	}
	return (0);
}

/*
 *      mul_long 
 */
int mul_long() {
	
    int	n,				/* inside loop variable */
	  loop_cnt;			/* internal loop count */

	long l1, l2,			/* working copies */
	  l;				/* result */

	l1 = 1;			/* use register variables */
	l2 = 1;
	loop_cnt = 20000;

	l = 12345678;
	/*
	 * Variable Values 
	 */
	/*
	 * l    l1    l2  
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    x    1     1   - initial value */
		l *= l1;		/*    x    1     1   */
		l1 *= l2;		/*    x    1     1   */
		l1 *= l2;		/*    x    1     1   */
		l2 *= l1;		/*    x    1     1   */
		l2 *= l1;		/*    x    1     1   */
		l *= l2;		/*    x    1     1   */
		l *= l1;		/*    x    1     1   */
		l1 *= l2;		/*    x    1     1   */
		l1 *= l2;		/*    x    1     1   */
		l2 *= l1;		/*    x    1     1   */
		l2 *= l1;		/*    x    1     1   */
		l *= l2;		/*    x    1     1   */
		/*
		 * Note that at loop end, all values 
		 */
		/*
		 * as we started.  Thus, the values 
		 */
		/*
		 * in the loop are stable 
		 */
	}
	return (0);			/* return success */
}

/*
 *      mul_int 
 */
int mul_int() {
	
    int n,				/* inside loop variable */
	  loop_cnt;			/* internal loop count */

	int i1, i2,			/* working copies */
	  i;				/* result */
	
    i1 = 1;			/* use register variables */
	i2 = 1;
	loop_cnt = 20000;

	i = 12345678;
	/*
	 * Variable Values 
	 */
	/*
	 * i    i1    i2  
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    x    1     1   - initial value */
		i *= i1;		/*    x    1     1   */
		i1 *= i2;		/*    x    1     1   */
		i1 *= i2;		/*    x    1     1   */
		i2 *= i1;		/*    x    1     1   */
		i2 *= i1;		/*    x    1     1   */
		i *= i2;		/*    x    1     1   */
		i *= i1;		/*    x    1     1   */
		i1 *= i2;		/*    x    1     1   */
		i1 *= i2;		/*    x    1     1   */
		i2 *= i1;		/*    x    1     1   */
		i2 *= i1;		/*    x    1     1   */
		i *= i2;		/*    x    1     1   */
		/*
		 * Note that at loop end, all values 
		 */
		/*
		 * as we started.  Thus, the values 
		 */
		/*
		 * in the loop are stable 
		 */
	}
	return (0);			/* return success */
}

/*
 *      mul_short 
 */
int mul_short() {
	
    int n,				/* inside loop variable */
	  loop_cnt;			/* internal loop count */

	short s1, s2,			/* working copies */
	  s;				/* result */
	
    s1 = 1;			/* use register variables */
	s2 = 1;
	loop_cnt = 25000;

	s = 1234;
	/*
	 * Variable Values 
	 */
	/*
	 * s    s1    s2  
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    x    1     1   - initial value */
		s *= s1;		/*    x    1     1   */
		s1 *= s2;		/*    x    1     1   */
		s1 *= s2;		/*    x    1     1   */
		s2 *= s1;		/*    x    1     1   */
		s2 *= s1;		/*    x    1     1   */
		s *= s2;		/*    x    1     1   */
		s *= s1;		/*    x    1     1   */
		s1 *= s2;		/*    x    1     1   */
		s1 *= s2;		/*    x    1     1   */
		s2 *= s1;		/*    x    1     1   */
		s2 *= s1;		/*    x    1     1   */
		s *= s2;		/*    x    1     1   */
		/*
		 * Note that at loop end, all values 
		 */
		/*
		 * as we started.  Thus, the values 
		 */
		/*
		 * in the loop are stable 
		 */
	}
	return (0);			/* return success */
}
