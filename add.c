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

#include <stdio.h>			/* enable printf(), etc. */
#define PI (3.14159)

int add_double() {
	
    int n,				/* internal loop variable */
	  loop_cnt;			/* internal loop count */

	double
	  d1,				/* copy of arg 1 */
	  d2,				/* copy of arg 2 */
	  d;				/* result goes here */

	d1 = PI;			/* use register variables */
	d2 = -PI;
	loop_cnt = 1500000;

	d = 0.0;
	/*
	 * Variable Values 
	 */
	/*
	 * d    d1    d2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    0    x     -x  - initial value */
		d += d1;		/*    x    x     -x   */
		d1 += d2;		/*    x    0     -x   */
		d1 += d2;		/*    x    -x    -x   */
		d2 += d;		/*    x    -x    0    */
		d2 += d;		/*    x    -x    x    */
		d += d1;		/*    0    -x    x    */
		d += d1;		/*    -x   -x    x    */
		d1 += d2;		/*    -x   0     x    */
		d1 += d2;		/*    -x   x     x    */
		d2 += d;		/*    -x   x     0    */
		d2 += d;		/*    -x   x     -x   */
		d += d1;		/*    0    x     -x   */
		/*
		 * Note that at loop end, d1 = -d2 
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
 *      add_float
 */
int add_float()
{
	int
	  n,				/* internal loop variable */
	  loop_cnt;			/* internal loop count */

	float
	  f1,				/* copy of arg 1 */
	  f2,				/* copy of arg 2 */
	  f;				/* result goes here */

	f1 = 3.5f;			/* use register variables */
	f2 = -3.5f;
	loop_cnt = 1000000;

	f = 0.0;
	/*
	 * Variable Values 
	 */
	/*
	 * f    f1    f2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    0    x     -x  - initial value */
		f += f1;		/*    x    x     -x   */
		f1 += f2;		/*    x    0     -x   */
		f1 += f2;		/*    x    -x    -x   */
		f2 += f;		/*    x    -x    0    */
		f2 += f;		/*    x    -x    x    */
		f += f1;		/*    0    -x    x    */
		f += f1;		/*    -x   -x    x    */
		f1 += f2;		/*    -x   0     x    */
		f1 += f2;		/*    -x   x     x    */
		f2 += f;		/*    -x   x     0    */
		f2 += f;		/*    -x   x     -x   */
		f += f1;		/*    0    x     -x   */
		/*
		 * Note that at loop end, f1 = -f2 
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
 *      add_long
 */
int add_long() {
	int
	  n,				/* internal loop variable */
	  loop_cnt;			/* internal loop count */

	long
	  l1,				/* copy of arg 1 */
	  l2,				/* copy of arg 2 */
	  l;				/* result goes here */

    l1 = 3l;			/* use register variables */
	l2 = -3l;
	loop_cnt = 5000000;

	l = 0;
	/*
	 * Variable Values 
	 */
	/*
	 * l    l1    l2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    0    x     -x  - initial value */
		l += l1;		/*    x    x     -x   */
		l1 += l2;		/*    x    0     -x   */
		l1 += l2;		/*    x    -x    -x   */
		l2 += l;		/*    x    -x    0    */
		l2 += l;		/*    x    -x    x    */
		l += l1;		/*    0    -x    x    */
		l += l1;		/*    -x   -x    x    */
		l1 += l2;		/*    -x   0     x    */
		l1 += l2;		/*    -x   x     x    */
		l2 += l;		/*    -x   x     0    */
		l2 += l;		/*    -x   x     -x   */
		l += l1;		/*    0    x     -x   */
		/*
		 * Note that at loop end, l1 = -l2 
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
 *      add_int
 */
int add_int() {
	int
	  n,				/* internal loop variable */
	  loop_cnt;		/* internal loop count */

	int
	  i1,				/* copy of arg 1 */
	  i2,				/* copy of arg 2 */
	  i;				/* result goes here */
	i1 = 3;			/* use register variables */
	i2 = -3;
	loop_cnt = 5000000;

	i = 0;
	/*
	 * Variable Values 
	 */
	/*
	 * i    i1    i2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    0    x     -x  - initial value */
		i += i1;		/*    x    x     -x   */
		i1 += i2;		/*    x    0     -x   */
		i1 += i2;		/*    x    -x    -x   */
		i2 += i;		/*    x    -x    0    */
		i2 += i;		/*    x    -x    x    */
		i += i1;		/*    0    -x    x    */
		i += i1;		/*    -x   -x    x    */
		i1 += i2;		/*    -x   0     x    */
		i1 += i2;		/*    -x   x     x    */
		i2 += i;		/*    -x   x     0    */
		i2 += i;		/*    -x   x     -x   */
		i += i1;		/*    0    x     -x   */
		/*
		 * Note that at loop end, i1 = -i2 
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
 *      add_short
 */
int add_short() {
	int
	  n,				/* internal loop variable */
	  loop_cnt;			/* internal loop count */

	short
	  s1,				/* copy of arg 1 */
	  s2,				/* copy of arg 2 */
	  s;				/* result goes here */
	s1 = 3;			/* use register variables */
	s2 = -3;
	loop_cnt = 2000000;

	s = 0;
	/*
	 * Variable Values 
	 */
	/*
	 * s    s1    s2   
	 */
	for (n = loop_cnt; n > 0; n--) {	/*    0    x     -x  - initial value */
		s += s1;		/*    x    x     -x   */
		s1 += s2;		/*    x    0     -x   */
		s1 += s2;		/*    x    -x    -x   */
		s2 += s;		/*    x    -x    0    */
		s2 += s;		/*    x    -x    x    */
		s += s1;		/*    0    -x    x    */
		s += s1;		/*    -x   -x    x    */
		s1 += s2;		/*    -x   0     x    */
		s1 += s2;		/*    -x   x     x    */
		s2 += s;		/*    -x   x     0    */
		s2 += s;		/*    -x   x     -x   */
		s += s1;		/*    0    x     -x   */
		/*
		 * Note that at loop end, s1 = -s2 
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
