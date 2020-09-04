#include "prompt.h"
#include "headers.h"
#include "main.h"

void prompt(char *cwd)
{
    char host[1025];
    host[1024] = '\0';
    int hostname = gethostname(host, 1024);
    if (hostname == -1)
    {
        perror("hostname: ");
    }
    else
    {

        struct passwd *pw;
        pw = getpwuid(getuid());

        if (pw == NULL)
        {
            perror("passwd: ");
        }
        else
        {
            if (strcmp(cwd, home) != 0)
            {
                printf("< ");
                printf("\033[1;34m");
                printf("%s", pw->pw_name);
                printf("\033[0m");
                printf(" @ ");
                printf("\033[1;34m");
                printf("%s", host);
                printf("\033[0m");
                printf(" : ");
                // printf("< %s@%s : ", pw->pw_name, host);
                printf("\033[01;33m");
                printf("%s", cwd);
                printf("\033[0m");
                printf(">");
            }
            else
            {
                printf("< ");
                printf("\033[1;34m");
                printf("%s", pw->pw_name);
                printf("\033[0m");
                printf(" @ ");
                printf("\033[1;34m");
                printf("%s", host);
                printf("\033[0m");
                printf(" : ");
                printf("\033[01;33m");
                printf("~");
                printf("\033[0m");
                printf(">");
            }
        }
    }
}
