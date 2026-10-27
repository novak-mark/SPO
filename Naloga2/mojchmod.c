#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <ctype.h>
#include <string.h>


void check_input(char *input)
{
    
    for(int i= 0; input[i] != '\0'; i++)
    {
            
        if(input[i] < '0' || input[i] > '7')
        {
            printf("ERROR: Invalid input, values must be between 0 and 7.\n");
            exit(2);
        }
    }
}

int main(int argc,char *argv[])
{
    int fd;
    struct stat buff;
    struct passwd *file_owner;
    mode_t new_mode;
    int status;
    int chmodstatus;
    char *path_to_file;
    char file_prems[10];
    char *pt_prem;
    long int input_prem;

    

    
    path_to_file = argv[2];

    status = stat(path_to_file,&buff);

    
    if(strcmp(argv[1],"u+s") == 0)
    {
        new_mode = buff.st_mode | S_ISUID;
        chmodstatus = chmod(path_to_file,new_mode);

    }
    else if(strcmp(argv[1],"u-s") == 0)
    {
        new_mode = buff.st_mode & ~S_ISUID;
        chmodstatus = chmod(path_to_file,new_mode);

    }
    else if((strcmp(argv[1],"g+s")) == 0)
    {
        new_mode = buff.st_mode | S_ISGID;

        chmodstatus = chmod(path_to_file,new_mode);
    }
    else if(strcmp(argv[1],"a+rX") == 0)
    {
        new_mode = buff.st_mode | S_IRUSR | S_IRGRP | S_IROTH;

        chmodstatus = chmod(path_to_file,new_mode);

    }

    else 
    {
        check_input(argv[1]);
        input_prem = strtol(argv[1],&pt_prem,8);

        chmodstatus = chmod(path_to_file,input_prem);
    }


    if(chmodstatus < 0)
    {
        perror("CHMOD error:");
        exit(1);
    }

    
    status = stat(path_to_file,&buff);

    //user dovoljenja
    file_prems[0] = (buff.st_mode & S_IRUSR) ? 'r' : '-';
    file_prems[1] = (buff.st_mode & S_IWUSR) ? 'w' : '-';

    if((buff.st_mode & S_IXUSR))
    {
        file_prems[2] = (buff.st_mode & S_ISUID) ? 's' : 'x';
    }
    else
    {
        file_prems[2] = (buff.st_mode & S_ISUID) ? 'S' : '-';
    }
    //group dovoljenja
    file_prems[3] = (buff.st_mode & S_IRGRP) ? 'r' : '-';
    file_prems[4] = (buff.st_mode & S_IWGRP) ? 'w' : '-';

    if((buff.st_mode & S_IXGRP))
    {
        file_prems[5] = (buff.st_mode & S_ISGID) ? 's' : 'x';
    }
    else
    {
        file_prems[5] = (buff.st_mode & S_ISGID) ? 'S' : '-';
    }
    //other dovoljenja
    file_prems[6] = (buff.st_mode & S_IROTH) ? 'r' : '-';
    file_prems[7] = (buff.st_mode & S_IWOTH) ? 'w' : '-';
    file_prems[8] = (buff.st_mode & S_IXOTH) ? 'x' : '-';
    file_prems[9] = '\0';

    printf("Nova dovoljenja: %s \n",file_prems);

    

    return 0;

}