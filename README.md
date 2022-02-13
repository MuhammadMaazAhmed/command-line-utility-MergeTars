# command-line-utility-MergeTars
 Project Authors: Muhammad Maaz Ahmed
                  Joshua Rachpaul
Project Description
A  command-line utility program that merges the contents of multiple tar archive files into a single tar archive file .
The inputs are merged to form the output according to the following definitions and rules:
 --Two or more files from different archives are considered the same file if they have the same relative pathname (including the name of the directory holding the file and the        filename itself).
   If from different archives, the files "project2/src/mergetars.c" and "project2/src/mergetars.c" are considered the same file.
   In contrast, "monday/project2/src/mergetars.c" and "wednesday/project2/src/mergetars.c" are considered different files.

--Two or more files from different archives with the same relative pathname, are considered different versions of the same file. The output archive should contain just the latest   of all such versions.
  If two or more files have the same modification time, then the largest of these will be copied. If two or more files have the same modification time and size, the file from     the latest tarfile (on the command-line) will be copied.
--All other files with different relative pathnames are considered different files. The output archive should contain one copy of each different file.

Program invocation
The purpose of your mergetars command-line utility is to merge the contents of multiple tar archive files into a single tar archive. The program receives the name of one or more input filenames, and a single output filename (if only a single input filename is provided, then mergetars will act like a simple file-copying program, although there is no requirement to check for this special case). A typical program invocation is:

prompt>  ./mergetars input_tarfile1 [input_tarfile2 ...] output_tarfile
