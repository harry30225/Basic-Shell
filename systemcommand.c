#include "headers.h"
#include "prompt.h"
#include "systemcommand.h"
#include "main.h"
#include "pinfo.h"
#include "history.h"
#include "jobs.h"
#include "signalhandler.h"

int ongoing_process = 0;
void systemcommand(char **argument, int no_of_arg)
{
    int background = 0;
    if (strcmp(argument[no_of_arg - 1], "&") == 0)
    {
        background = 1;
    }
    int pid = fork();
    if (pid < 0)
    {
        perror("fork: ");
    }
    else if (pid == 0)
    {

        if (background == 1)
        {

            setpgid(0, 0);

            close(STDERR_FILENO);
            //close(STDOUT_FILENO);
            // close(STDIN_FILENO);
            argument[no_of_arg - 1] = 0;
        }
        //ctrlz and ctrlc
        //  signal(SIGINT, SIG_DFL);
        //  signal(SIGTSTP, SIG_DFL);

        // printf("1\n");
        // int t = execvp(argument[0], argument);
        // printf("11\n");
        if (strcmp(argument[0], "history") == 0)
        {
            history(no_of_arg - 1, argument);
        }
        else if (strcmp(argument[0], "pinfo") == 0)
        {
            pinfo(argument, no_of_arg - 1);
        }
        else if (strcmp(argument[0], "jobs") == 0)
        {
            jobs(argument, no_of_arg - 1);
        }
        else
        {
            if (execvp(argument[0], argument) == -1)
            {
                perror("Execute : ");
            }
        }
        exit(1);
    }
    else
    {
        if (background == 0)
        {
            ongoing_process = pid;
            int status;
            waitpid(pid, &status, WUNTRACED);
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
}