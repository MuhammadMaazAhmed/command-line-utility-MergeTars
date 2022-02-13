
//welcome to the main headerfile

//include these bad boys in our files
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <dirent.h>
#include <fcntl.h>
//add any #define//


//add any global variables//
typedef struct{
	char *name;
	char *path;
	char *subPath;
	int modTime;
	int size;
	int Arg;
} FILES;

//add function declartions//
extern void createdir(int, char**);
extern void clean(int, char**);
extern void store(int, int *, char**, FILES**);
extern void extract(int, char**, char**);
extern void FindBestDup(int, int*, FILES*, int**);
extern void copy(int*, int, char*, FILES*);
extern void createTar(char*, char*);
