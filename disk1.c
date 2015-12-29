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
#include <stdio.h>			/* enable scanf(), etc.  */
#include <stdlib.h>			/* enable rand(), etc. */
#include <unistd.h>			/* enable write(), etc. */
#include <sys/types.h>			/* required for creat() */
#include <sys/stat.h>			/* required for creat() */
#include <fcntl.h>			/* required for creat() */
#include <string.h>			/* for strchr() */

#include "aim7.h"

static char filename1[STRLEN];
static char filename2[STRLEN];

static char nbuf[NBUFSIZE];		/* 1K blocks */

/* test file size is 2^10 */
#define SHIFT	10			/* Change with block size */

/* 
 * replaces the contents of the string pointed to by template with a unique file name.
 * The string in template should look like a file name with six trailing Xs.
 * aim_mktemp() will replace the Xs with a character string that can be used to create a
 * unique file name.
 * aim_mktemp() is a substitute for unix "mktemp()", which is not POSIX compliant.
 * tmpnam() does not allow a directory to be specified.
 * tempnam() is not POSIX compliant.
 * changed from 3 pid char to 5 pid char  10/17/95  1.1.
 */
void aim_mktemp(char *template) {
	static int counter = -1;	/* used to fill in template */
	static int pid_end;		/* holds last 5 digits of pid, constant for this process */
	char *Xs;			/* points to string of Xs in template */

	if ((template == NULL) || (*template == '\0')) {	/* make sure caller passes parameter */
		fprintf(stderr, "aim_mktemp : template parameter empty \n");
		return;
	}
	Xs = template + (strlen(template) - sizeof ("XXXXXXXXXX")) + 1;	/* find the X's */
	if (strcmp(Xs, "XXXXXXXXXX") != 0) {	/* bad parameter */
		fprintf(stderr,
			"aim_mktemp : template parameter needs 10 Xs \n");
		return;
	}
	if (counter++ == -1) {		/* initialize counter and pid */
		pid_end = getpid() % 100000;	/* use uniqueness of pid, only need 5 digits */
	} else if (counter == 100000)	/* reset, only need 5 digits */
		counter = 0;

	sprintf(Xs, "%05d%05d", pid_end, counter);	/* write over XXXXXXXXXX, zero pad counter */
}
/*
 * "Semi"-Random disk read					 
 * TVL 11/28/89
 */
int disk_rr() {
	int i, fd, n;
	long sk;

	sk = 0l;
	n = DISK_ITERATION_COUNT;	/* user specified size */
	sprintf(filename2, "DISKS/%s", TMPFILE2);
	aim_mktemp(filename2);		/* generate new file name */

	if ((fd = creat(filename2, (S_IRWXU | S_IRWXG | S_IRWXO))) < 0) {
		fprintf(stderr, "disk_rr : cannot create %s\n", filename2);
		perror(__FILE__);
		return (-1);
	}
	/*
	 * We do this to "encourage" the system to read from disk
	 * instead of the buffer cache.
	 * 12/12/89 TVL
	 */
	while (n--) {
		if (write(fd, nbuf, sizeof nbuf) != sizeof nbuf) {
			perror("disk_rr()");
			fprintf(stderr, "disk_rr : cannot write %s\n", filename2);
			close(fd);
			unlink(filename2);
			return (-1);
		}
	}
	close(fd);
	if ((fd = open(filename2, O_RDONLY)) < 0) {
		fprintf(stderr, "disk_rr : cannot open %s\n", filename2);
		perror(__FILE__);
		return (-1);
	}

	unlink(filename2);

  /********** pseudo random read *************/
	for (i = 0; i < DISK_ITERATION_COUNT; i++) {
		/*
		 * get random block to read, making sure not to read past end of file 
		 */
		sk = aim_rand() % ((DISK_ITERATION_COUNT * (long)sizeof (nbuf)) >> SHIFT);	/* rand() % (filesize/blocksize) */
		/*
		 * sk specifies a specific block, multiply by blocksize to get offset in bytes 
		 */
		sk <<= SHIFT;
		if (lseek(fd, sk, 0) == -1) {
			perror("disk_rr()");
			fprintf(stderr, "disk_rr : can't lseek %s\n", filename2);

/*      unlink(filename2);   */
			close(fd);
			return (-1);
		}
		if ((n = read(fd, nbuf, sizeof nbuf)) != sizeof nbuf) {
			perror("disk_rr()");
			fprintf(stderr, "disk_rr : can't read %s\n", filename2);

/*      unlink(filename2);   */
			close(fd);
			return (-1);
		}
	}
	/*
	 * unlink(filename2);  
	 */
	close(fd);
	return (0);
}



/*
 * "Semi"-Random disk write
 */


int disk_rw() {
	
    int i, fd, n;
	long sk;

	sk = 0l;
	n = DISK_ITERATION_COUNT;	/* user specified size */
	sprintf(filename2, "DISKS/%s", TMPFILE2);
	aim_mktemp(filename2);

	if ((fd = creat(filename2, (S_IRWXU | S_IRWXG | S_IRWXO))) < 0) {
		fprintf(stderr, "disk_rw : cannot create %s\n", filename2);
		perror(__FILE__);
		return (-1);
	}

	while (n--) {
		if (write(fd, nbuf, sizeof nbuf) != sizeof nbuf) {
			perror("disk_rw()");
			fprintf(stderr, "disk_rw : cannot write %s\n", filename2);
			close(fd);
			unlink(filename2);
			return (-1);
		}
	}
	close(fd);
	if ((fd = open(filename2, O_WRONLY)) < 0) {
		fprintf(stderr, "disk_rw : cannot open %s\n", filename2);
		perror(__FILE__);
		return (-1);
	}

	unlink(filename2);

  /********** pseudo random write *************/

	for (i = 0; i < DISK_ITERATION_COUNT; i++) {
		/*
		 * get random block to read, making sure not to read past end of file 
		 */
		sk = aim_rand() % ((DISK_ITERATION_COUNT * (long)sizeof (nbuf)) >> SHIFT);	/* rand() % (filesize/blocksize) */
		/*
		 * sk specifies a specific block, multiply by blocksize to get offset in bytes 
		 */
		sk <<= SHIFT;
		if (lseek(fd, sk, 0) == -1) {
			perror("disk_rw()");
			fprintf(stderr, "disk_rw : can't lseek %s\n", filename2);

/*      unlink(filename2);   */
			close(fd);
			return (-1);
		}
		if ((n = write(fd, nbuf, sizeof nbuf)) != sizeof nbuf) {
			perror("disk_rw()");
			fprintf(stderr, "disk_rw : can't read %s\n", filename2);

/*      unlink(filename2);   */
			close(fd);
			return (-1);
		}
	}

/*      unlink(filename2);   */
	close(fd);
	return (0);
}

int sync_disk_rw() {
	
    int i, fd, blocks, n;
	long sk;

	sk = 0l;
	n = blocks = DISK_ITERATION_COUNT / 2;	/* divide by 2 so as not to pound disk */
	sprintf(filename2, "DISKS/%s", TMPFILE2);
	aim_mktemp(filename2);

	if ((fd = open(filename2, (O_WRONLY | O_CREAT | O_TRUNC),	/* standard CREAT mode */
		       (S_IRWXU | S_IRWXG | S_IRWXO))) < 0) {	/* standard permissions */
		fprintf(stderr, "sync_disk_rw : cannot create %s\n", filename2);
		perror(__FILE__);
		return (-1);
	}

	while (n--) {
		if (write(fd, nbuf, sizeof nbuf) != sizeof nbuf) {
			perror("disk_rw()");
			fprintf(stderr, "sync_disk_rw : cannot write %s\n",
				filename2);
			close(fd);
			unlink(filename2);
			return (-1);
		}
	}
	close(fd);
	if ((fd = open(filename2, O_WRONLY | O_SYNC)) < 0) {	/* open it again synchronously */
		fprintf(stderr, "sync_disk_rw : cannot open %s\n", filename2);
		perror(__FILE__);
		return (-1);
	}

/*  unlink(filename2); *//*
 * unlink moved after write 10/17/95  
 */

  /********** pseudo random write *************/

	for (i = 0; i < blocks; i++) {	/* get random block to read, 
					 * making sure not to read past end of file */
		sk = aim_rand() % ((blocks * (long)sizeof (nbuf)) >> SHIFT);	/* rand() % (filesize/blocksize) */

		sk <<= SHIFT;		/* sk specifies a specific block, 
					 * multiply by blocksize to get offset in bytes */
		if (lseek(fd, sk, 0) == -1) {
			perror("sync_disk_rw()");
			fprintf(stderr, "sync_disk_rw : can't lseek %s\n",
				filename2);
			unlink(filename2);
			close(fd);
			return (-1);
		}
		if ((n = write(fd, nbuf, sizeof nbuf)) != sizeof nbuf) {
			perror("sync_disk_rw()");
			fprintf(stderr,
				"sync_disk_rw : can't write %lu bytes to %s\n",
				sizeof nbuf, filename2);
			unlink(filename2);
			close(fd);
			return (-1);
		}
	}
	unlink(filename2);
	close(fd);
	return (0);
}

int disk_rd() {
	
    int i, fd;

	sprintf(filename1, "DISKS/%s", TMPFILE1);
	fd = open(filename1, O_RDONLY);
	if (fd < 0) {			/*  */
		fprintf(stderr, "disk_rd : cannot open %s\n", filename1);
		perror(__FILE__);
		return (-1);
	}
	/*
	 * forward sequential read only 
	 */
	if (lseek(fd, 0L, 0) < 0) {
		fprintf(stderr, "disk_rd : can't lseek %s\n", filename1);
		perror(__FILE__);
		close(fd);
		return (-1);
	}
	for (i = 0; i < DISK_ITERATION_COUNT; i++) {
		if (read(fd, nbuf, sizeof nbuf) != sizeof nbuf) {
			fprintf(stderr, "disk_rd : can't read %s\n", filename1);
			perror(__FILE__);
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (0);
}

int disk_cp() {
	
    int status,			/* result of last system call */
	  n, fd, fd2;

	n = DISK_ITERATION_COUNT;	/* user specified size */
	sprintf(filename1, "DISKS/%s", TMPFILE1);	/* if so, build source file name */
	sprintf(filename2, "DISKS/%s", TMPFILE2);	/* and destination file name */
	aim_mktemp(filename2);		/* convert into unique temporary name */
	fd = open(filename1, O_RDONLY);	/* open the file */
	if (fd < 0) {			/* open source file */
		fprintf(stderr, "disk_cp (1): cannot open %s\n", filename1);	/* handle error */
		perror(__FILE__);	/* print error */
		return (-1);		/* return error */
	}
	fd2 = creat(filename2, (S_IRWXU | S_IRWXG | S_IRWXO));	/* create the file */
	if (fd2 < 0) {			/* create output file */
		fprintf(stderr, "disk_cp (2): cannot create %s\n", filename2);	/* talk to human on error */
		perror(__FILE__);
		close(fd);		/* close source file */
		return (-1);		/* return error */
	}
	unlink(filename2);			/* make it anonymous (and work NFS harder) */
	status = lseek(fd, 0L, SEEK_SET);	/* move pointer to offset 0 (rewind) */
	if (status < 0) {		/* handle error case */
		fprintf(stderr, "disk_cp (3): cannot lseek %s\n", filename1);	/* talk to human */
		perror(__FILE__);
		/*
		 * unlink(filename2);
 *//*
 * make it anonymous (and work NFS harder) 
 */
		close(fd);		/* close source file */
		close(fd2);		/* close this file */
		return (-1);		/* return error */
	}
	while (n--) {			/* while not done */
		status = read(fd, nbuf, sizeof nbuf);	/* do the read */
		if (status != sizeof nbuf) {	/* return the status */
			fprintf(stderr,
				"disk_cp (4): cannot read %s %d (status = %d)\n",
				filename1, fd, status);
			perror(__FILE__);
			/*
			 * unlink(filename2); 
 *//*
 * make it anonymous (and work NFS harder) 
 */
			close(fd);
			close(fd2);
			return (-1);
		}
		status = write(fd2, nbuf, sizeof nbuf);	/* do the write */
		if (status != sizeof nbuf) {	/* check for error */
			fprintf(stderr, "disk_cp (5): cannot write %s\n", filename2);
			perror(__FILE__);
			/*
			 * unlink(filename2); 
 *//*
 * make it anonymous (and work NFS harder) 
 */
			close(fd);
			close(fd2);
			return (-1);
		}
	}
	/*
	 * unlink(filename2); 
 *//*
 * make it anonymous (and work NFS harder) 
 */
	close(fd);			/* close input file */
	close(fd2);			/* close (and delete) output file */
	return (0);			/* show success */
}

int sync_disk_cp() {
	
    int status,			/* result of last system call */
	  n, blocks, fd, fd2;

	n = blocks = DISK_ITERATION_COUNT / 2;	/* divide by 2 so as not to pound disk */
	sprintf(filename1, "DISKS/%s", TMPFILE1);	/* if so, build source file name */
	sprintf(filename2, "DISKS/%s", TMPFILE2);	/* and destination file name */
	aim_mktemp(filename2);		/* convert into unique temporary name */
	fd = open(filename1, O_RDONLY);	/* open the file */
	if (fd < 0) {			/* open source file */
		fprintf(stderr, "sync_disk_cp (1): cannot open %s\n", filename1);	/* handle error */
		perror(__FILE__);	/* print error */
		return (-1);		/* return error */
	}
	fd2 = open(filename2, (O_SYNC | O_WRONLY | O_CREAT | O_TRUNC), (S_IRWXU | S_IRWXG | S_IRWXO));	/* create the file */
	if (fd2 < 0) {			/* create output file */
		fprintf(stderr, "sync_disk_cp (2): cannot create %s\n", filename2);	/* talk to human on error */
		perror(__FILE__);
		close(fd);		/* close source file */
		return (-1);		/* return error */
	}

/*  unlink(filename2);	*//*
 * make it anonymous (and work NFS harder) 
 */
	status = lseek(fd, 0L, SEEK_SET);	/* move pointer to offset 0 (rewind) */
	if (status < 0) {		/* handle error case */
		fprintf(stderr, "sync_disk_cp (3): cannot lseek %s\n", filename1);	/* talk to human */
		perror(__FILE__);
		close(fd);		/* close source file */
		close(fd2);		/* close this file */
		return (-1);		/* return error */
	}
	while (n--) {			/* while not done */
		status = read(fd, nbuf, sizeof nbuf);	/* do the read */
		if (status != sizeof nbuf) {	/* return the status */
			fprintf(stderr,
				"sync_disk_cp (4): cannot read %s %d (status = %d)\n",
				filename1, fd, status);
			perror(__FILE__);
			unlink(filename2);	/* make it anonymous (and work NFS harder) */
			close(fd);
			close(fd2);
			return (-1);
		}
		status = write(fd2, nbuf, sizeof nbuf);	/* do the write (SYNC) */
		if (status != sizeof nbuf) {	/* check for error */
			fprintf(stderr, "sync_disk_cp (5): cannot write %s\n",
				filename2);
			perror(__FILE__);
			unlink(filename2);	/* make it anonymous (and work NFS harder) */
			close(fd);
			close(fd2);
			return (-1);
		}
	}
	unlink(filename2);			/* make it anonymous (and work NFS harder) */
	close(fd);			/* close input file */
	close(fd2);			/* close (and delete) output file */
	return (0);			/* show success */
}

int disk_wrt() {

    int n, fd, i;

	n = DISK_ITERATION_COUNT;	/* user specified size */
	i = 0;
	sprintf(filename2, "DISKS/%s", TMPFILE2);
	aim_mktemp(filename2);
	fd = creat(filename2, (S_IRWXU | S_IRWXG | S_IRWXO));
	if (fd < 0) {
		fprintf(stderr, "disk_wrt : cannot create %s\n", filename2);
		perror(__FILE__);
		return (-1);
	}

	unlink(filename2);

	while (n--) {
		if ((i = write(fd, nbuf, sizeof nbuf)) != sizeof nbuf) {
			fprintf(stderr, "disk_wrt : cannot write %s\n", filename2);
			perror(__FILE__);

/*  unlink(filename2); *//*
 * unlink moved after write 10/17/95  
 */
			unlink(filename2);
			close(fd);
			return (-1);
		}
	}

/*  unlink(filename2); *//*
 * unlink moved after write 10/17/95  
 */
	close(fd);
	return (0);
}

int sync_disk_wrt() {
	
    int n, blocks, fd, i;

	n = blocks = DISK_ITERATION_COUNT / 2;	/* divide by 2 so as not to pound disk */
	i = 0;
	sprintf(filename2, "DISKS/%s", TMPFILE2);
	aim_mktemp(filename2);
	fd = open(filename2, (O_SYNC | O_WRONLY | O_CREAT | O_TRUNC), (S_IRWXU | S_IRWXG | S_IRWXO));	/* sync creat */
	if (fd < 0) {
		fprintf(stderr, "sync_disk_wrt : cannot create %s\n", filename2);
		perror(__FILE__);
		return (-1);
	}

/*  unlink(filename2); *//*
 * unlink moved after write 10/17/95  
 */

	while (n--) {
		if ((i = write(fd, nbuf, sizeof nbuf)) != sizeof nbuf) {
			fprintf(stderr, "sync_disk_wrt : cannot write %s\n",
				filename2);
			perror(__FILE__);
			unlink(filename2);
			close(fd);
			return (-1);
		}
	}
	unlink(filename2);
	close(fd);
	return (0);
}

int sync_disk_update() {
	
    int i, fd, blocks, loop, n;

	long sk;

	sk = 0l;
	n = blocks = DISK_ITERATION_COUNT;
	sprintf(filename2, "DISKS/%s", TMPFILE2);
	aim_mktemp(filename2);

	/*
	 * create a "database" file 
	 */
	if ((fd = open(filename2, (O_WRONLY | O_CREAT | O_TRUNC),	/* standard CREAT mode */
		       (S_IRWXU | S_IRWXG | S_IRWXO))) < 0) {	/* standard permissions */
		fprintf(stderr, "sync_disk_update : cannot create %s\n", filename2);
		perror(__FILE__);
		return (-1);
	}

	while (n--) {
		if (write(fd, nbuf, sizeof nbuf) != sizeof nbuf) {
			perror("disk_rw()");
			fprintf(stderr, "sync_disk_update : cannot write %s\n",
				filename2);
			close(fd);
			unlink(filename2);
			return (-1);
		}
	}
	close(fd);
	if ((fd = open(filename2, O_RDWR | O_SYNC)) < 0) {	/* open it again synchronously */
		fprintf(stderr, "sync_disk_update : cannot open %s\n", filename2);
		perror(__FILE__);
		return (-1);
	}

/*  unlink(filename2); *//*
 * unlink moved after update 10/17/95  
 */

	/*
	 * pseudo random read then update 
	 */
	loop = blocks / 2;		/* only touch 1/2 the blocks */
	for (i = 0; i < loop; i++) {	/* get random block to read, 
					 * making sure not to read past end of file */
		sk = aim_rand() % ((blocks * (long)sizeof (nbuf)) >> SHIFT);	/* rand() % (filesize/blocksize) */

		sk <<= SHIFT;		/* sk specifies a specific block, 
					 * multiply by blocksize to get offset in bytes */
		if (lseek(fd, sk, 0) == -1) {	/* look something up */
			perror("sync_disk_update()");
			fprintf(stderr, "sync_disk_update : can't lseek %s\n",
				filename2);
			unlink(filename2);
			close(fd);
			return (-1);
		}
		if ((n = read(fd, nbuf, sizeof nbuf)) != sizeof nbuf) {	/* read it in */
			perror("sync_disk_update()");
			fprintf(stderr,
				"sync_disk_update : can't read %lu bytes to %s\n",
				sizeof nbuf, filename2);
			unlink(filename2);
			close(fd);
			return (-1);
		}
		if ((n = write(fd, nbuf, sizeof nbuf)) != sizeof nbuf) {	/* update it */
			perror("sync_disk_update()");
			fprintf(stderr,
				"sync_disk_update : can't write %lu bytes to %s\n",
				sizeof nbuf, filename2);
			unlink(filename2);
			close(fd);
			return (-1);
		}
	}
	unlink(filename2);
	close(fd);
	return (0);
}

