#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc,char *argv[])
{
    int fd;
    int file_size;
    int number_of_bytes;
    int bytes_written;
    char *path_to_file;
    char buf[MAX_BUFFER_SIZE];
    char test;
    int filesize;
    int i;
    int count = 0;
    int lines_to_read = 5;
    int bytes_to_write;
    
    if(argc > 3)
    {
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

     

     for (i = filesize; i > 0; i--) 
     {
        lseek(fd, i, SEEK_SET);

        number_of_bytes = read(fd, &test,1);
        if(number_of_bytes != 1)
        {
            printf("Read ERROR");
            exit(2);
        }
        if(test == '\n')
        {

            count++;
            if(count >= lines_to_read)
            {
                
                i++;
                break;
            }
        }
    }

    lseek(fd,i,SEEK_SET);

    while(number_of_bytes = read(fd,&test,1) > 0)
    {
        printf("%c",test);
    }


    
    close(fd);
    return 0;
}