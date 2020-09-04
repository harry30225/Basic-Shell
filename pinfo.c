#include "headers.h"
#include "main.h"
#include "prompt.h"
#include "pinfo.h"

void pinfo(char **argument, int no_of_arg)
{
    char filepath[1024] = "";
    if (no_of_arg == 1)
    {
        strcat(filepath, "/proc/self/stat");
    }
    else
    {
        strcat(filepath, "/proc/");
        strcat(filepath, argument[1]);
        strcat(filepath, "/stat");
    }
    int fd1 = open(filepath, O_RDONLY);
    if (fd1 == -1)
    {
        perror("");
    }
    else
    {
        char buffer[512];
        int chars = read(fd1, buffer, 512);
        char divs[100][100];
        int index = 0;
        for (int i = 0; i < chars; i++)
        {
            int k = 0;
            while (buffer[i] != ' ')
            {
                divs[index][k] = buffer[i];
                i++;
                k++;
            }
            if (k != 0)
            {
                index++;
            }
        }
        char path[128] = "~/";
        for (int i = 1; i < strlen(divs[1]) - 1; i++)
        {
            path[i + 1] = divs[1][i];
        }
        printf("pid --  %s\n", divs[0]);
        printf("Process Status --  %s\n", divs[2]);
        printf("memory --  %s\n", divs[22]);
        printf("Executable path -- %s\n", path);
    }
}