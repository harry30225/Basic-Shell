#include "headers.h"
#include "main.h"
#include "takeinput.h"
#include "prompt.h"
#include "systemcommand.h"
#include "io.h"
void piping(char **argument, int no_of_arg)
{
    int pipes[50];
    int read = 0;
    for (int i = 0; i < 50; i++)
        pipes[i] = 0;
    int total_pipes = 0;
    for (int i = 0; i < no_of_arg; i++)
    {
        if (strcmp(argument[i], "|") == 0)
        {
            pipes[total_pipes] = i;
            total_pipes++;
        }
    }
    for (int i = 0; i <= total_pipes; i++)
    {
        int flag_io = 0, size_of_args1 = 0;
        // parsing commands
        char **args1 = (char **)malloc(256);
        if (i == 0)
        {
            for (int j = 0; j < pipes[0]; j++)
            {
                args1[j] = (char *)malloc(256 * sizeof(char));
                strcpy(args1[j], argument[j]);
                if (strcmp(argument[j], "<") == 0 || strcmp(argument[j], ">") == 0 || strcmp(argument[j], ">>") == 0)
                {
                    flag_io = 1;
                }
            }
            args1[pipes[0]] = (char *)malloc(256 * sizeof(char));
            args1[pipes[0]] = 0;
            size_of_args1 = pipes[0];
            //    for (int j = 0; j < pipes[0]; j++)
            //    {
            //        printf("%s ", args1[j]);
            //    }
            //    printf("\n");
        }
        else if (i > 0 && i != total_pipes)
        {
            for (int j = pipes[i - 1] + 1; j < pipes[i]; j++)
            {
                args1[j - pipes[i - 1] - 1] = (char *)malloc(256 * sizeof(char));
                strcpy(args1[j - pipes[i - 1] - 1], argument[j]);
                if (strcmp(argument[j], "<") == 0 || strcmp(argument[j], ">") == 0 || strcmp(argument[j], ">>") == 0)
                {
                    flag_io = 1;
                }
            }
            args1[pipes[i] - pipes[i - 1] - 1] = (char *)malloc(256 * sizeof(char));
            args1[pipes[i] - pipes[i - 1] - 1] = 0;
            size_of_args1 = pipes[i] - pipes[i - 1] - 1;
            //    for (int j = 0; j < pipes[i] - pipes[i - 1] - 1; j++)
            //    {
            //        printf("%s ", args1[j]);
            //    }
            //    printf("\n");
        }
        else
        {
            for (int j = pipes[i - 1] + 1; j < no_of_arg; j++)
            {
                args1[j - pipes[i - 1] - 1] = (char *)malloc(256 * sizeof(char));
                strcpy(args1[j - pipes[i - 1] - 1], argument[j]);
                if (strcmp(argument[j], "<") == 0 || strcmp(argument[j], ">") == 0 || strcmp(argument[j], ">>") == 0)
                {
                    flag_io = 1;
                }
            }
            args1[no_of_arg - pipes[i - 1] - 1] = (char *)malloc(256 * sizeof(char));
            args1[no_of_arg - pipes[i - 1] - 1] = 0;
            size_of_args1 = no_of_arg - pipes[i - 1] - 1;
        }
        //   for (int j = 0; j < size_of_args1; j++)
        //   {
        //       printf("%s ", args1[j]);
        //   }
        //   printf("\n");
        // starting the real pipe thing
        int fd[2];
        if (pipe(fd) < 0)
        {
            perror("Unable to make pipe : ");
        }
        else
        {
            int pid = fork();
            if (pid < 0)
            {
                perror("Unable to fork : ");
            }
            else if (pid == 0)
            {
                // printf("%d  %d\n", fd[0], fd[1]);
                //    fprintf(stderr, "read %d\n", read);
                //    fprintf(stderr, "fd[1] %d\n", fd[1]);
                //    fprintf(stderr, "fd[0] %d\n", fd[0]);
                if (dup2(read, STDIN_FILENO) < 0)
                {
                    perror("Unable to make file descriptor : ");
                }
                if (i != total_pipes)
                {
                    int t = dup2(fd[1], STDOUT_FILENO);
                    if (t < 0)
                    {
                        perror("Unable to make file descritor");
                    }
                }
                close(fd[0]);
                if (flag_io == 1)
                {
                    io(args1, size_of_args1);
                }
                else
                {

                    if (execvp(args1[0], args1) < 0)
                    {
                        perror("Execute : ");
                        exit(0);
                    }
                }
                exit(1);
            }
            else
            {
                wait(NULL);
                // fprintf(stderr, "Wtf??\n");
                close(fd[1]);
                read = fd[0];
                //  fprintf(stderr, "fd[1] %d\n", fd[1]);
                //  fprintf(stderr, "fd[0] %d\n", fd[0]);
            }
        }
        free(args1);
    }
}