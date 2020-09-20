#include "headers.h"
#include "main.h"
#include "takeinput.h"
#include "systemcommand.h"
#include "prompt.h"
#include "ls.h"
#include "pinfo.h"
#include "history.h"

void generalcommand(char **argument, int no_of_arg)
{
    if (no_of_arg != 0)
    {
        char redirect_filename[3][1024];
        int flag_i = 0, flag_o = 0, flag_io = 0;
        for (int i = 0; i < no_of_arg; i++)
        {
            if (strcmp(argument[i], "<") == 0)
            {
                if (i + 1 != no_of_arg)
                {
                    flag_i = 1;
                    if (strcmp(argument[i + 1], "~") != 0 && strncmp(argument[i + 1], "~", 1) != 0)
                    {
                        strcpy(redirect_filename[0], argument[i + 1]);
                    }
                    else
                    {
                        strcpy(redirect_filename[0], home);
                        for (int j = 1; j < strlen(argument[i + 1]); j++)
                        {

                            redirect_filename[0][strlen(home) + j - 1] = argument[i + 1][j];
                        }
                    }
                }
            }
            else if (strcmp(argument[i], ">") == 0)
            {
                if (i + 1 != no_of_arg)
                {
                    flag_o = 1;
                    if (strcmp(argument[i + 1], "~") != 0 && strncmp(argument[i + 1], "~", 1) != 0)
                    {
                        strcpy(redirect_filename[1], argument[i + 1]);
                    }
                    else
                    {
                        strcpy(redirect_filename[1], home);
                        for (int j = 1; j < strlen(argument[i + 1]); j++)
                        {

                            redirect_filename[1][strlen(home) + j - 1] = argument[i + 1][j];
                        }
                    }
                }
            }
            else if (strcmp(argument[i], ">>") == 0)
            {
                if (i + 1 != no_of_arg)
                {
                    flag_io = 1;
                    if (strcmp(argument[i + 1], "~") != 0 && strncmp(argument[i + 1], "~", 1) != 0)
                    {
                        strcpy(redirect_filename[2], argument[i + 1]);
                    }
                    else
                    {
                        strcpy(redirect_filename[2], home);
                        for (int j = 1; j < strlen(argument[i + 1]); j++)
                        {

                            redirect_filename[2][strlen(home) + j - 1] = argument[i + 1][j];
                        }
                    }
                }
            }
        }
        // pwd command
        if (strcmp(argument[0], "pwd") == 0)
        {
            if (strcmp(argument[no_of_arg - 1], "&") == 0)
            {
                systemcommand(argument, no_of_arg);
            }
            else
            {
                int fd, saved_stdout_pwd;
                saved_stdout_pwd = dup(1);
                if (flag_o == 1 && flag_io == 0)
                {
                    fd = open(redirect_filename[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
                    if (fd < 1)
                    {
                        perror("file : ");
                    }
                    else
                    {
                        if (dup2(fd, STDOUT_FILENO) < 0)
                        {
                            perror("Unable to duplicate file descriptor.");
                        }
                    }
                }
                else if (flag_o == 0 && flag_io == 1)
                {
                    fd = open(redirect_filename[2], O_RDWR | O_CREAT | O_APPEND, 0644);
                    if (fd < 1)
                    {
                        perror("file : ");
                    }
                    else
                    {
                        if (dup2(fd, STDOUT_FILENO) < 0)
                        {
                            perror("Unable to duplicate file descriptor.");
                        }
                    }
                }
                char currentdir[1024];
                getcwd(currentdir, 1024);
                printf("%s\n", currentdir);
                if (dup2(saved_stdout_pwd, STDOUT_FILENO) < 0)
                {
                    perror("Unable to duplicate file descriptor.");
                }
                close(fd);
                close(saved_stdout_pwd);
            }
        }
        // echo command
        else if (strcmp(argument[0], "echo") == 0)
        {
            int saved_stdout_echo = dup(1);
            int saved_stdin_echo = dup(STDIN_FILENO);
            int fd;
            if (strcmp(argument[no_of_arg - 1], "&") == 0)
            {
                systemcommand(argument, no_of_arg);
            }
            else
            {
                if (flag_i == 0 && flag_io == 0 && flag_o == 1)
                {
                    fd = open(redirect_filename[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
                    if (fd < 1)
                    {
                        perror("file : ");
                    }
                    else
                    {
                        if (dup2(fd, STDOUT_FILENO) < 0)
                        {
                            perror("Unable to duplicate file descriptor.");
                        }
                        else
                        {
                            for (int i = 1; i < no_of_arg - 2; i++)
                            {
                                printf("%s ", argument[i]);
                            }
                            printf("\n");
                        }
                        if (dup2(saved_stdout_echo, STDOUT_FILENO) < 0)
                        {
                            perror("Unable to duplicate file descriptor.");
                        }
                        close(fd);
                        close(saved_stdout_echo);
                    }
                }
                else if (flag_i == 1 && flag_io == 0 && flag_o == 0)
                {
                    fd = open(redirect_filename[0], O_RDWR);
                    if (fd < 1)
                    {
                        perror("file : ");
                    }
                    else
                    {
                        char buffer[10240] = "";
                        read(fd, buffer, 10240);
                        printf("%s\n", buffer);

                        close(fd);
                    }
                }
                else if (flag_i == 0 && flag_io == 1 && flag_o == 0)
                {
                    fd = open(redirect_filename[2], O_RDWR | O_CREAT | O_APPEND, 0644);
                    if (fd < 1)
                    {
                        perror("file : ");
                    }
                    else
                    {
                        if (dup2(fd, STDOUT_FILENO) < 0)
                        {
                            perror("Unable to duplicate file descriptor.");
                        }
                        else
                        {
                            for (int i = 1; i < no_of_arg - 2; i++)
                            {
                                printf("%s ", argument[i]);
                            }
                            printf("\n");
                        }
                        if (dup2(saved_stdout_echo, STDOUT_FILENO) < 0)
                        {
                            perror("Unable to duplicate file descriptor.");
                        }
                        close(fd);
                        close(saved_stdout_echo);
                    }
                }
                else if (flag_i == 1 && (flag_io == 1 || flag_o == 1))
                {
                    int fd_read = open(redirect_filename[0], O_RDWR);
                    if (fd_read < 0)
                    {
                        perror("readfile : ");
                    }
                    else
                    {
                        char buffer[10240] = "";
                        read(fd_read, buffer, 10240);
                        if (flag_o == 1 && flag_io == 0)
                        {
                            fd = open(redirect_filename[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
                            if (fd < 0)
                            {
                                perror("file : ");
                            }
                            else
                            {
                                if (dup2(fd, STDOUT_FILENO) < 0)
                                {
                                    perror("Unable to duplicate file descriptor");
                                }
                                else
                                {
                                    printf("%s\n", buffer);
                                }
                                if (dup2(saved_stdout_echo, STDOUT_FILENO) < 0)
                                {
                                    perror("Unable to duplicate file descriptor.");
                                }
                                close(fd);
                                close(saved_stdout_echo);
                                close(fd_read);
                            }
                        }
                        else if (flag_io == 1 && flag_o == 0)
                        {
                            fd = open(redirect_filename[2], O_RDWR | O_CREAT | O_APPEND, 0644);
                            if (fd < 0)
                            {
                                perror("file : ");
                            }
                            else
                            {
                                if (dup2(fd, STDOUT_FILENO) < 0)
                                {
                                    perror("Unable to duplicate file descriptor");
                                }
                                else
                                {
                                    printf("%s\n", buffer);
                                }
                                if (dup2(saved_stdout_echo, STDOUT_FILENO) < 0)
                                {
                                    perror("Unable to duplicate file descriptor.");
                                }
                                close(fd);
                                close(saved_stdout_echo);
                                close(fd_read);
                            }
                        }
                    }
                }
                else if (flag_o == 0 && flag_i == 0 && flag_io == 0)
                {
                    for (int i = 1; i < no_of_arg; i++)
                    {
                        printf("%s ", argument[i]);
                    }
                    printf("\n");
                }
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
                if (flag_i == 1)
                {
                    int fd = open(redirect_filename[0], O_RDWR);
                    if (fd < 0)
                    {
                        perror("file : ");
                    }
                    else
                    {
                        char buffer[1024] = "";
                        int chars = read(fd, buffer, 1024);
                        if (strcmp(buffer, "~") == 0 || strncmp(buffer, "~", 1) == 0)
                        {
                            char addr[2048] = "";
                            strcpy(addr, home);
                            for (int i = 1; i < chars; i++)
                            {
                                addr[strlen(home) + i - 1] = buffer[i];
                            }
                            int cderror = chdir(addr);
                            if (cderror != 0)
                            {
                                perror("cd command : ");
                            }
                        }
                        else
                        {
                            int cderror = chdir(buffer);
                            if (cderror != 0)
                            {
                                perror("cd command : ");
                            }
                        }
                    }
                    close(fd);
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