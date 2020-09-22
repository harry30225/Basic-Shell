#include "headers.h"
#include "main.h"
#include "takeinput.h"
#include "prompt.h"
#include "systemcommand.h"

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
        // parsing commands
        char **args1 = (char **)malloc(256);
        if (i == 0)
        {
            for (int j = 0; j < pipes[0]; j++)
            {
                args1[j] = (char *)malloc(256 * sizeof(char));
                strcpy(args1[j], argument[j]);
            }
            args1[pipes[0]] = (char *)malloc(256 * sizeof(char));
            args1[pipes[0]] = 0;
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
            }
            args1[pipes[i] - pipes[i - 1] - 1] = (char *)malloc(256 * sizeof(char));
            args1[pipes[i] - pipes[i - 1] - 1] = 0;
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
            }
            args1[no_of_arg - pipes[i - 1] - 1] = (char *)malloc(256 * sizeof(char));
            args1[no_of_arg - pipes[i - 1] - 1] = 0;
            //    for (int j = 0; j < no_of_arg - pipes[i - 1] - 1; j++)
            //    {
            //        printf("%s ", args1[j]);
            //    }
            //    printf("\n");
        }
        //  char **args2 = (char **)malloc(256);
        //  if (i + 1 < total_pipes)
        //  {
        //      for (int j = pipes[i] + 1; j < pipes[i + 1]; j++)
        //      {
        //          args2[j - pipes[i] - 1] = (char *)malloc(256 * sizeof(char));
        //          strcpy(args2[j - pipes[i] - 1], argument[j]);
        //      }
        //      args2[pipes[i + 1] - pipes[i] - 1] = (char *)malloc(256 * sizeof(char));
        //      args2[pipes[i + 1] - pipes[i] - 1] = 0;
        //  }
        //  else
        //  {
        //      for (int j = pipes[i] + 1; j < no_of_arg; j++)
        //      {
        //          args2[j - pipes[i] - 1] = (char *)malloc(256 * sizeof(char));
        //          strcpy(args2[j - pipes[i] - 1], argument[j]);
        //      }
        //      args2[no_of_arg - pipes[i] - 1] = (char *)malloc(256 * sizeof(char));
        //      args2[no_of_arg - pipes[i] - 1] = 0;
        //  }

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
                dup2(read, STDIN_FILENO);
                if (i != total_pipes)
                    dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);

                if (execvp(args1[0], args1) < 0)
                {
                    perror("Execute : ");
                    exit(0);
                }
            }
            else
            {
                wait(NULL);
                close(fd[1]);
                read = fd[0];
            }
        }
        free(args1);
    }
}