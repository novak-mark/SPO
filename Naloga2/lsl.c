#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc,char *argv[])
{
    int fd;
    struct stat buffer;
    int status;
    char *path_to_file;
    
    path_to_file = argv[1];

    status = stat(path_to_file,&buffer);

    if(status < 0)
    {
        perror("STAT Error: ");
        exit(1);
    }
    

    return 0;

}