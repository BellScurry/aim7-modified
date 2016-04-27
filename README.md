AIM7 Modified
=================================
This is benchmark for manycore OS simulations. <br />

This benchmark is made by modifying AIM7 benchmark. <br />

If you want to see original AIM7 benchmark, see [AIM7 mirror](https://github.com/BellScurry/aim7-mirror) or [https://sourceforge.net/projects/aimbench/](https://sourceforge.net/projects/aimbench/). <br />

If you want to know about 'Manycore OS Project with ETRI', see [this](http://manycoreos.synology.me/MediaWiki/index.php?title=%EB%B6%84%ED%95%A0%ED%98%95_%EA%B5%AC%EC%A1%B0_%EC%8B%9C%EB%AE%AC%EB%A0%88%EC%9D%B4%EC%85%98)

##How Original AIM7 Works
####AIM7 File List
- Headers
  - files.h
  - funcal.h
  - suite.h
  - testerr.h
- Source Codes
  - multitask.c
  - funcal.c
  - add.c
  - mul.c
  - div.c
  - num\_fcns.c
  - int\_fncs.c
  - rand.c
  - ram.c
  - disk1.c
  - disk\_src.c
  - creat-clo.c
  - pipe-test.c
  - rpt.c
  - rtmsec.c
  - fillin.c
- Workload
  - workload.compute
  - workload.dbase
  - workload.fserver
  - workload.shared
  - aim\_1.sh
  - aim\_2.sh
  - aim\_3.sh
- _etc_.

Every .c file has only one non-static function, whose name is same with the file name. <br />
(ex) *add.c* has a function '*add\_c*()'

We will call the the non-static functions in .c files '_register function_', because the functions register all function in the file. <br />
(ex) *add\_c*() will register all functions in *add.c*: *add\_double*(), *add\_float*(), *add\_long*(), *add\_short*(), *add\_int*().

Every _register function_ will return (source\_file \*) result.

In _suite.h_, data type *source\_file* is defined.
```c
typedef struct {

    char *sccs;
    char *filename;
    char *date;
    char *time;
} source_file;
```

For example, in _add.c_, _register function_ looks like:
```c
#define PI (3.14159)
#define OPS_PER_LOOP 12

source_file *add_c() {

	static char args_double[256];
	static char args_float[256];
	static source_file s = { " @(#) add.c:1.9 3/4/94 17:16:58",	/* SCCS info */
		__FILE__, __DATE__, __TIME__
	};

	sprintf(args_double, "%g %g 1500000", PI, -PI);	/* arbitrary use of pi */
	register_test("add_double", args_double, add_double,
		      1500 * OPS_PER_LOOP,
		      "Thousand Double Precision Additions");

	sprintf(args_float, "%g %g 1000000", 3.5, -3.5);	/* 3.5 to minimize round-off error */
	register_test("add_float", args_float, add_float, 1000 * OPS_PER_LOOP,
		      "Thousand Single Precision Additions");

	register_test("add_long", "3 -3 5000000", add_long,
		      5000 * OPS_PER_LOOP, "Thousand Long Integer Additions");
	register_test("add_int", "3 -3 5000000", add_int, 5000 * OPS_PER_LOOP,
		      "Thousand Integer Additions");
	register_test("add_short", "3 -3 2000000", add_short,
		      2000 * OPS_PER_LOOP, "Thousand Short Integer Additions");
	return &s;
}
```

In _multitask.c_, function *register\_test*() is defined.
```c
void register_test(char *name, char *args, int (*f)(), int factor, char *units) {

    if (num_cmdargs >= MAXCMDARGS) {
	
        fprintf(stderr, "\nInternal Error: Attempted to register too many tests.\n");
		exit(1);
	}

	cmdargs[num_cmdargs].name = name;
	cmdargs[num_cmdargs].args = args;
	cmdargs[num_cmdargs].f = f;
	cmdargs[num_cmdargs].factor = -1;	    /* unused by multitask */
	cmdargs[num_cmdargs].units = units;
	num_cmdargs++;
}
```

##How Modified AIM7 Works
####AIM7-Modified File List
- Added or Modified to AIM7
  - aim7.h
  <br />: Combine all macro and declarations in headers and source codes & Add custom repetition count macro. 
  - fork\_test.c
  <br />: Split *fork\_test*() from _creat-clo.c_
  - main.c
  <br />: Split main() function from _multitask.c_
- Removed from AIM7
  - suite.h
  <br />: All contents in _aim7.h_
  - funcal.h
  - testerr.h
  - files.h
  - rtmsec.c
  - fillin.c
  - funcal.c
  - rpt.c
