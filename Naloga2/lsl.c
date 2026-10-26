#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>


int main(int argc,char *argv[])
{
    int fd;
    struct stat buff;
    struct passwd *file_owner;
    int status;
    char *path_to_file;
    char file_type;
    char user_prems[4];
    char group_prems[4];
    char other_prems[4];

    
    path_to_file = argv[1];

    status = stat(path_to_file,&buff);

    if(status < 0)
    {
        perror("STAT Error: ");
        exit(1);
    }
    
    if(S_ISREG(buff.st_mode))
    {
        file_type = '.';
    }
    else if(S_ISDIR(buff.st_mode))
    {
        file_type = 'd';
    }
    else if(S_ISCHR(buff.st_mode))
    {
        file_type = 'c';
    }
    else if(S_ISBLK(buff.st_mode))
    {
        file_type = 'b';
    }
    else if(S_ISFIFO(buff.st_mode))
    {
        file_type = 'p';
    }
    else if(S_ISLNK(buff.st_mode))
    {
        file_type = 'l';
    }
    else if(S_ISSOCK(buff.st_mode))
    {
        file_type = 's';
    }
    else 
    {
        file_type = '-';
    }

    //user dovoljenja
    user_prems[0] = (buff.st_mode & S_IRUSR) ? 'r' : '-';
    user_prems[1] = (buff.st_mode & S_IWUSR) ? 'w' : '-';
    user_prems[2] = (buff.st_mode & S_IXUSR) ? 'x' : '-';
    user_prems[3] = '\0';
   //group dovoljenja
    group_prems[0] = (buff.st_mode & S_IRGRP) ? 'r' : '-';
    group_prems[1] = (buff.st_mode & S_IWGRP) ? 'w' : '-';
    group_prems[2] = (buff.st_mode & S_IXGRP) ? 'x' : '-';
    group_prems[3] = '\0';
  //other dovoljenja
    other_prems[0] = (buff.st_mode & S_IROTH) ? 'r' : '-';
    other_prems[1] = (buff.st_mode & S_IWOTH) ? 'w' : '-';
    other_prems[2] = (buff.st_mode & S_IXOTH) ? 'x' : '-';
    other_prems[3] = '\0';
    
    file_owner = getpwuid(buff.st_uid);
    
    printf("%c%s%s%s %d %s %d %s\n",file_type,user_prems,group_prems,other_prems,buff.st_nlink,file_owner->pw_name,buff.st_size,argv[1]);

    

    return 0;

}