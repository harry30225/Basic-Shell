#include "prompt.h"
#include "headers.h"

// pwd command function
void pwdd()
{
    char currentdir[1024];
    getcwd(currentdir, 1024);
    printf("%s\n", currentdir);
}

// cd command function
void cd(char *str)
{
    int cderror = chdir(str);
    if (cderror != 0)
    {
        perror("cd command : ");
    }
}

// shell starts
int main()
{
    while (1)
    {
        char cwd[1024];
        getcwd(cwd, 1024);
        prompt(cwd);
        // TAKE INPUT HERE
        char buffer[100000];
        char *b = buffer;
        size_t bufsize = 100000;
        int characters = getline(&b, &bufsize, stdin);
        //Tokenize extra spaces and tabs
        char arguments[1024][1024];
        for (int i = 0; i < 1024; i++)
        {
            for (int k = 0; k < 1024; k++)
            {
                arguments[i][k] = '\0';
            }
        }
        int j = 0;
        for (int i = 0; i < characters - 1; i++)
        {
            int k = 0;
            while (buffer[i] != ' ')
            {
                arguments[j][k] = buffer[i];
                i++;
                k++;
                if (i >= characters - 1)
                {
                    break;
                }
            }
            if (k != 0)
            {
                j++;
            }
        }
        // pwd command
        if (strcmp(arguments[0], "pwd") == 0)
        {
            pwdd();
        }
        // echo command
        else if (strcmp(arguments[0], "echo") == 0)
        {
            for (int i = 1; i < j; i++)
            {
                printf("%s ", arguments[i]);
            }
            printf("\n");
        }
        // cd command
        else if (strcmp(arguments[0], "cd") == 0)
        {
            cd(arguments[1]);
        }
    }
}
