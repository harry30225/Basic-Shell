#include "headers.h"
#include "main.h"
#include "prompt.h"
#include "pinfo.h"

void pinfo(char **argument, int no_of_arg)
{
    char filepath[1024] = "";
    char filepath2[1024] = "";
    if (no_of_arg == 1)
    {
        strcat(filepath, "/proc/self/stat");
        strcat(filepath2, "/proc/self/exe");
    }
    else
    {
        strcat(filepath, "/proc/");
        strcat(filepath, argument[1]);
        strcat(filepath, "/stat");
        strcat(filepath2, "/proc/");
        strcat(filepath2, argument[1]);
        strcat(filepath2, "/exe");
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
                if (i >= chars)
                {
                    break;
                }
            }
            if (k != 0)
            {
                index++;
            }
        }
        char datab[2048] = "";
        int endchar = readlink(filepath2, datab, 2048);
        datab[endchar] = '\0';
        if (strcmp(datab + (endchar - 9), "(deleted)") == 0)
        {
            datab[endchar - 10] = '\0';
        }
        char advdatab[2048] = "";
        if (strlen(datab) >= strlen(home))
        {
            int flag = 0;
            for (int i = 0; i < strlen(datab); i++)
            {
                int j = 0;
                while (datab[i] == home[j])
                {
                    i++;
                    j++;
                    if (j == strlen(home))
                    {
                        flag = j;
                        break;
                    }
                    if (i >= strlen(datab))
                    {
                        break;
                    }
                }
            }
            // printf("%s\n", home);
            // printf("flag %d\n", flag);
            if (flag != 0)
            {
                advdatab[0] = '~';
                //   advdatab[1] = '/';
                int j = 1;
                for (int i = flag; i < strlen(datab); i++)
                {
                    advdatab[j] = datab[i];
                    j++;
                }
            }
            else
            {
                strcpy(advdatab, datab);
            }
        }
        else
        {
            strcpy(advdatab, datab);
        }

        printf("pid --  %s\n", divs[0]);
        printf("Process Status --  %s\n", divs[2]);
        printf("memory --  %s\n", divs[22]);
        printf("Executable path -- %s\n", advdatab);
        close(fd1);
    }
}