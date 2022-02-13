#include "mergetars.h"

//arrays//
char** TempDir;
char* TempDestination;
char* FinalDestination;
FILES *files;
int *OutputIndex;
int size;
int SizeO;

int main(int argc, char *argv[])
{
    //Initalisations and defintions for ease of reading//
    int TempDirNeeded;
    TempDirNeeded = argc-1; //create a temp for all argument cept the command
    TempDir = malloc(TempDirNeeded*sizeof(*TempDir));
    printf("Directory Count: %i\n", TempDirNeeded);

    //FAILURE CONDITION//
    if(argc<3)
    {
        fprintf(stderr, "Mergetars expects 3 arguments, but recieved only %i\n", argc);
        exit(EXIT_FAILURE);
    }

    //TODO ADD FUNCTIONS//
    createdir(TempDirNeeded, TempDir);
    extract(TempDirNeeded, TempDir, argv);
    store(TempDirNeeded, &size, TempDir, &files);
    FindBestDup(size,&SizeO,files, &OutputIndex);
    
    TempDestination = TempDir[TempDirNeeded-1];
    FinalDestination = argv[TempDirNeeded];

    copy(OutputIndex, SizeO, TempDestination, files);
    createTar(TempDestination, FinalDestination);
    clean(TempDirNeeded, TempDir);
 
    //debugging//
    files = &files[0];

    for(int i=0; i<size; i++)
    {
        printf("\n\tALL FILES\n");
        printf("%i: %s\nPath %s\nSubPath %s\nModTime %i\n", i+1, files[i].name,
                        files[i].path, files[i].subPath,files[i].modTime);
        printf("Size %i\nArg %i\n", files[i].size, files[i].Arg);
    }

//    struct stat stat_buffer;  //turn clean off to use this functiosnsss

    for(int i=0; i<SizeO; i++)
    {
        int Index = OutputIndex[i];
    
        //Best File info stored//
        printf("\n\tFinal Output\n");
        printf("name %s \n", files[Index].name);
        printf("path %s \n", files[Index].path);
        printf("size %i \n", files[Index].size);
        printf("Mod Time %i \n", files[Index].modTime);
        printf("Arg %i \n", files[Index].Arg);
        printf("Index %i \n", OutputIndex[i]);

            //turn clean off to test this//
/*
        char* name = files[Index].name;
        char* SubPath = files[Index].subPath;
        char FullDestination[MAXPATHLEN];

        //In Destination//
        sprintf(FullDestination, "%s%s/%s",TempDestination,SubPath,name);  
        printf("Destination %s\n", FullDestination);

        if(stat(FullDestination, &stat_buffer) != 0)
        {
            perror("main");
            exit(EXIT_FAILURE);
        }
        printf("\n\tIn Temp Destination\n");       
        printf("name %s \n", FullDestination);       
        printf("size %i \n", (int)stat_buffer.st_size);
        printf("Mod Time %i \n", (int)stat_buffer.st_mtime);
*/
    }
    exit(EXIT_SUCCESS);
}
