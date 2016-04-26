AIM7 Modified
=================================
Modified for manycore OS simulations.

See [this](http://manycoreos.synology.me/MediaWiki/index.php?title=%EB%B6%84%ED%95%A0%ED%98%95_%EA%B5%AC%EC%A1%B0_%EC%8B%9C%EB%AE%AC%EB%A0%88%EC%9D%B4%EC%85%98)


##How Original AIM7 Works
Every .c file has a function whose name is same with the file name. <br />
(ex) *add.c* has a function '*add\_c*()'

We will call the function '_register function_', because the functions register all function in the file. <br />
(ex) *add\_c*() will register all functions in *add.c*: *add\_double*(), *add\_float*(), *add\_long*(), *add\_short*(), *add\_int*().

Every _register function_ will return (_source_*\_file *\*) result.

In _suite.h_, data type *source\_file* is defined.
```c
typedef struct {

    char *sccs;
    char *filename;
    char *date;
    char *time;
} source_file;
```
