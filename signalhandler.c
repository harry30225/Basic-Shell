#include "headers.h"
#include "main.h"
#include "takeinput.h"
#include "prompt.h"
#include "systemcommand.h"
#include "io.h"
#include "history.h"
#include "pinfo.h"
#include "signalhandler.h"

void signalc(int sig_no)
{
    int process_pid = ongoing_process;
    if (process_pid > 0)
    {
        //fprintf(stderr, "%d process_pid\n", process_pid);
        if (kill(process_pid, sig_no) < 0)
        {
            perror("signalc : ");
        }
        else
        {
            printf("\n");
            ongoing_process = 0;
            fflush(stdout);
        }
    }
    else
    {
        printf("\n");
        char cwd[1024] = "";
        getcwd(cwd, 1024);
        prompt(cwd);
        fflush(stdout);
    }
}
void signalz(int sig_no)
{
    int process_pid = ongoing_process;
    if (process_pid > 0)
    {
        // printf("%d process_pid", process_pid);
        if (kill(process_pid, sig_no) < 0)
        {
            perror("signalz : ");
        }
        else
        {
            int k = process_pid;
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
            char cmd[1024] = "";
            strcat(cmd, "/proc/");
            strcat(cmd, str2);
            strcat(cmd, "/stat");
            int fd1 = open(cmd, O_RDONLY);
            if (fd1 == -1)
            {
                printf("Process is ended\n");
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
                backgroundpid[backgroundprocess] = process_pid;
                strcpy(background_process[backgroundprocess], divs[1]);
                backgroundprocess++;
                close(fd1);
                printf("\n%d stopped\n", process_pid);
                ongoing_process = 0;
            }
        }
    }
    else
    {
        printf("\n");
        char cwd[1024] = "";
        getcwd(cwd, 1024);
        prompt(cwd);
        fflush(stdout);
    }
}