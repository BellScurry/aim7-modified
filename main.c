#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>           /*  clock_t, clock()    */
#include <sys/syscall.h>    /*  syscall()           */
#include "aim7.h"

#define GET_TICK(target_function) start=clock(); target_function(); end=clock();

int main (int agrc, char *argv[]) {

    clock_t start, end;    /*  unsigned long    */
    unsigned long sum;
    double avg;
    int i;
    pid_t parent_tid, tid;

    sum = 0;
    init_num_fcns_c();
    init_pipe_test_c();

    parent_tid = syscall(SYS_gettid);

/*****************************************************************************/

    
    
    
    
    
    
    
/*****************************************************************************/
    

    sum = 0;

    for (i = 0; i < 100 ; i ++) {
    
        start = clock();
        syscall(SYS_clone);
        end = clock();

        tid = syscall(SYS_gettid);   
        if (tid != parent_tid || tid == -1)
            exit(1);
        sum += (end-start);
    }

    avg = sum/100;
    printf("Average Ticks: %.2lf ticks\n", avg);

    syscall(SYS_fork);

/*****************************************************************************/

    /*

    sum = 0;

    for (i = 0 ; i < 100 ; i ++) {
        
        GET_TICK(disk_src);
        sum += (end-start);
    }

    avg = sum/100;
    printf("Average Ticks: %.2lf ticks\n", avg);
    */

/*****************************************************************************/
/*
    char dummy[1000];
    sprintf(dummy, "AIM_MKTEMP_TESTXXXXXXXXXX");
    aim_mktemp(dummy);
    creat_clo();
*/
    return 0;
}
