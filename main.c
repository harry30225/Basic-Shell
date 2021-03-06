#include "prompt.h"
#include "ls.h"
#include "headers.h"
#include "systemcommand.h"
#include "main.h"
#include "takeinput.h"
#include "generalcommand.h"
#include "pinfo.h"
#include "io.h"
#include "signalhandler.h"

int backgroundpid[512];
int flaghome = 0;
int backgroundprocess = 0;
char home[1024];
int input_count = 0;
int saved_stdout;
int saved_stdin;
char background_process[512][512];
int flagrun = 1;

// shell starts
int main()
{
    printf("\033[1;36m");
    printf("                                       ************************* Welcome to Cr4ck 5h3ll ********************************\n");
    printf("\033[0m");
    if (flaghome == 0)
    {
        getcwd(home, 1024);
        flaghome = 1;
    }
    saved_stdout = dup(STDOUT_FILENO);
    saved_stdin = dup(STDIN_FILENO);
    for (int i = 0; i < 512; i++)
    {
        backgroundpid[i] = 0;
    }
    signal(SIGINT, signalc);
    signal(SIGTSTP, signalz);
    // int flag = 0;
    while (flagrun)
    {
        //ctrlz and ctrlc signals
        signal(SIGINT, signalc);
        // initaiting prompt
        char cwd[1024];
        getcwd(cwd, 1024);
        dup2(saved_stdout, STDOUT_FILENO);
        dup2(saved_stdin, STDIN_FILENO);
        prompt(cwd);

        // TAKE INPUT HERE
        takeinput();

        // Background Process Completion
        for (int i = 0; i < backgroundprocess; i++)
        {
            char command[1024] = "";
            strcat(command, "/proc/");

            if (backgroundpid[i] != 0)
            {
                int k = backgroundpid[i];
                int count = 0;
                char str1[256], str2[256];
                for (int i = 0; i < 256; i++)
                {
                    str1[i] = '\0';
                    str2[i] = '\0';
                }
                while (k > 0)
                {
                    str1[count] = k % 10 + '0';
                    k = k / 10;
                    count++;
                }
                int index = 0;
                while (index < count)
                {
                    str2[index] = str1[count - 1 - index];
                    index++;
                }
                strcat(command, str2);
                strcat(command, "/stat");
                int fd1 = open(command, O_RDONLY);
                //  printf("%d\n", fd1);
                if (fd1 == -1)
                {
                    // printf("WTFF\n");
                    printf(" %s Background Process with PID : %s is exited successfully\n", background_process[i], str2);
                    backgroundpid[i] = 0;
                    strcpy(background_process[i], "\0");
                }
                else
                {
                    char a[1024] = "";
                    char divs[128][128];
                    for (int ind = 0; ind < 128; ind++)
                    {
                        for (int indi = 0; indi < 128; indi++)
                        {
                            divs[ind][indi] = '\0';
                        }
                    }
                    int charread = read(fd1, a, 1024);
                    index = 0;
                    for (int ind = 0; ind < charread; ind++)
                    {
                        // printf("ind = %d\n", ind);
                        int k = 0;
                        while (a[ind] != ' ')
                        {
                            divs[index][k] = a[ind];
                            ind++;
                            k++;
                            //  printf("ind = %d\n", ind);
                            if (ind >= charread)
                            {
                                break;
                            }
                        }
                        if (k != 0)
                        {
                            index++;
                        }
                    }
                    //printf("%s\n", divs[2]);
                    if (strcmp(divs[2], "Z") == 0)
                    {
                        // printf("Wtff\n");
                        printf(" %s Background Process with PID : %s is exited successfully\n", background_process[i], str2);
                        backgroundpid[i] = 0;
                        strcpy(background_process[i], "\0");
                    }
                    close(fd1);
                }
            }
        }
    }
    return 0;
}
