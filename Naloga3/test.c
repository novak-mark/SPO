#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <time.h>

int main(int argc,char *argv[])
{
    int fd;
    struct stat buff;
    struct passwd *file_owner;
    int status;
    char *path_to_file;
    
    
    if(argc < 1)
    {
        printf("Premalo argumentov");
        exit(1);
    }
    path_to_file = argv[1];

    status = stat(path_to_file,&buff);

    

    printf("time modified: %s \n", ctime(&buff.st_mtime));


    
    

    return 0;

}