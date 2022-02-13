//Defintion needed for mkdtemp//
#define _POSIX_C_SOURCE 200809L

//header//
#include "mergetars.h"

/*Defintions
    -TEMPLATE is the name and path of temp file created
    -SIZE is the number of elements in the char array TEMPLATE(size of string)
*/
#define TEMPLATE "/tmp/Merge-XXXXXX"
#define SIZE 20

/*createdir
    Creates temporary directories corresponding to the number of tar input
    arguments.
    Notes:
    - "TempDirectories" stores the paths of the directories created
    - "n" is the Number of directories created
*/

void createdir(int n, char** TempDirectories)
{
    //Create n Directories//
    for(int i=0; i<n; i++)  //add 1 to create tmp output directory//
    {
        char dirName[SIZE];
        
        TempDirectories[i] = malloc(SIZE*sizeof(char));

        strcpy(dirName, TEMPLATE);
        strcpy(TempDirectories[i], mkdtemp(dirName));

        if(TempDirectories[i] == NULL)
        {
            fprintf(stderr, "Failed to create Temporary Directory\n");
            exit(EXIT_FAILURE);
        }
    }
}

