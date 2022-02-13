/**/















#include "mergetars.h"

#define Suffix1 ".tar.gz"
#define Suffix2 ".tgz"

bool SameChar(char *OutputDestination, int index, int i ,int Remaining)
{
            //check if chars are the same AND if we have enough space 
            //remaining for it to be a suffix//
    return (OutputDestination[index]==Suffix1[index-i] && Remaining>=7) ||
            (OutputDestination[index]==Suffix2[index-i] && Remaining>=4);
}

bool HasSuffix(char *OutputDestination)
{
    int size;
    int index;
    int CharRemaining;
    size = strlen(OutputDestination);

    for(int i=0; i<size;i++)
    {
        if(OutputDestination[i] == '.')
        {
            
            index = i;
            CharRemaining = size-index;
            while(SameChar(OutputDestination, index, i, CharRemaining) && index<size)
            {
                index++;
            }

            if(SameChar(OutputDestination, index, i, CharRemaining))
            {
                printf("Match\n");
                return true;
            }
        }

    }
    printf("No Match\n");
    return false;
}

//creates a tar file containing the best duplicates//
void createTar(char* TempDir, char* OutputDestination)
{
    int pid;
    pid = fork();

    switch(pid)
    {
        case -1:
            perror("createTar");
            exit(EXIT_FAILURE);
            break;

        case 0:
            if(HasSuffix(OutputDestination))
            {
                printf("Compressing\n");
                execl("/bin/tar", "tar", "cvpzf", OutputDestination,"-C" , TempDir,".", NULL);
            } else {
                execl("/bin/tar", "tar", "cvpf", OutputDestination,"-C" , TempDir,".", NULL);
            }
            break;

        default:
        {
            int child;
            int status;
            child = wait(&status);

            printf("createTar: Process %i terminated with status %i\n", 
                        child,WEXITSTATUS(status));

            if(WEXITSTATUS(status)>0)
            {
                exit(EXIT_FAILURE);
            }
        }
    }
}

