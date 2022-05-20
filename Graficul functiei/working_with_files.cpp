#include <string.h>
#include <iostream>

extern char path_dir[255];


void read_file(char str[], char name[])
{
    FILE *fptr;

    char path_file[255] = "";
    strcpy(path_file, path_dir);
    strcat(path_file, "\\files\\");
    strcat(path_file, name);

    if ((fptr = fopen(path_file,"r")) != NULL)
        {
        fscanf(fptr,"%s", str);
        fclose(fptr);
        }
}

void write_file(char str[], char name[])
{
    FILE *fptr;

    char path_file[255] = "";
    strcpy(path_file, path_dir);
    strcat(path_file, "\\files\\");
    strcat(path_file, name);

    if ((fptr = fopen(path_file,"w")) != NULL)
        {
        fprintf(fptr,"%s", str);
        fclose(fptr);
        }
}
