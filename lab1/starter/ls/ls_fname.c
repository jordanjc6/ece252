/**
 * @file: ls_fname.c
 * @brief: simple ls command to list file names of a directory 
  */

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>   /* for printf().  man 3 printf */
#include <stdlib.h>  /* for exit().    man 3 exit   */
#include <string.h>  /* for strcat().  man strcat   */

int main(int argc, char *argv[]) 
{
    DIR *p_dir;
    struct dirent *p_dirent;
    char str[64];

    if (argc == 1) { // no directory name specified
        fprintf(stderr, "Usage: %s <directory name>\n", argv[0]); // print content in file
        exit(1); // minor error
    }

    if ((p_dir = opendir(argv[1])) == NULL) { // no such directory existing
        sprintf(str, "opendir(%s)", argv[1]); // format string to be printed and store in str
        perror(str);
        exit(2); // major error
    }

    while ((p_dirent = readdir(p_dir)) != NULL) { // loop until there is no next directory entry
        char *str_path = p_dirent->d_name;  /* relative path name! (d_name is file name) */ 

        if (str_path == NULL) {
            fprintf(stderr,"Null pointer found!"); 
            exit(3);
        } else {
            printf("%s\n", str_path);
        }
    }

    if ( closedir(p_dir) != 0 ) { // if close fails
        perror("closedir");
        exit(3);
    }

    return 0;
}
