#include "headers.h"
#include "io.h"
#include "prompt.h"
#include "systemcommand.h"
#include "generalcommand.h"
#include "ls.h"
#include "pinfo.h"
#include "history.h"
#include "main.h"
#include "jobs.h"
#include "signalhandler.h"

void io(char **argument, int no_of_arg)
{
    int in_redirect = 0;
    int out_redirect = 0;
    int out_redirect_d = 0;
    int flag_out = 0, flag_out_d = 0;
    char **in = (char **)malloc(1024);
    char **out = (char **)malloc(1024);
    char **outd = (char **)malloc(1024);
    char **args = (char **)malloc(1024);
    int no_args = 0;
    // fprintf(stderr, "%d\n", no_of_arg);
    int background = 0;
    if (strcmp(argument[no_of_arg - 1], "&") == 0)
    {
        background = 1;
    }
    for (int i = 0; i < no_of_arg; i++)
    {
        // fprintf(stderr, "hihi\n");
        if (strcmp(argument[i], "<") != 0 && strcmp(argument[i], ">") != 0 && strcmp(argument[i], ">>") != 0 && strcmp(argument[i], "&") != 0)
        {
            args[no_args] = (char *)malloc(1024 * sizeof(char));
            strcpy(args[no_args], argument[i]);
            no_args++;
        }
        if (strcmp(argument[i], "<") == 0)
        {
            if (i + 1 < no_of_arg)
            {
                in[in_redirect] = (char *)malloc(1024 * sizeof(char));
                strcpy(in[in_redirect], argument[i + 1]);
                in_redirect++;
                i++;
            }
        }
        else if (strcmp(argument[i], ">") == 0)
        {
            if (i + 1 < no_of_arg)
            {
                out[out_redirect] = (char *)malloc(1024 * sizeof(char));
                strcpy(out[out_redirect], argument[i + 1]);
                out_redirect++;
                flag_out = out_redirect;
                i++;
            }
        }
        else if (strcmp(argument[i], ">>") == 0)
        {
            if (i + 1 < no_of_arg)
            {
                outd[out_redirect_d] = (char *)malloc(1024 * sizeof(char));
                strcpy(outd[out_redirect_d], argument[i + 1]);
                out_redirect_d++;
                flag_out_d = out_redirect_d;
                i++;
            }
        }
    }
    args[no_args] = (char *)malloc(1024 * sizeof(char));
    args[no_args] = 0;
    outd[out_redirect_d] = (char *)malloc(1024 * sizeof(char));
    outd[out_redirect_d] = 0;
    out[out_redirect] = (char *)malloc(1024 * sizeof(char));
    out[out_redirect] = 0;
    in[in_redirect] = (char *)malloc(1024 * sizeof(char));
    in[in_redirect] = 0;
    int pid = fork();

    if (pid < 0)
    {
        perror("process : ");
    }
    else if (pid == 0)
    {
        int fd_in, fd_out, fd_outd, valid_i = 0, valid_o = 0, valid_od = 0;

        if (in_redirect > 0)
        {
            if (strcmp(in[in_redirect - 1], "~") == 0 || strncmp(in[in_redirect - 1], "~", 1) == 0)
            {
                char addr[2048] = "";
                strcpy(addr, home);
                for (int i = 1; i < strlen(in[in_redirect - 1]); i++)
                {
                    addr[strlen(home) + i - 1] = in[in_redirect - 1][i];
                }
                fd_in = open(addr, O_RDONLY);
            }
            else
            {

                fd_in = open(in[in_redirect - 1], O_RDONLY);
                //  fprintf(stderr, "fd_in %d\n", fd_in);
            }
            if (fd_in < 0)
            {
                perror("Input file : ");
            }
            else
            {

                if (dup2(fd_in, STDIN_FILENO) < 0)
                {
                    perror("Unable to access file descriptor : ");
                }
                else
                {
                    valid_i = 1;
                }
            }
            close(fd_in);
        }
        if (out_redirect > 0 || out_redirect_d > 0)
        {
            if (out_redirect > 0 && flag_out > flag_out_d)
            {
                if (strcmp(out[out_redirect - 1], "~") == 0 || strncmp(out[out_redirect - 1], "~", 1) == 0)
                {
                    char addr[2048] = "";
                    strcpy(addr, home);
                    for (int i = 1; i < strlen(out[out_redirect - 1]); i++)
                    {
                        addr[strlen(home) + i - 1] = out[out_redirect - 1][i];
                    }
                    fd_out = open(addr, O_RDWR | O_CREAT | O_TRUNC, 0644);
                }
                else
                {
                    fd_out = open(out[out_redirect - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
                }
                if (fd_out < 0)
                {
                    perror("Output file : ");
                }
                else
                {
                    if (dup2(fd_out, STDOUT_FILENO) < 0)
                    {
                        perror("Unable to open file descriptor : ");
                    }
                    else
                    {
                        valid_o = 1;
                    }

                    close(fd_out);
                }
            }
            else if (out_redirect_d > 0 && flag_out < flag_out_d)
            {
                if (strcmp(outd[out_redirect_d - 1], "~") == 0 || strncmp(outd[out_redirect_d - 1], "~", 1) == 0)
                {
                    char addr[2048] = "";
                    strcpy(addr, home);
                    for (int i = 1; i < strlen(outd[out_redirect_d - 1]); i++)
                    {
                        addr[strlen(home) + i - 1] = outd[out_redirect_d - 1][i];
                    }
                    fd_outd = open(addr, O_RDWR | O_CREAT | O_APPEND, 0644);
                }
                else
                {
                    fd_outd = open(outd[out_redirect_d - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
                }
                if (fd_outd < 0)
                {
                    perror("Output file : ");
                }
                else
                {
                    if (dup2(fd_outd, STDOUT_FILENO) < 0)
                    {
                        perror("Unable to open file descriptor : ");
                    }
                    else
                    {
                        valid_od = 1;
                    }

                    close(fd_outd);
                }
            }
        }
        if ((in_redirect > 0 && valid_i == 1) || (in_redirect <= 0))
        {
            if (background == 1)
            {
                setpgid(0, 0);

                close(STDERR_FILENO);
            }
            //   //ctrlc and ctrlz
            //   signal(SIGINT, SIG_DFL);
            //   signal(SIGTSTP, SIG_DFL);

            if (strcmp(args[0], "history") == 0)
            {
                history(no_args, args);
            }
            else if (strcmp(args[0], "pinfo") == 0)
            {
                pinfo(args, no_args);
            }
            else if (strcmp(args[0], "jobs") == 0)
            {
                jobs(args, no_args);
            }
            else
            {
                if (execvp(args[0], args) < 0)
                {
                    perror("Execute : ");
                    exit(0);
                }
            }
            exit(1);
        }
    }
    else
    {
        if (background == 0)
        {
            ongoing_process = pid;
            waitpid(pid, NULL, 0);
            ongoing_process = 0;
        }
        else
        {
            printf("%d\n", pid);
            //signal(SIGCHLD, SIG_IGN);
            backgroundpid[backgroundprocess] = pid;
            strcpy(background_process[backgroundprocess], argument[0]);
            backgroundprocess++;
        }
    }
    free(in);
    free(out);
    free(outd);
    free(args);
}