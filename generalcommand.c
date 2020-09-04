#include "headers.h"
#include "main.h"
#include "takeinput.h"
#include "systemcommand.h"
#include "prompt.h"
#include "ls.h"
#include "pinfo.h"

void generalcommand(char **argument, int no_of_arg)
{
    if (no_of_arg != 0)
    {
        // pwd command
        if (strcmp(argument[0], "pwd") == 0)
        {
            char currentdir[1024];
            getcwd(currentdir, 1024);
            printf("%s\n", currentdir);
        }
        // echo command
        else if (strcmp(argument[0], "echo") == 0)
        {
            for (int i = 1; i < no_of_arg; i++)
            {
                printf("%s ", argument[i]);
            }
            printf("\n");
        }
        // cd command
        else if (strcmp(argument[0], "cd") == 0)
        {
            if (strcmp(argument[1], "~") == 0)
            {
                int cderror = chdir(home);
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
        //ls command
        else if (strcmp(argument[0], "ls") == 0)
        {
            ls(argument, no_of_arg, home);
        }
        //pinfo command
        else if (strcmp(argument[0], "pinfo") == 0)
        {
            pinfo(argument, no_of_arg);
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
}