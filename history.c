#include "headers.h"
#include "main.h"
#include "generalcommand.h"
#include "prompt.h"
#include "history.h"

void history(int no_of_arg, char **argument)
{
    // fprintf(stderr, "%d\n", no_of_arg);
    char addre[2048] = "";
    strcat(addre, home);
    strcat(addre, "/");
    strcat(addre, "history.txt");
    char hists[20][256];
    for (int i = 0; i < 20; i++)
    {
        for (int k = 0; k < 256; k++)
        {
            hists[i][k] = '\0';
        }
    }
    int fd1 = open(addre, O_RDWR);
    //  int fd1 = open(addre, O_RDWR);
    int kj = 0;
    if (fd1 < 0)
    {
        perror("history.txt - ");
    }
    else
    {
        char buffer[1024] = "";
        int chars = read(fd1, buffer, 1024);
        //  printf("%s\n", buffer);
        for (int i = 0; i < chars; i++)
        {
            int k = 0;
            while (buffer[i] != '\n')
            {
                hists[kj][k] = buffer[i];
                k++;
                i++;
                if (buffer[i] == '\n' || i >= chars)
                {
                    break;
                }
            }
            hists[kj][k] = '\0';
            if (k != 0)
            {
                kj++;
            }
        }
    }
    close(fd1);
    if (no_of_arg == 1)
    {
        if (kj <= 10)
        {
            for (int i = 0; i < kj; i++)
            {
                printf("%s\n", hists[i]);
            }
        }
        else
        {
            for (int i = kj - 10; i < kj; i++)
            {
                printf("%s\n", hists[i]);
            }
        }
    }
    else
    {
        int number = 0;
        int t = 1;
        for (int i = strlen(argument[1]) - 1; i >= 0; i--)
        {
            number += (int)(argument[1][i] - '0') * t;
            t = t * 10;
        }
        if (number > kj)
        {
            printf("Invalid Operation");
        }
        else
        {
            for (int i = kj - number; i < kj; i++)
            {
                printf("%s\n", hists[i]);
            }
        }
    }
}