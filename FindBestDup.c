/*-----------------------------------------------------------------------------
                            ////FILE INFO////

    FindBestDup.c is split into three functions:
        o FindBestDup - calls the below functions where relevant. Increases 
                        output array size for each unique file found and 
                        stores each unique file found in OutputIndex.
        o isBestDup - Finds the best duplicate (most recent) between two files.
        o inOutput - Checks if provided file is already in the output array.

    This was done in an attempt to make the code more readable by breaking it
    up into digestable chunks.

    Authour: Joshua Rachpaul, Muhammad Maaz Ahmed
-----------------------------------------------------------------------------*/

#include "mergetars.h"

    /*IsBestDup//
    The indicies of two files are passed to isBestDup and the best dup between
    the two is found. This function compares the first file against the second.
    Function:
        - returns true if first file (index i) is best dup.
        - returns false if second file (index ii) is best dup */

bool isBestDup(int i, int ii, FILES* Files)
{
    //variable defintions for file 1//
    char PathName1[MAXPATHLEN];
    sprintf(PathName1, "%s/%s", Files[i].subPath, Files[i].name);
    int Arg1 = Files[i].Arg;
    int mtime1 = Files[i].modTime;
    int size1 = Files[i].size;

    //variable definitions for file 2
    char PathName2[MAXPATHLEN];
    sprintf(PathName2, "%s/%s", Files[ii].subPath, Files[ii].name);
    int Arg2 = Files[ii].Arg;
    int mtime2 = Files[ii].modTime;
    int size2 = Files[ii].size;

    printf("File1: %s\n", PathName1);
    printf("File2: %s\n", PathName2);

    //Comparing//
    if(strcmp(PathName1,PathName2))
    {
        //different files//
        return true;

    }else if(!(mtime1==mtime2)){
        if(mtime1>mtime2)
        {
            //file1 is more recent//
            return true;

        } else{
            //file2 is more recent//
            return false;
        }

    } else if(!(size1==size2)){
        if(size1>size2)
        {
            //file 1 larger//
            return true;
        
        } else {
            //file 2 larger//
            return false;
        }
        return false;

    } else if(Arg1>Arg2){
        //file1 is last arg//
        return true;
    } else {
        //file2 is last arg or they're both the same//
        return false;
    }
}

    /*inOutput//
    checks if PathName1 is already in the Output, if it is, it already
    has been compared.
    returns true if PathName1 in output and false otherwise*/

bool inOutput(int SizeO, int Index1, int *OutputIndex, FILES* Files)
{
    //ease of reading defintions
    char PathName1[MAXPATHLEN];
    sprintf(PathName1, "%s/%s", Files[Index1].subPath, Files[Index1].name);

    for(int i=0; i<SizeO; i++)
    {
        //definitons for ease of reading
        char PathName2[MAXPATHLEN];
        int O_Index = OutputIndex[i];
        sprintf(PathName2,"%s/%s", Files[O_Index].subPath, Files[O_Index].name);

        if(!strcmp(PathName1, PathName2))
        {
            printf("They are the same %s %s\n", PathName1, PathName2);
            return true;
        }
    }

    printf("%s has no match\n", PathName1);
    return false;
}

    /*FindBestDup
    Finds the best duplicate of each file pathname. If a file is the most
    recent duplicate that could be found it's added to the OutputIndex array.
    The index of that file, relative to our array of files, is stored in
    OutputIndex.
    Notes:
    - Size is the size of the array of files
    - SizeO is a pointer to the size of the array OutputIndex
    - Files is an array of FILES
    - OutputIndex is a pointer to an array of integers*/

void FindBestDup(int size,int *SizeO, FILES *Files, int **OutputIndex)
{
    int O_Index;
    int Index;

    for(int i=0; i<size; i++)
    {
        //default output is the first file//
        O_Index = i;

        if(inOutput((*SizeO), i,*OutputIndex, Files))
        {
            //if its already in the Output skip comparion
            continue;

        } else {
            //the zeros are used to deallocate the pointer//
            (*SizeO)+=1;
            *OutputIndex = realloc(*OutputIndex, (*SizeO)*sizeof(**OutputIndex));
            Index = (*SizeO)-1;
        }

        //start loop after current element we're looking at//
        for(int ii = i+1; ii<size; ii++)
        {
            //if first file isn't the best dup//
            if(!isBestDup(O_Index, ii, Files))
            {
                //set output to second file//
                O_Index = ii;
            }
        }
        printf("added %i to the output\n", O_Index);
        (*OutputIndex)[Index]=O_Index;
    }
}
