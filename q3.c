#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct stat buffer ;
char str[100];
int strl;

char* getfilename(char *path){
    char *filename = strrchr(path,'/');
    if(filename)
        return filename+1;
    else
        return (char*)path;
}

int main(int argc, char **argv){

    // if input file name is not provided then throw an error and exit
    if(argc < 2){
        strl = sprintf(str,"Please provide input file name\n");
        write(1,str,strl);
        exit(0);
    }

    // get input file name from path
    char *inputfilename = getfilename(argv[1]);

    // Generate output file 1 name from the input file name
    int length = strlen(inputfilename);
    length += 3;
    char* temp = "1_";
    char outputfilename1[length];
    strcpy(outputfilename1,temp);
    strcat(outputfilename1,inputfilename);
    char* directory = "Assignment/";
    length += strlen(directory);
    char fullpath1[length];
    strcpy(fullpath1,directory);
    strcat(fullpath1,outputfilename1);

    // generate output file 2 name from input file name
    char* temp2 = "2_";
    char outputfilename2[length];
    strcpy(outputfilename2,temp2);
    strcat(outputfilename2,inputfilename);
    char fullpath2[length];
    strcpy(fullpath2,directory);
    strcat(fullpath2,outputfilename2);

    // check if "Assignment" directory is created or not
    int fd = stat("Assignment",&buffer);
    if(fd == 0 && S_ISDIR(buffer.st_mode)){
        strl = sprintf(str,"Directory Created: Yes\n\n");
        write(1,str,strl);
    }
    else{
        strl = sprintf(str,"Directory Created: No\n\n");
        write(1,str,strl);
    }

    // if not able to get status of directory then show error and exit
    // else print the directory permissions
    if(fd < 0){
        perror("Error");
    }
    else{
        mode_t fileperm = buffer.st_mode ;
        if(fileperm & 00400){
            strl = sprintf(str,"User has read permission on Directory: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"User has read permission on Directory: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00200){
            strl = sprintf(str,"User has write permission on Directory: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"User has write permission on Directory: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00100){
            strl = sprintf(str,"User has execute permission on Directory: Yes\n\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"User has execute permission on Directory: No\n\n");
            write(1,str,strl);
        }
        if(fileperm & 00040){
            strl = sprintf(str,"\nGroup has read permission on Directory: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"\nGroup has read permission on Directory: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00020){
            strl = sprintf(str,"Group has write permission on Directory: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"Group has write permission on Directory: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00010){
            strl = sprintf(str,"Group has execute permission on Directory: Yes\n\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"Group has execute permission on Directory: No\n\n");
            write(1,str,strl);
        }
        if(fileperm & 00004){
            strl = sprintf(str,"\nOther have read permission on Directory: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"\nOther have read permission on Directory: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00002){
            strl = sprintf(str,"Others have write permission on Directory: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"Others have write permission on Directory: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00001){
            strl = sprintf(str,"Others have execute permission on Directory: Yes\n\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"Others have execute permission on Directory: No\n\n");
            write(1,str,strl);
        }
    }

    // get stat of output file 1
    int result = stat(fullpath1,&buffer);

    // if not able to get stat then display an error and exit
    // else print output file 1 permissions
    if(result < 0){
        perror("Error");
    }
    else{
        mode_t fileperm = buffer.st_mode ;
        if(fileperm & 00400){
            strl = sprintf(str,"User has read permission on output_file_1: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"User has read permission on output_file_1: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00200){
            strl = sprintf(str,"User has write permission on output_file_1: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"User has write permission on output_file_1: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00100){
            strl = sprintf(str,"User has execute permission on output_file_1: Yes\n\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"User has execute permission on output_file_1: No\n\n");
            write(1,str,strl);
        }
        if(fileperm & 00040){
            strl = sprintf(str,"\nGroup has read permission on output_file_1: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"\nGroup has read permission on output_file_1: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00020){
            strl = sprintf(str,"Group has write permission on output_file_1: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"Group has write permission on output_file_1: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00010){
            strl = sprintf(str,"Group has execute permission on output_file_1: Yes\n\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"Group has execute permission on output_file_1: No\n\n");
            write(1,str,strl);
        }
        if(fileperm & 00004){
            strl = sprintf(str,"\nOther have read permission on output_file_1: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"\nOther have read permission on output_file_1: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00002){
            strl = sprintf(str,"Others have write permission on output_file_1: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"Others have write permission on output_file_1: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00001){
            strl = sprintf(str,"Others have execute permission on output_file_1: Yes\n\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"Others have execute permission on output_file_1: No\n\n");
            write(1,str,strl);
        }
    }

    // get stat of output_file_2
    result = stat(fullpath2,&buffer);

    // if not able to get the stat then display an error
    // else print the permissions of the output_file_2
    if(result < 0){
        perror("Error");
    }
    else{
        mode_t fileperm = buffer.st_mode ;
        if(fileperm & 00400){
            strl = sprintf(str,"User has read permission on output_file_2: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"User has read permission on output_file_2: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00200){
            strl = sprintf(str,"User has write permission on output_file_2: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"User has write permission on output_file_2: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00100){
            strl = sprintf(str,"User has execute permission on output_file_2: Yes\n\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"User has execute permission on output_file_2: No\n\n");
            write(1,str,strl);
        }
        if(fileperm & 00040){
            strl = sprintf(str,"\nGroup has read permission on output_file_2: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"\nGroup has read permission on output_file_2: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00020){
            strl = sprintf(str,"Group has write permission on output_file_2: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"Group has write permission on output_file_2: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00010){
            strl = sprintf(str,"Group has execute permission on output_file_2: Yes\n\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"Group has execute permission on output_file_2: No\n\n");
            write(1,str,strl);
        }
        if(fileperm & 00004){
            strl = sprintf(str,"\nOther have read permission on output_file_2: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"\nOther have read permission on output_file_2: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00002){
            strl = sprintf(str,"Others have write permission on output_file_2: Yes\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"Others have write permission on output_file_2: No\n");
            write(1,str,strl);
        }
        if(fileperm & 00001){
            strl = sprintf(str,"Others have execute permission on output_file_2: Yes\n\n");
            write(1,str,strl);
        }
        else{
            strl = sprintf(str,"Others have execute permission on output_file_2: No\n\n");
            write(1,str,strl);
        }
    }
}