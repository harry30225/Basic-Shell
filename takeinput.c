#include "headers.h"
#include "ls.h"
#include "main.h"
#include "prompt.h"
#include "generalcommand.h"
#include "systemcommand.h"
#include "pinfo.h"

void takeinput()
{
    char buffer[100000];
    char *b = buffer;
    size_t bufsize = 100000;
    int characters = getline(&b, &bufsize, stdin);
    input_count++;
    //Tokenize extra spaces and tabs
    char *a = strtok(buffer, ";");
    while (a != NULL)
    {
        if (strlen(a) > 0)
        {
            char **arguments = (char **)malloc(1024 * sizeof(char *));
            int j = 0;
            arguments[j] = (char *)malloc(1024 * sizeof(char));
            for (int i = 0; i < strlen(a) - 1; i++)
            {
                int k = 0;
                while (a[i] != ' ')
                {
                    arguments[j][k] = a[i];
                    i++;
                    k++;
                    if (i >= strlen(a) - 1)
                    {
                        arguments[j][k] = '\0';
                        break;
                    }
                    if (a[i] == ' ')
                    {
                        arguments[j][k] = '\0';
                    }
                }
                if (k != 0)
                {
                    j++;
                    arguments[j] = (char *)malloc(1024 * sizeof(char));
                }
            }
            arguments[j] = NULL;
            // for (int i = 0; i < j; i++)
            // {
            //     printf("%s ", arguments[i]);
            // // }
            char addre[2048] = "";
            strcat(addre, home);
            strcat(addre, "/");
            strcat(addre, "history.txt");
            int kj = 0;
            char hists[20][256];
            for (int i = 0; i < 20; i++)
            {
                for (int k = 0; k < 256; k++)
                {
                    hists[i][k] = '\0';
                }
            }
            int fd1 = open(addre, O_RDWR);
            if (fd1 < 0)
            {
                perror("history.txt - ");
            }
            else
            {
                char buffer1[1024] = "";
                int chars = read(fd1, buffer1, 1024);
                //  printf("%s\n", buffer);
                for (int i = 0; i < chars; i++)
                {
                    int k = 0;
                    while (buffer1[i] != '\n')
                    {
                        hists[kj][k] = buffer1[i];
                        k++;
                        i++;
                        if (buffer1[i] == '\n' || i >= chars)
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

            if (j > 0)
            {
                if (kj < 20)
                {
                    int fd1 = open(addre, O_WRONLY | O_APPEND | O_CREAT);
                    if (fd1 < 0)
                    {
                        perror("history.txt - ");
                    }
                    else
                    {
                        for (int i = 0; i < j; i++)
                        {
                            write(fd1, arguments[i], strlen(arguments[i]));
                            write(fd1, " ", 1);
                        }
                        write(fd1, "\n", 1);
                    }
                    close(fd1);
                }
                else
                {
                    int fd11 = open(addre, O_WRONLY | O_TRUNC);
                    if (fd11 < 0)
                    {
                        perror("history.txt - ");
                    }
                    else
                    {
                        lseek(fd11, 0, SEEK_SET);
                        for (int i = 1; i < kj; i++)
                        {
                            write(fd11, hists[i], strlen(hists[i]));
                            write(fd11, "\n", 1);
                        }
                    }
                    close(fd11);
                    int fd111 = open(addre, O_WRONLY | O_APPEND);
                    if (fd111 < 0)
                    {
                        perror("history.txt - ");
                    }
                    else
                    {
                        for (int i = 0; i < j; i++)
                        {
                            write(fd111, arguments[i], strlen(arguments[i]));
                            write(fd111, " ", 1);
                        }
                        write(fd111, "\n", 1);
                    }
                    close(fd111);
                }
            }
            if (j > 0)
            {
                generalcommand(arguments, j);
            }
            free(arguments);
        }
        a = strtok(NULL, ";");
    }
}
