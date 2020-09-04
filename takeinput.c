#include "headers.h"
#include "ls.h"
#include "main.h"
#include "prompt.h"
#include "generalcommand.h"
#include "systemcommand.h"
#include "pinfo.h"

void takeinput()
{
    char buffer[100000];
    char *b = buffer;
    size_t bufsize = 100000;
    int characters = getline(&b, &bufsize, stdin);
    //Tokenize extra spaces and tabs
    char *a = strtok(buffer, ";");
    while (a != NULL)
    {
        if (strlen(a) > 0)
        {
            char **arguments = (char **)malloc(1024 * sizeof(char *));
            int j = 0;
            arguments[j] = (char *)malloc(1024 * sizeof(char));
            for (int i = 0; i < strlen(a) - 1; i++)
            {
                int k = 0;
                while (a[i] != ' ')
                {
                    arguments[j][k] = a[i];
                    i++;
                    k++;
                    if (i >= strlen(a) - 1)
                    {
                        break;
                    }
                }
                if (k != 0)
                {
                    j++;
                    arguments[j] = (char *)malloc(1024 * sizeof(char));
                }
            }
            arguments[j] = NULL;
            // for (int i = 0; i < j; i++)
            // {
            //     printf("%s ", arguments[i]);
            // }
            if (j > 0)
            {
                generalcommand(arguments, j);
            }
            free(arguments);
        }
        a = strtok(NULL, ";");
    }
}