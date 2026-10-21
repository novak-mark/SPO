#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(int argc,char *argv[])
{
    int fd;
    int number_of_bytes;
    char *path_to_file;
    char znak;
    int filesize;
    int i;
    int count = 0;
    int lines_to_read = 5;
    int bytes_to_write;
    
    if(argc > 3)
    {
        if(strcmp(argv[1],"-n") != 0)
        {
            printf("Nezanani argument, pravilna uporaba: -n [STEVILO] ime_datoteke \n");
            exit(4);
        }
        lines_to_read = atoi(argv[2]);
        path_to_file = argv[3]; 
    }
    else 
    {
        path_to_file = argv[1];
    }

    fd = open(path_to_file,O_RDONLY);

    if(fd < 0)
    {
        printf("Datoteka neobstaja, prosimo ustvarite datoteko pred pisanjem \n");
        exit(1);
    }
    
    filesize = lseek(fd,-3,SEEK_END);

    if(filesize == -1)
    {
        perror("LSEEK ERROR");
        exit(3);
    }

     for (i = filesize; i > 0; i--) 
     {
        if((lseek(fd, i, SEEK_SET)) == -1)
        {
            perror("LSEEK ERROR");
            exit(3);
        }
    
        number_of_bytes = read(fd, &znak,1);
        if(number_of_bytes != 1)
        {
            perror("READ ERROR");
            exit(2);
        }
        if(znak == '\n')
        {
            count++;
            if(count >= lines_to_read)
            {       
                i++;
                break;
            }
        }
    }

    if((lseek(fd,i,SEEK_SET)) == -1)
    {
        perror("LSEEK ERROR");
        exit(3);
    }

    while(number_of_bytes = read(fd,&znak,1) > 0)
    {
        printf("%c",znak);
    }

    close(fd);
    return 0;
}