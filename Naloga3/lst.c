#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

#define MAX_BUFFER_SIZE 128


struct file 
{
    char *file_name;
    time_t mtime;
};

int comp(const void *a, const void *b)
{
    struct file *file_a =  (struct file*)a;
    struct file *file_b =  (struct file*)b;

    if(file_a->mtime < file_b->mtime)
    {
        return 1;
    }
    else if(file_a->mtime > file_b->mtime)
    {
        return -1;
    }
    else 
    {
        return 0;
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
    path_to_dir = argv[1];

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
        file_count++;
    }

    rewinddir(target_dir);

    //struct file file_array[file_count];

    struct file* ptr = (struct file*) malloc(file_count*sizeof(struct file));

    int i = 0;

    while((dirp = readdir(target_dir)) != NULL)
    {
        //you need to construct the path to the file, so stat can read the file.
        sprintf(file_path,"%s/%s",path_to_dir,dirp->d_name);
        
        status = stat(file_path,&buff);

        if(status < 0)
        {
            perror("Stat error");
            exit(3);
        }

        //printf("%s time modified: %s  \n",dirp->d_name, ctime(&buff.st_mtime));

        
        ptr[i].file_name = dirp->d_name;
        
        ptr[i].mtime = buff.st_mtime;

        i++;
    
    }
    //printf("%s %s\n", ptr[3].file_name, ctime(&ptr[3].mtime));

    qsort(ptr,file_count,sizeof(struct file),comp);

    for(int j=0; j < file_count; j++)
    {
        //printf("%d \n",j);
        printf("%s %s", ptr[j].file_name, ctime(&ptr[j].mtime));

    }




    


    closedir(target_dir);
    free(ptr);

    return 0;

}