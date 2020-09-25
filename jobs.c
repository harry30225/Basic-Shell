#include "headers.h"
#include "main.h"
#include "prompt.h"
#include "generalcommand.h"

void jobs(char **argument, int no_of_arg)
{
    if (no_of_arg != 1)
    {
        printf("Invalid command set \n");
    }
    else
    {
        int j = 0;
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
                    perror("Unable to open jobs : ");
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
                    if (strcmp(divs[2], "R") == 0)
                    {
                        // printf("Wtff\n");
                        j++;
                        printf("[%d] Running %s  [%s] \n", j, divs[1], str2);
                    }
                    else if (strcmp(divs[2], "T") == 0 || strcmp(divs[2], "t") == 0)
                    {
                        // printf("Wtff\n");
                        j++;
                        printf("[%d] Stopped %s  [%s] \n", j, divs[1], str2);
                    }
                    close(fd1);
                }
            }
        }
    }
}

void kjob(char **argument, int no_of_arg)
{
    if (no_of_arg != 3)
    {
        printf("Invalid Command set\n");
    }
    else
    {
        int flag_on = -1;
        int number_1 = 0;
        int t = 1;
        for (int i = strlen(argument[1]) - 1; i >= 0; i--)
        {
            number_1 += (int)(argument[1][i] - '0') * t;
            t = t * 10;
        }
        int number_2 = 0;
        t = 1;
        for (int i = strlen(argument[2]) - 1; i >= 0; i--)
        {
            number_2 += (int)(argument[1][i] - '0') * t;
            t = t * 10;
        }
        int j = 0;
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
                    perror("Unable to open jobs : ");
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
                    if (strcmp(divs[2], "R") == 0)
                    {
                        // printf("Wtff\n");
                        j++;
                        if (j == number_1)
                        {
                            flag_on = backgroundpid[i];
                            break;
                        }
                        //  printf("[%d] Running %s  [%s] \n", j, divs[1], str2);
                    }
                    else if (strcmp(divs[2], "T") == 0 || strcmp(divs[2], "t") == 0)
                    {
                        // printf("Wtff\n");
                        j++;
                        if (j == number_1)
                        {
                            flag_on = backgroundpid[i];
                            break;
                        }
                        //  printf("[%d] Stopped %s  [%s] \n", j, divs[1], str2);
                    }
                    close(fd1);
                }
            }
        }
        if (flag_on == -1)
        {
            printf("Inavlid Job Number");
        }
        else
        {
            if ((kill(flag_on, number_2)))
            {
                perror("kjob : ");
            }
            else
            {
                backgroundpid[flag_on] = 0;
                strcpy(background_process[flag_on], "\0");
            }
        }
    }
}
void overkill(char **argument, int no_of_arg)
{
    if (no_of_arg != 1)
    {
        printf("Invalid Command set\n");
    }
    else
    {
        for (int i = 0; i < backgroundprocess; i++)
        {
            if (backgroundpid[i] != 0)
            {
                if (kill(backgroundpid[i], SIGKILL))
                {
                    printf("Kill does not work on process %s with pid %d \n", background_process[i], backgroundpid[i]);
                }
                else
                {
                    printf("Kill work on process %s with pid %d \n", background_process[i], backgroundpid[i]);
                    backgroundpid[i] = 0;
                    strcpy(background_process[i], "\0");
                }
            }
        }
    }
}