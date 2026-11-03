#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

#define MAX_BUFFER_SIZE 128
#define BLUE "\033[34m"
#define RESET "\033[0m"



int is_reverse = 0;

struct file 
{
    char *file_name;
    int is_dir;
    time_t mtime;
};

int comp(const void *a, const void *b)
{
    struct file *file_a =  (struct file*)a;
    struct file *file_b =  (struct file*)b;

    if(is_reverse)
    {
        if (file_a->mtime > file_b->mtime)
        {
            return 1;
        }
        else if (file_a->mtime < file_b->mtime)
        {
            return -1;
        }
        else
        {
            return strcmp(file_a->file_name, file_b->file_name);
        }
    }
    else 
    {
        if (file_a->mtime > file_b->mtime)
        {
            return -1;
        }
        else if (file_a->mtime < file_b->mtime)
        {
            return 1;
        }
        else
        {
            return strcmp(file_a->file_name, file_b->file_name);
        }
    }
   
}

int main(int argc,char *argv[])
{
    int fd;
    int file_count = 0;
    int status;
    struct stat buff;
    struct passwd *file_owner;
    char file_path[256];
    char *path_to_dir;
    DIR *target_dir;
    struct dirent *dirp;

 
    if(argc < 1)
    {
        printf("Premalo argumentov");
        exit(1);
    }
    if(argc > 2)
    {
        if((strcmp(argv[1],"-r")) == 0)
        {
            is_reverse = 1;
            path_to_dir = argv[2];
        }
        else 
        {
            printf("Napcani argument \n");
            exit(2);
        }
       
    }
    else
    {
        path_to_dir = argv[1];
    }
    target_dir = opendir(path_to_dir);


    if((target_dir == NULL))
    {
        perror("Cannot open dir: ");
        exit(2);
    }


    while((dirp = readdir(target_dir)) != NULL)
    {
        if(dirp == NULL)
        {
            perror("Read error");
            exit(2);
        }
        if((strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0))
        {
            continue;
        }
        if (dirp->d_name[0] == '.')
        {
            continue;
        }

        file_count++;
    }

    rewinddir(target_dir);

    

    struct file* ptr = (struct file*) malloc(file_count*sizeof(struct file));

    int i = 0;

    while((dirp = readdir(target_dir)) != NULL)
    {
        if((strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0))
        {
            continue;
        }
        if (dirp->d_name[0] == '.')
        {
            continue;
        }

        sprintf(file_path,"%s/%s",path_to_dir,dirp->d_name);

        status = stat(file_path,&buff);

        if(status < 0)
        {
            perror("Stat error");
            exit(3);
        }
        
        ptr[i].file_name = strdup(dirp->d_name);
        if(S_ISDIR(buff.st_mode))
        {
             ptr[i].is_dir = 1;
        }
        else 
        {
            ptr[i].is_dir = 0;
        }
        
        ptr[i].mtime = buff.st_mtime;

        i++;
    
    }

    qsort(ptr,file_count,sizeof(struct file),comp);

    

    for(int j=0; j < file_count; j++)
    {
        if(ptr[j].is_dir == 1)
        {
            printf(BLUE"%s/ \n"RESET, ptr[j].file_name);
        }
        else
        { 
            printf("%s \n", ptr[j].file_name);
        }
    }

    closedir(target_dir);
    for(int j = 0; j < file_count; j++)
    {
        free(ptr[j].file_name);
    }
    free(ptr);

    return 0;

}