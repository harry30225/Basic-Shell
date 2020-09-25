#include "headers.h"
#include "main.h"
#include "takeinput.h"
#include "systemcommand.h"
#include "prompt.h"
#include "ls.h"
#include "pinfo.h"
#include "history.h"
#include "io.h"
#include "jobs.h"

void generalcommand(char **argument, int no_of_arg)
{
    if (no_of_arg != 0)
    {
        // pwd command
        if (strcmp(argument[0], "pwd") == 0)
        {
            if (strcmp(argument[no_of_arg - 1], "&") == 0)
            {
                systemcommand(argument, no_of_arg);
            }
            else
            {

                char currentdir[1024];
                getcwd(currentdir, 1024);
                printf("%s\n", currentdir);
            }
        }
        // echo command
        else if (strcmp(argument[0], "echo") == 0)
        {
            if (strcmp(argument[no_of_arg - 1], "&") == 0)
            {
                systemcommand(argument, no_of_arg);
            }
            else
            {
                for (int i = 1; i < no_of_arg; i++)
                {
                    printf("%s ", argument[i]);
                }
                printf("\n");
            }
        }
        // cd command
        else if (strcmp(argument[0], "cd") == 0)
        {
            if (strcmp(argument[no_of_arg - 1], "&") == 0)
            {
                systemcommand(argument, no_of_arg);
            }
            else
            {

                if (strcmp(argument[1], "~") == 0 || strncmp(argument[1], "~", 1) == 0)
                {
                    char addr[2048] = "";
                    strcpy(addr, home);
                    for (int i = 1; i < strlen(argument[1]); i++)
                    {
                        addr[strlen(home) + i - 1] = argument[1][i];
                    }
                    int cderror = chdir(addr);
                    if (cderror != 0)
                    {
                        perror("cd command : ");
                    }
                }
                else
                {
                    int cderror = chdir(argument[1]);
                    if (cderror != 0)
                    {
                        perror("cd command : ");
                    }
                }
            }
        }
        //ls command
        else if (strcmp(argument[0], "ls") == 0)
        {
            if (strcmp(argument[no_of_arg - 1], "&") == 0)
            {
                systemcommand(argument, no_of_arg);
            }
            else
            {
                ls(argument, no_of_arg, home);
            }
        }
        //pinfo command
        else if (strcmp(argument[0], "pinfo") == 0)
        {
            if (strcmp(argument[no_of_arg - 1], "&") == 0)
            {
                systemcommand(argument, no_of_arg);
            }
            else
            {
                pinfo(argument, no_of_arg);
            }
        }
        //history command
        else if (strcmp(argument[0], "history") == 0)
        {
            if (strcmp(argument[no_of_arg - 1], "&") == 0)
            {
                systemcommand(argument, no_of_arg);
            }
            else
            {
                history(no_of_arg, argument);
            }
        }
        //setenv command
        else if (strcmp(argument[0], "setenv") == 0)
        {
            if (no_of_arg < 2 || no_of_arg > 3)
            {
                printf("Invalid Command Set\n");
            }
            else if (no_of_arg == 2)
            {
                char str1[512] = "";
                char str2[512] = "";
                strcpy(str1, argument[1]);
                if (setenv(str1, str2, 1) < 0)
                {
                    perror("setenv : ");
                }
            }
            else
            {
                char str1[512] = "";
                char str2[512] = "";
                strcpy(str1, argument[1]);
                strcpy(str2, argument[2]);
                if (setenv(str1, str2, 1) < 0)
                {
                    perror("setenv : ");
                }
            }
        }
        //unsetenv command
        else if (strcmp(argument[0], "unsetenv") == 0)
        {
            if (no_of_arg != 2)
            {
                printf("Inavlid Command Set \n");
            }
            else
            {
                char str[512] = "";
                strcpy(str, argument[1]);
                if ((getenv(str)))
                {
                    if (unsetenv(str) < 0)
                    {
                        perror("unsetenv : ");
                    }
                }
                else
                {
                    printf("env does not exist\n");
                }
            }
        }
        // jobs command
        else if (strcmp(argument[0], "jobs") == 0)
        {
            jobs(argument, no_of_arg);
        }
        //kjob command
        else if (strcmp(argument[0], "kjob") == 0)
        {
            kjob(argument, no_of_arg);
        }
        //overkill command
        else if (strcmp(argument[0], "overkill") == 0)
        {
            overkill(argument, no_of_arg);
        }
        // System Command
        else
        {
            if (strlen(argument[0]) != 0)
            {
                systemcommand(argument, no_of_arg);
            }
        }
    }
    else
    {
        printf("Insufficient arguments provided\n");
    }
}