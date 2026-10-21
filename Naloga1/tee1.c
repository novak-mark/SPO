#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 128

int main(int argc,char *argv[])
{
    int fd;
    int number_of_bytes;
    int bytes_written;
    char *path_to_file;
    char buf[MAX_BUFFER_SIZE];

    if(argc > 2)
    {
        
        if(strcmp(argv[1],"-a") == 0)
        {
            path_to_file = argv[2];
            fd = open(path_to_file,O_RDWR | O_APPEND);
        }
        else 
        {
            printf("Napacen argument \n");
            exit(3);
        }
    }
    else
    {
        path_to_file = argv[1];
        fd = open(path_to_file,O_RDWR);
    }

    if(fd < 0)
    {
        perror("Open error");
        exit(1);
    }


    while( (number_of_bytes = read(STDIN_FILENO, buf, MAX_BUFFER_SIZE)) > 0)
    {
		if ( write(fd, buf, number_of_bytes) != number_of_bytes)
        {
			printf("Napaka.\n");
        }
        printf("%s",buf);
        
    }
    close(fd);
    return 0;

}