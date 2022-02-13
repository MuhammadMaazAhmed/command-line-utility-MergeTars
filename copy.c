#include "mergetars.h"

//pipe size is the size of data transfer//
#define PIPESIZE 10000

//copies best duplicates to the output tar file//

//destination is the /tmp/ file where outputs will be copied into//

void CreateSub(int *OutputIndex, int SizeO, char* Destination, FILES *Files)
{
    int pid;
    int index;
    char* SubPath;
    char Path[MAXPATHLEN];                                                                            
    for(int i=0; i<SizeO; i++)
    {
        //ease of reading
        index = OutputIndex[i];
        SubPath = Files[index].subPath;
        sprintf(Path,"%s%s", Destination, SubPath);
        printf("%s\n", Path);
        pid = fork();
                                                                                
        switch(pid){
            case -1:
                printf("fork failed\n");
                exit(EXIT_FAILURE);
                break;
                                                                                
            case 0:
                execl("/bin/mkdir","mkdir", "-p", Path, NULL);
                break;
                                                                                
            default:
            {
                int child;
                int status;
                                                                                
                child = wait(&status);
                printf("Process %i terminated with status %i\n", 
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

//calls create sub
//then copies files into their respective subdirectories//

void copy(int *OutputIndex, int SizeO, char* Destination, FILES *Files)
{
    int index;
    int mtime;
    char Source[MAXPATHLEN];
    char FullDestination[MAXPATHLEN];
    char *Spath;
    char *name;
    char *SubPath;

    //create sub folders//   
    CreateSub(OutputIndex, SizeO, Destination, Files);

    for(int i = 0; i<SizeO; i++)
    {
        //ease of reading//
        index = OutputIndex[i];
        Spath = Files[index].path;
        name = Files[index].name;
        mtime = Files[index].modTime;
        SubPath = Files[index].subPath;
        sprintf(Source, "%s/%s",Spath,name);       
        sprintf(FullDestination, "%s%s/%s",Destination,SubPath,name);  
        char buffer[PIPESIZE];
        size_t got;
        struct timeval newtimes[2];

        //copy
        printf("\nSource %s\n", Source);
        printf("Destination %s\n", FullDestination);

        //open and check//
        int fdS = open(Source, O_RDONLY);
        if(fdS == -1)
        {
            fprintf(stderr, "Failed open %s\n", Source);
            exit(EXIT_FAILURE);
        }
        int fdD = open(FullDestination, O_WRONLY|O_CREAT, 0600);
        if(fdD == -1)
        {
            close(fdS);
            fprintf(stderr, "Failed open %s\n", Source);
            exit(EXIT_FAILURE);

        }

        while((got = read(fdS, buffer, sizeof(buffer)))>0)
        {
            if(write(fdD, buffer, got) != got)
            {
                close(fdS); 
                close(fdD);
                fprintf(stderr, "Failed write %s\n", Source);
                exit(EXIT_FAILURE); 
            }
        }

        close(fdS); 
        close(fdD);   

        //change modtime//
        newtimes[0].tv_sec = mtime;
        newtimes[0].tv_usec = 0;
        newtimes[1].tv_sec = mtime;
        newtimes[1].tv_usec = 0;
        
        utimes(FullDestination,newtimes);
    }
}

