/*----------------------------------------------------------------------------
                            //FILE INFO//
    //STORE.C//
    responsible for storing the information of the all files found in the
    temporary directories.

    It is broken into two pieces:
    readDirectory - Does the actual reading and storing.
    Store - Passes inital information to read directories.

    Why?
    The seperate readDirectories function allows us to pass the information
    of any subdirectories found back through readDirectories. Creating a 
    simple method of recursive directory reading

    Authour: Joshua Rachpaul
-----------------------------------------------------------------------------*/

#define _POSIX_C_SOURCE 200809L //needed for strdup

#include "mergetars.h"

    /*readDirectory//
    When given a directory it reads its contents and the contents of its 
    sub directories

    Notes:
    - Path is the directory we are reading e.g. /tmp/tepfile
    - subpath is the paths INSIDE the tmp directory e.g. /tmp/tempfile/file1, 
      the sub path is /file1
    - this is done to simplfiy the process of remembering the directory 
      structure of the file (no complex string deconstruction).
    - fpp is a pointer to an array of files structure
    - Arg the commandline index of where the tar file is found
    - Size is a pointer to an int declared in mergetars.c, it contains the
      size of the files array.*/

void readDirectory(char *Path, char *SubPath, FILES **fpp, int Arg, int *size)
{
    char NewPath[MAXPATHLEN];
    char NewSubPath[MAXPATHLEN];
    char FullPath[MAXPATHLEN];
    DIR *dirp;
    struct dirent *dp;
    
    dirp = opendir(Path);

    if(dirp == NULL) {
        perror("readDirectory");
        exit(EXIT_FAILURE);
    }

    while((dp = readdir(dirp)) != NULL)
    {
        struct stat stat_buffer;  

        if(strcmp(dp->d_name,".")!=0 && strcmp(dp->d_name,"..")!=0)
        {
            sprintf(FullPath, "%s/%s", Path, dp->d_name);

            if(stat(FullPath, &stat_buffer) != 0)
            {
                perror("readDirectory");
            } else if(S_ISDIR(stat_buffer.st_mode)) {

                //create new path to include subdirectory//
                strcpy(NewPath, Path);
                strcat(NewPath, "/");
                strcat(NewPath, dp->d_name);

                //remember the subdirectory structure//
                strcpy(NewSubPath, SubPath);
                strcat(NewSubPath, "/");
                strcat(NewSubPath, dp->d_name);

                //read contents of subdirectory//
                printf("Entering %s\n",NewPath);
                readDirectory(NewPath,NewSubPath, fpp, Arg, size);

            } else if(S_ISREG(stat_buffer.st_mode)){
                
                *size +=1;
                *fpp = realloc(*fpp,(*size)*sizeof(**fpp));
                int Index = (*size)-1;
                FILES *Files = *fpp;

                //store file data//
                Files[Index].name=strdup(dp->d_name);                    
                Files[Index].path=strdup(Path);   
                Files[Index].subPath=strdup(SubPath);                 
                Files[Index].modTime = (int)stat_buffer.st_mtime;
                Files[Index].size = (int)stat_buffer.st_size;
                Files[Index].Arg = Arg;

            } else{
                fprintf(stderr,"%s is unknown filetype!\n", FullPath);
                exit(EXIT_FAILURE);
            }
            
        }
    }
    closedir(dirp);
}

    /*store//
    Passes initial information to readDirectory. Makes sure all temporary files
    are read.

    Notes:
    - n is the number of directories
    - Size is a pointer to int that stores the size of the files array
    - Tempdirectories is a pointer to an array of temporary directories
    - fp is a pointer to an array of files */

void store(int n, int *size, char **TempDirectories, FILES **fp)
{
    *size = 0;
    n-=1; //dont look through last directory//

    //read each temporary directory//
    for(int i=0; i<n; i++)
    {
        printf("directory reading: %s\n", TempDirectories[i]);
        readDirectory(TempDirectories[i],"", fp, i+1, size);
    }

}

