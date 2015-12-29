#define JMP_TEST_REP        1000            /*  AIM7 Default: 1000      */
#define SIEVE_REP           5               /*  AIM7 Default: 5         */
#define RAM_COPY_REP        64              /*  AIM7 Default: 64        */
#define MEM_RTNS_1_REP      1000000         /*  AIM7 Default: 100       */
#define SHARED_MEMORY_REP   100000000       /*  AIM7 Default: 100       */
#define SORT_RTNS_1_REP     100000          /*  AIM7 Default: 10        */

/**  custom repetition count (for I/O jobs)   **/
#define PAGE_TEST_REP       1000000         /*  AIM7 Default: 100       */
#define BRK_TEST_REP        1000000         /*  AIM7 Default: 1000      */
#define FORK_TEST_REP       1000000         /*  AIM7 Default: 100       */
#define CREAT_CLO_REP       10000000        /*  AIM7 Default: 1000      */
#define EXEC_TEST_REP       5               /*  AIM7 Default: 5         */
#define SIGNAL_TEST_REP     1000000         /*  AIM7 Default: 1000      */
#define TCP_TEST_REP        1000000         /*  AIM7 Default: 90        */
#define UDP_TEST_REP        1000000         /*  AIM7 Default: 100       */
#define PIPE_CPY_REP        1000000         /*  AIM7 Default: 100       */
#define STREAM_PIPE_REP     1000000         /*  AIM7 Default: 100       */
#define DGRAM_PIPE_REP      1000000         /*  AIM7 Default: 100       */
#define STRING_RTNS_1_REP   1000000         /*  AIM7 Default: 100       */
#define MISC_RTNS_1_REP     1000000         /*  AIM7 Default: 10        */
#define DIR_RTNS_1_REP      100000000       /*  AIM7 Default: 10000     */
#define LINK_TEST_REP       100000          /*  AIM7 Default: 9         */


//  multitask.c
#define DISK_ITERATION_COUNT 1024   /*  disk_iteration_count: Specified by workfile, test file size in KiBs. (Default file size: 1 MiB -> Default disk_iteration_count = 1024)    */
#define DEBUG 0

//  suite.h
#ifdef COUNT
    #define COUNT_START static int aim_iteration_test_count = 0, caim_iteration_test_count = 0;
    #define COUNT_ZERO aim_iteration_test_count = 0; caim_iteration_test_count = 0
    #define COUNT_BUMP  { aim_iteration_test_count++; }
    #define COUNT_END(a) if (caim_iteration_test_count++ == 0) printf("Count = %d for test %s in file %s at line %d\n", aim_iteration_test_count, a, __FILE__, __LINE__);
#else
    #define COUNT_START
    #define COUNT_ZERO
    #define COUNT_BUMP
    #define COUNT_END(a)
#endif
#define TMPFILE1 "tmpa.common"
#define TMPFILE2 "tmpb.XXXXXXXXXX"
#define NBUFSIZE    1024		/* size of disk read/write buffer: 1KiB */
#define STRLEN		80
#define Members(x)	(sizeof(x)/sizeof(x[0]))	/* number items in array */
unsigned int aim_rand(), aim_rand2();
void aim_srand(), aim_srand2();

//  add.c
int add_double(), add_float(), add_long(), add_int(), add_short();

//  mul.c
int mul_double(), mul_float(), mul_long(), mul_short(), mul_int();

//  div.c
int div_double(), div_float(), div_long(), div_short(), div_int();

//  num_fcns.c
void init_num_fcns_c();
int num_rtns_1();	/* numeric routines (log, exp, etc.) */
int series_1();		/* series expansion () */
int newton_raphson();	/* newton/raphson equation solver */
int trig_rtns();		/* trig routines (sin, cos, etc.) */
int matrix_rtns();	/* rendering test (1x4) * (4x4) = (4x1) */
int array_rtns();	/* linear solutions using gausian elimination */
int string_rtns_1();	/* string operations (str{cat, cpy, str,...} etc.) */
int mem_rtns_1();	/* *alloc tests */
int mem_rtns_2();	/* mem{set, cpy, move}, etc. */
int sort_rtns_1();	/* qsort, bsearch, etc. */
int misc_rtns_1();	/* miscellaneous routines getpid, etc. */
int dir_rtns_1();	/* dir routines read/rewind dir, etc. */

//  ram.c
int ram_copy();

//  int_fcns.c
int sieve();

//  creat-clo.c
int	creat_clo(), brk_test(), fork_test(), exec_test(), jmp_test(), signal_test(), link_test(), page_test();

//  disk1.c
void aim_mktemp(char *template);
int sync_disk_rw(), sync_disk_wrt(), sync_disk_cp(), sync_disk_update(), disk_rr(), disk_rw(), disk_rd(), disk_wrt(), disk_cp();

//  disk_src.c
int disk_src();

//  pipe_test.c
void init_pipe_test_c();
int shared_memory(), tcp_test(), udp_test(), stream_pipe(), dgram_pipe(), pipe_cpy();
