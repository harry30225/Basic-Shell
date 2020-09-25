#include "headers.h"
#include "prompt.h"
#include "systemcommand.h"
#include "main.h"
#include "pinfo.h"

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
        // printf("1\n");
        int t = execvp(argument[0], argument);
        // printf("11\n");
        if (t == -1)
        {
            perror("Execute : ");
        }
        exit(1);
    }
    else
    {
        if (background == 0)
        {
            int status;
            waitpid(pid, &status, WUNTRACED);
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