#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 500


int main(int argc,char *argv[])
{
    int fd,fd_current;

    int status;
    struct stat buff;
    struct stat buff_current;


    

    int numb_of_elements = 0;


    
    DIR *current_dir;
    DIR *parrent_dir;

    struct dirent *parrent_dirp;
    struct dirent *current_dirp;


    //current_dir = opendir(".");

    while(1)
    {
        fd = stat(".",&buff);
        fd_current = stat("..",&buff_current);

        if(buff.st_ino == buff_current.st_ino)
        {
            break;
        }
        parrent_dir = opendir("..");


        while ((parrent_dirp = readdir(parrent_dir)) != NULL)
        {
            if (parrent_dirp == NULL)
            {
                perror("Read error");
                exit(2);
            }

            if (parrent_dirp->d_ino == buff.st_ino)
            {
                printf("current dir: %s \n", parrent_dirp->d_name);
                
                
                
                break;
            }
        }
          
        closedir(parrent_dir);
        chdir("..");

    }

    

    


    

    return 0;

}