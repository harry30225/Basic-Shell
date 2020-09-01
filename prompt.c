#include "prompt.h"
#include "headers.h"

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
            int fd1 = open("makefile", O_RDONLY);
            if (fd1 == -1)
            {
                printf("< %s@%s : %s>", pw->pw_name, host, cwd);
            }
            else
            {
                printf("< %s@%s : ~>", pw->pw_name, host);
            }
            close(fd1);
        }
    }
}
