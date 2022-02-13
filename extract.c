#include "mergetars.h"

    /*extract//
    This function when given an array of tar files and an array of directories
    extracts all tar files into seperate directories.

    Uses program "tar" with flags "-xvpf" and option -C to extract the tars 
    into a specified directory. process is forked, the child becomes a tar 
    process and the parent waits

    Notes:
    - TempDirectories is an array of temporary directories.
    - n is the size of the array of directories.
    - argv is a pointer to the arguments passed to mergetars, it will only be 
      used pass the input tar files.*/

void extract(int n,char **TempDirectories, char **argv)
{
    int pid;
    char *Directory;
    char *InputTar;
    n-=1; //dont extract anything in the last tmp directory//

    for(int i = 0; i<n; i++)
    {
        pid = fork();
        Directory = TempDirectories[i];
        InputTar = argv[i+1];

        switch(pid)
        {
            case -1:
                fprintf(stderr, "extract: Failed to fork()");
                exit(EXIT_FAILURE);
                break;

            case 0:
                
                printf("argv: %s\n TempDir %s\n",InputTar,Directory);
                execl("/bin/tar","tar","-xvpf",InputTar,"-C",Directory, NULL);
                break;

            default:
            {
                int child;
                int status;

                child = wait(&status);
                printf("Extract: Process %i terminated with status %i\n", 
                            child,WEXITSTATUS(status));
                if(WEXITSTATUS(status)>0)
                {
                    exit(EXIT_FAILURE);
                }
                break;
            }
         }
    }
}

