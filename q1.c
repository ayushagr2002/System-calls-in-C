#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


char str[100];
int strl;
// function to get size of data to be processed at once(chunk size) according to file size
long getchunksize(long fileLength){
    if(fileLength <= 10)    // 10B
        return 1;
    else if(fileLength <= 100)  // 100B
        return 1;
    else if(fileLength <= 1000)   // 1 KB
        return 10;
    else if(fileLength <= 10000)    // 10 KB
        return 100;
    else if(fileLength <= 100000)   // 100 KB
        return 1000;
    else if(fileLength <= 1000000)  // 1 MB
        return 10000;
    else if(fileLength <= 10000000)     // 10 MB
        return 100000;
    else                                // > 10 MB
        return 1000000;
}

// function to get file name from path
char* getfilename(char *path){
    char *filename = strrchr(path,'/');
    if(filename)
        return filename+1;
    else
        return (char*)path;
}

int main(int argc, char **argv)
{
    // if input file name is not provided then throw an error and exit
    if(argc < 2){
        strl = sprintf(str,"Please Enter input file Name\n");
        write(1,str,strl);
        exit(0);
    }

    // get input file name from path
    char *inputfilename = getfilename(argv[1]);

    // generate output file name as 1_inputfilename
    int length = strlen(inputfilename);
    length += 3;
    char* temp = "1_";
    char outputfilename[length];
    strcpy(outputfilename,temp);
    strcat(outputfilename,inputfilename);
    
    // generate path to create the output file
    char* directory = "Assignment/";
    length += strlen(directory);
    char fullpath[length];
    strcpy(fullpath,directory);
    strcat(fullpath,outputfilename);


    // make directory named "Assignment" if not already exists with read,write,execute permissions for user
    char* dirname = "Assignment";
    struct stat sb;
    int fd = stat(dirname,&sb);
    if(!((fd == 0) && S_ISDIR(sb.st_mode))){
        int created = mkdir(dirname,0700);
        if(created == -1){
            perror("Could not create directory");
            _exit(0);
        }
    }
    else
        chmod(dirname,0700);
    
    // Open input file and output file in Assignment directory
    int f_read = open(argv[1], O_RDONLY);
    if (f_read == -1)
    {
        perror("Error opening input file");
        _exit(0);
    }
    int f_write = open(fullpath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if(f_write == -1){
        perror("Error opening output file");
        _exit(0);
    }
    

    // get file length and initialise some variables
    off_t fileLength = lseek(f_read, 0, SEEK_END);
    off_t bytes_read = 0;
    off_t bytes_left = 0;

    // get chunk size according to file size
    long chunk_size = getchunksize(fileLength);

    // allocate space for 2 buffers: one to read original chunk and other to store reversed chunk
    char *p = (char*)malloc(sizeof(char) * (chunk_size + 1));
    char *r = (char*)malloc(sizeof(char) * (chunk_size + 1));
    
    

    // process the file
    while (1)
    {

        lseek(f_read, -chunk_size, SEEK_CUR);
        read(f_read, p, chunk_size);
        for (int i = 0; i < chunk_size; i++)
            r[i] = p[chunk_size - i - 1];
        r[chunk_size] = '\0';
        write(f_write, r, chunk_size);
        bytes_read += chunk_size;

        bytes_left = fileLength - bytes_read;

        if (bytes_left <= chunk_size)
        {
            lseek(f_read, -(chunk_size + bytes_left), SEEK_CUR);
            read(f_read, p, bytes_left);
            bytes_read += bytes_left;

            for (int i = 0; i < bytes_left; i++)
                r[i] = p[bytes_left - i - 1];
            r[bytes_left] = '\0';

            write(f_write, r, bytes_left);
            strl = sprintf(str,"\rProgress: %.2f%%", (float)bytes_read * 100/ fileLength);
            write(1,str,strl);

            lseek(f_read,-bytes_left,SEEK_CUR);
            break;
        }
        strl = sprintf(str,"\rProgress: %.2f%%", (float)bytes_read * 100/ fileLength);
        write(1,str,strl);
        
        lseek(f_read, -chunk_size, SEEK_CUR);
    }


    // Print "Done" and close the files and free memory allocated on heap
    strl = sprintf(str,"\nCompleted\n");
    write(1,str,strl);
    free(p);
    free(r);
    close(f_read);
    close(f_write);
}