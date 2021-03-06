#include "ls.h"
#include "prompt.h"
#include "headers.h"
#include "systemcommand.h"
#include "takeinput.h"
#include "generalcommand.h"
#include "main.h"

// ls command function
void ls(char **argument, int no_of_arg, char home[1024])
{
    if (no_of_arg == 1)
    {
        struct dirent *de;
        DIR *dr = opendir(".");

        if (dr == NULL) // opendir returns NULL if couldn't open directory
        {
            perror("directory: ");
        }
        else
        {

            // for readdir()
            while ((de = readdir(dr)) != NULL)
            {
                if (*de->d_name != '.')
                    printf("%s", de->d_name);
                printf("   ");
            }
            printf("\n");
            closedir(dr);
        }
    }
    else if (no_of_arg == 2)
    {
        if (strcmp(argument[1], ".") == 0)
        {
            struct dirent *de;
            DIR *dr = opendir(".");

            if (dr == NULL) // opendir returns NULL if couldn't open directory
            {
                perror("directory: ");
            }
            else
            {

                // for readdir()
                while ((de = readdir(dr)) != NULL)
                {
                    if (*de->d_name != '.')
                        printf("%s", de->d_name);
                    printf("   ");
                }
                printf("\n");
                closedir(dr);
            }
        }
        else if (strcmp(argument[1], "..") == 0)
        {
            struct dirent *de;
            DIR *dr = opendir("..");

            if (dr == NULL) // opendir returns NULL if couldn't open directory
            {
                perror("directory: ");
            }
            else
            {

                // for readdir()
                while ((de = readdir(dr)) != NULL)
                {
                    if (*de->d_name != '.')
                        printf("%s", de->d_name);
                    printf("    ");
                }
                printf("\n");
                closedir(dr);
            }
        }
        else if (strcmp(argument[1], "~") == 0)
        {
            struct dirent *de;
            DIR *dr = opendir(home);

            if (dr == NULL) // opendir returns NULL if couldn't open directory
            {
                perror("directory: ");
            }
            // for readdir()
            while ((de = readdir(dr)) != NULL)
            {
                if (*de->d_name != '.')
                    printf("%s    ", de->d_name);
            }
            printf("\n");
            closedir(dr);
        }
        else if (strcmp(argument[1], "-a") == 0 || strcmp(argument[1], "-A") == 0)
        {
            struct dirent *de;
            DIR *dr = opendir(".");

            if (dr == NULL) // opendir returns NULL if couldn't open directory
            {
                perror("directory: ");
            }
            // for readdir()
            else
            {

                while ((de = readdir(dr)) != NULL)
                {
                    printf("%s    ", de->d_name);
                }
                printf("\n");
                closedir(dr);
            }
        }
        else if (strcmp(argument[1], "-l") == 0)
        {
            struct dirent *de;
            struct dirent *dee;
            DIR *dr = opendir(".");
            DIR *drr = opendir(".");
            if (dr == NULL || drr == NULL) // opendir returns NULL if couldn't open directory
            {
                perror("directory: ");
            }
            else
            {
                long int total = 0;
                while ((dee = readdir(drr)) != NULL)
                {
                    if (*dee->d_name != '.')
                    {
                        struct stat sfile;
                        if (stat(dee->d_name, &sfile) == -1)
                        {
                            perror("file : ");
                        }
                        else
                        {
                            total += sfile.st_blocks;
                        }
                    }
                }
                printf("total : %ld\n", total / 2);
                closedir(drr);
                // for readdir()
                while ((de = readdir(dr)) != NULL)
                {
                    if (*de->d_name != '.')
                    {
                        struct stat sfile;
                        struct tm dt;
                        if (stat(de->d_name, &sfile) == -1)
                        {
                            perror("file : ");
                        }
                        else
                        {
                            printf((sfile.st_mode & S_IRUSR) ? "r" : "-");
                            printf((sfile.st_mode & S_IWUSR) ? "w" : "-");
                            printf((sfile.st_mode & S_IXUSR) ? "x" : "-");
                            printf("   ");
                            printf((sfile.st_mode & S_IRGRP) ? "r" : "-");
                            printf((sfile.st_mode & S_IWGRP) ? "w" : "-");
                            printf((sfile.st_mode & S_IXGRP) ? "x" : "-");
                            printf("   ");
                            printf((sfile.st_mode & S_IROTH) ? "r" : "-");
                            printf((sfile.st_mode & S_IWOTH) ? "w" : "-");
                            printf((sfile.st_mode & S_IXOTH) ? "x" : "-");
                            printf("   ");
                            printf("%ld   ", sfile.st_nlink);
                            printf("File size: %ld", sfile.st_size);
                            int fsize = sfile.st_size;
                            int count = 0;
                            while (fsize > 0)
                            {
                                count++;
                                fsize = fsize / 10;
                            }
                            for (int i = 0; i < 15 - count; i++)
                            {
                                printf(" ");
                            }
                            struct passwd *pw = getpwuid(sfile.st_uid);
                            struct group *gr = getgrgid(sfile.st_gid);
                            if (pw != NULL)
                            {
                                printf("%s  ", pw->pw_name);
                            }
                            if (gr != NULL)
                            {
                                printf("%s   ", gr->gr_name);
                            }

                            dt = *(gmtime(&sfile.st_ctime));
                            printf("Created on: %02d-%02d-%02d %02d:%02d:%02d    ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                                   dt.tm_hour, dt.tm_min, dt.tm_sec);

                            dt = *(gmtime(&sfile.st_mtime));
                            printf("Modified on: %02d-%02d-%02d %02d:%02d:%02d    ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                                   dt.tm_hour, dt.tm_min, dt.tm_sec);
                            printf("%s\n", de->d_name);
                        }
                    }
                }
                closedir(dr);
            }
        }
        else if (strcmp(argument[1], "-la") == 0 || strcmp(argument[1], "-al") == 0 || strcmp(argument[1], "-lA") == 0 || strcmp(argument[1], "-Al") == 0)
        {
            struct dirent *de;
            struct dirent *dee;
            DIR *dr = opendir(".");
            DIR *drr = opendir(".");

            if (dr == NULL || drr == NULL) // opendir returns NULL if couldn't open directory
            {
                perror("directory: ");
            }
            else
            {
                long int total = 0;
                while ((dee = readdir(drr)) != NULL)
                {
                    struct stat sfile;
                    if (stat(dee->d_name, &sfile) == -1)
                    {
                        perror("file : ");
                    }
                    else
                    {
                        total += sfile.st_blocks;
                    }
                }
                printf("total : %ld\n", total / 2);
                closedir(drr);

                // for readdir()
                while ((de = readdir(dr)) != NULL)
                {

                    struct stat sfile;
                    struct tm dt;
                    if (stat(de->d_name, &sfile) == -1)
                    {
                        perror("file : ");
                    }
                    else
                    {
                        printf((sfile.st_mode & S_IRUSR) ? "r" : "-");
                        printf((sfile.st_mode & S_IWUSR) ? "w" : "-");
                        printf((sfile.st_mode & S_IXUSR) ? "x" : "-");
                        printf("   ");
                        printf((sfile.st_mode & S_IRGRP) ? "r" : "-");
                        printf((sfile.st_mode & S_IWGRP) ? "w" : "-");
                        printf((sfile.st_mode & S_IXGRP) ? "x" : "-");
                        printf("   ");
                        printf((sfile.st_mode & S_IROTH) ? "r" : "-");
                        printf((sfile.st_mode & S_IWOTH) ? "w" : "-");
                        printf((sfile.st_mode & S_IXOTH) ? "x" : "-");
                        printf("   ");
                        printf("%ld   ", sfile.st_nlink);
                        printf("File size: %ld", sfile.st_size);
                        int fsize = sfile.st_size;
                        int count = 0;
                        while (fsize > 0)
                        {
                            count++;
                            fsize = fsize / 10;
                        }
                        for (int i = 0; i < 15 - count; i++)
                        {
                            printf(" ");
                        }

                        struct passwd *pw = getpwuid(sfile.st_uid);
                        struct group *gr = getgrgid(sfile.st_gid);
                        if (pw != NULL)
                        {
                            printf("%s  ", pw->pw_name);
                        }
                        if (gr != NULL)
                        {
                            printf("%s   ", gr->gr_name);
                        }

                        dt = *(gmtime(&sfile.st_ctime));
                        printf("Created on: %02d-%02d-%02d %02d:%02d:%02d    ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                               dt.tm_hour, dt.tm_min, dt.tm_sec);

                        dt = *(gmtime(&sfile.st_mtime));
                        printf("Modified on: %02d-%02d-%02d %02d:%02d:%02d    ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                               dt.tm_hour, dt.tm_min, dt.tm_sec);
                        printf("%s\n", de->d_name);
                    }
                }
                closedir(dr);
            }
        }
        else
        {
            struct dirent *de;
            DIR *dr = opendir(argument[1]);

            if (dr == NULL) // opendir returns NULL if couldn't open directory
            {
                perror("directory: ");
            }
            else
            {

                // for readdir()
                while ((de = readdir(dr)) != NULL)
                {
                    if (*de->d_name != '.')
                        printf("%s   ", de->d_name);
                }
                printf("\n");
                closedir(dr);
            }
        }
    }
    else
    {
        int flag_l = 0, flag_a = 0, flag_al = 0;
        for (int i = 1; i < no_of_arg; i++)
        {
            if (strcmp(argument[i], "-l") == 0)
            {
                flag_l = 1;
            }
            else if (strcmp(argument[i], "-a") == 0 || strcmp(argument[i], "-A") == 0)
            {
                flag_a = 1;
            }
            else if (strcmp(argument[i], "-la") == 0 || strcmp(argument[i], "-al") == 0 || strcmp(argument[i], "-lA") == 0 || strcmp(argument[i], "-Al") == 0)
            {
                flag_al = 1;
            }
        }
        //   printf("%d %d %d \n", flag_a, flag_l, flag_al);
        for (int i = 1; i < no_of_arg; i++)
        {
            if (strcmp(argument[i], "-l") != 0 && strcmp(argument[i], "-a") != 0 && strcmp(argument[i], "-A") != 0 && strcmp(argument[i], "-la") != 0 && strcmp(argument[i], "-al") != 0 && strcmp(argument[i], "-lA") != 0 && strcmp(argument[i], "-Al") != 0)
            {
                if (flag_a == 1 && flag_l == 0 && flag_al == 0)
                {
                    printf("%s : \n", argument[i]);
                    struct dirent *de;
                    DIR *dr;
                    if (strcmp(argument[i], "~") == 0)
                    {
                        dr = opendir(home);
                    }
                    else
                    {
                        dr = opendir(argument[i]);
                    }

                    if (dr == NULL) // opendir returns NULL if couldn't open directory
                    {
                        perror("directory: ");
                    }
                    else
                    {

                        // for readdir()
                        while ((de = readdir(dr)) != NULL)
                        {
                            printf("%s   ", de->d_name);
                        }
                        printf("\n\n");
                        closedir(dr);
                    }
                }
                else if (flag_l == 1 && flag_a == 0 && flag_al == 0)
                {
                    printf("%s : \n", argument[i]);
                    struct dirent *de;
                    struct dirent *dee;
                    DIR *dr;
                    DIR *drr;
                    int flagh = 0;
                    if (strcmp(argument[i], "~") == 0)
                    {
                        flagh = 1;
                        dr = opendir(home);
                        drr = opendir(home);
                    }
                    else
                    {
                        dr = opendir(argument[i]);
                        drr = opendir(argument[i]);
                    }

                    if (dr == NULL || drr == NULL) // opendir returns NULL if couldn't open directory
                    {
                        perror("directory: ");
                    }
                    else
                    {
                        long int total = 0;
                        while ((dee = readdir(drr)) != NULL)
                        {
                            if (*dee->d_name != '.')
                            {
                                struct stat sfile;
                                char pathoffile2[2048] = "";
                                if (strcmp(argument[i], "~") != 0)
                                {
                                    strcat(pathoffile2, argument[i]);
                                    strcat(pathoffile2, "/");
                                    strcat(pathoffile2, dee->d_name);
                                }
                                else
                                {
                                    strcat(pathoffile2, dee->d_name);
                                }
                                if (stat(pathoffile2, &sfile) == -1)
                                {
                                    perror("file : ");
                                }
                                else
                                {
                                    total += sfile.st_blocks;
                                }
                            }
                        }
                        printf("total : %ld\n", total / 2);
                        closedir(drr);

                        // for readdir()
                        while ((de = readdir(dr)) != NULL)
                        {
                            if (*de->d_name != '.')
                            {
                                struct stat sfile;
                                struct tm dt;
                                char pathoffile[2048] = "";
                                if (strcmp(argument[i], "~") != 0)
                                {
                                    strcat(pathoffile, argument[i]);
                                    strcat(pathoffile, "/");
                                    strcat(pathoffile, de->d_name);
                                }
                                else
                                {
                                    strcat(pathoffile, de->d_name);
                                }
                                int t;
                                t = stat(pathoffile, &sfile);

                                if (t == -1)
                                {
                                    perror("file : ");
                                }
                                else
                                {
                                    printf((sfile.st_mode & S_IRUSR) ? "r" : "-");
                                    printf((sfile.st_mode & S_IWUSR) ? "w" : "-");
                                    printf((sfile.st_mode & S_IXUSR) ? "x" : "-");
                                    printf("   ");
                                    printf((sfile.st_mode & S_IRGRP) ? "r" : "-");
                                    printf((sfile.st_mode & S_IWGRP) ? "w" : "-");
                                    printf((sfile.st_mode & S_IXGRP) ? "x" : "-");
                                    printf("   ");
                                    printf((sfile.st_mode & S_IROTH) ? "r" : "-");
                                    printf((sfile.st_mode & S_IWOTH) ? "w" : "-");
                                    printf((sfile.st_mode & S_IXOTH) ? "x" : "-");
                                    printf("   ");
                                    printf("%ld   ", sfile.st_nlink);
                                    printf("File size: %ld", sfile.st_size);
                                    int fsize = sfile.st_size;
                                    int count = 0;
                                    while (fsize > 0)
                                    {
                                        count++;
                                        fsize = fsize / 10;
                                    }
                                    for (int i = 0; i < 15 - count; i++)
                                    {
                                        printf(" ");
                                    }

                                    struct passwd *pw = getpwuid(sfile.st_uid);
                                    struct group *gr = getgrgid(sfile.st_gid);
                                    if (pw != NULL)
                                    {
                                        printf("%s  ", pw->pw_name);
                                    }
                                    if (gr != NULL)
                                    {
                                        printf("%s   ", gr->gr_name);
                                    }

                                    dt = *(gmtime(&sfile.st_ctime));
                                    printf("Created on: %02d-%02d-%02d %02d:%02d:%02d    ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                                           dt.tm_hour, dt.tm_min, dt.tm_sec);

                                    dt = *(gmtime(&sfile.st_mtime));
                                    printf("Modified on: %02d-%02d-%02d %02d:%02d:%02d    ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                                           dt.tm_hour, dt.tm_min, dt.tm_sec);
                                    printf("%s\n", de->d_name);
                                }
                            }
                        }
                        printf("\n\n");
                        closedir(dr);
                    }
                }
                else if (flag_l == 0 && flag_a == 0 && flag_al == 0)
                {
                    printf("%s : \n", argument[i]);
                    struct dirent *de;
                    DIR *dr;
                    if (strcmp(argument[i], "~") == 0)
                    {
                        dr = opendir(home);
                    }
                    else
                    {
                        dr = opendir(argument[i]);
                    }

                    if (dr == NULL) // opendir returns NULL if couldn't open directory
                    {
                        perror("directory: ");
                    }
                    else
                    {

                        // for readdir()
                        while ((de = readdir(dr)) != NULL)
                        {
                            if (*de->d_name != '.')
                                printf("%s   ", de->d_name);
                        }
                        printf("\n\n");
                        closedir(dr);
                    }
                }
                else
                {
                    printf("%s : \n", argument[i]);
                    struct dirent *de;
                    struct dirent *dee;
                    DIR *dr;
                    DIR *drr;
                    int flagh = 0;
                    if (strcmp(argument[i], "~") == 0)
                    {
                        flagh = 1;
                        dr = opendir(home);
                        drr = opendir(home);
                    }
                    else
                    {
                        dr = opendir(argument[i]);
                        drr = opendir(argument[i]);
                    }

                    if (dr == NULL || drr == NULL) // opendir returns NULL if couldn't open directory
                    {
                        perror("directory: ");
                    }
                    else
                    {
                        long int total = 0;
                        while ((dee = readdir(drr)) != NULL)
                        {

                            struct stat sfile;
                            char pathoffile2[2048] = "";
                            if (strcmp(argument[i], "~") != 0)
                            {
                                strcat(pathoffile2, argument[i]);
                                strcat(pathoffile2, "/");
                                strcat(pathoffile2, dee->d_name);
                            }
                            else
                            {
                                strcat(pathoffile2, dee->d_name);
                            }

                            if (stat(pathoffile2, &sfile) == -1)
                            {
                                perror("file : ");
                            }
                            else
                            {
                                total += sfile.st_blocks;
                            }
                        }
                        printf("total : %ld\n", total / 2);
                        closedir(drr);

                        // for readdir()
                        while ((de = readdir(dr)) != NULL)
                        {
                            struct stat sfile;
                            struct tm dt;
                            int t;
                            char pathoffile[2048] = "";
                            if (strcmp(argument[i], "~") != 0)
                            {
                                strcat(pathoffile, argument[i]);
                                strcat(pathoffile, "/");
                                strcat(pathoffile, de->d_name);
                            }
                            else
                            {
                                strcat(pathoffile, de->d_name);
                            }
                            t = stat(pathoffile, &sfile);
                            if (t == -1)
                            {
                                perror("file : ");
                            }
                            else
                            {
                                printf((sfile.st_mode & S_IRUSR) ? "r" : "-");
                                printf((sfile.st_mode & S_IWUSR) ? "w" : "-");
                                printf((sfile.st_mode & S_IXUSR) ? "x" : "-");
                                printf("   ");
                                printf((sfile.st_mode & S_IRGRP) ? "r" : "-");
                                printf((sfile.st_mode & S_IWGRP) ? "w" : "-");
                                printf((sfile.st_mode & S_IXGRP) ? "x" : "-");
                                printf("   ");
                                printf((sfile.st_mode & S_IROTH) ? "r" : "-");
                                printf((sfile.st_mode & S_IWOTH) ? "w" : "-");
                                printf((sfile.st_mode & S_IXOTH) ? "x" : "-");
                                printf("   ");
                                printf("%ld   ", sfile.st_nlink);
                                printf("File size: %ld", sfile.st_size);
                                int fsize = sfile.st_size;
                                int count = 0;
                                while (fsize > 0)
                                {
                                    count++;
                                    fsize = fsize / 10;
                                }
                                for (int i = 0; i < 15 - count; i++)
                                {
                                    printf(" ");
                                }

                                struct passwd *pw = getpwuid(sfile.st_uid);
                                struct group *gr = getgrgid(sfile.st_gid);
                                if (pw != NULL)
                                {
                                    printf("%s  ", pw->pw_name);
                                }
                                if (gr != NULL)
                                {
                                    printf("%s   ", gr->gr_name);
                                }

                                dt = *(gmtime(&sfile.st_ctime));
                                printf("Created on: %02d-%02d-%02d %02d:%02d:%02d    ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                                       dt.tm_hour, dt.tm_min, dt.tm_sec);

                                dt = *(gmtime(&sfile.st_mtime));
                                printf("Modified on: %02d-%02d-%02d %02d:%02d:%02d    ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                                       dt.tm_hour, dt.tm_min, dt.tm_sec);
                                printf("%s\n", de->d_name);
                            }
                        }
                        // printf("\n\n");
                        closedir(dr);
                    }
                }
            }
            else if (flag_l == 1 && flag_a == 1 && flag_al == 0 && no_of_arg == 3)
            {

                struct dirent *de;
                struct dirent *dee;
                DIR *dr = opendir(".");
                DIR *drr = opendir(".");

                if (dr == NULL || drr == NULL) // opendir returns NULL if couldn't open directory
                {
                    perror("directory: ");
                }
                else
                {
                    long int total = 0;
                    while ((dee = readdir(drr)) != NULL)
                    {
                        struct stat sfile;
                        if (stat(dee->d_name, &sfile) == -1)
                        {
                            perror("file : ");
                        }
                        else
                        {
                            total += sfile.st_blocks;
                        }
                    }
                    printf("total : %ld\n", total / 2);
                    closedir(drr);

                    // for readdir()
                    while ((de = readdir(dr)) != NULL)
                    {
                        struct stat sfile;
                        struct tm dt;
                        if (stat(de->d_name, &sfile) == -1)
                        {
                            perror("file : ");
                        }
                        else
                        {
                            printf((sfile.st_mode & S_IRUSR) ? "r" : "-");
                            printf((sfile.st_mode & S_IWUSR) ? "w" : "-");
                            printf((sfile.st_mode & S_IXUSR) ? "x" : "-");
                            printf("   ");
                            printf((sfile.st_mode & S_IRGRP) ? "r" : "-");
                            printf((sfile.st_mode & S_IWGRP) ? "w" : "-");
                            printf((sfile.st_mode & S_IXGRP) ? "x" : "-");
                            printf("   ");
                            printf((sfile.st_mode & S_IROTH) ? "r" : "-");
                            printf((sfile.st_mode & S_IWOTH) ? "w" : "-");
                            printf((sfile.st_mode & S_IXOTH) ? "x" : "-");
                            printf("   ");
                            printf("%ld   ", sfile.st_nlink);
                            printf("File size: %ld", sfile.st_size);
                            int fsize = sfile.st_size;
                            int count = 0;
                            while (fsize > 0)
                            {
                                count++;
                                fsize = fsize / 10;
                            }
                            for (int i = 0; i < 15 - count; i++)
                            {
                                printf(" ");
                            }

                            struct passwd *pw = getpwuid(sfile.st_uid);
                            struct group *gr = getgrgid(sfile.st_gid);
                            if (pw != NULL)
                            {
                                printf("%s  ", pw->pw_name);
                            }
                            if (gr != NULL)
                            {
                                printf("%s   ", gr->gr_name);
                            }

                            dt = *(gmtime(&sfile.st_ctime));
                            printf("Created on: %02d-%02d-%02d %02d:%02d:%02d    ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                                   dt.tm_hour, dt.tm_min, dt.tm_sec);

                            dt = *(gmtime(&sfile.st_mtime));
                            printf("Modified on: %02d-%02d-%02d %02d:%02d:%02d    ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                                   dt.tm_hour, dt.tm_min, dt.tm_sec);
                            printf("%s\n", de->d_name);
                        }
                    }
                    //  printf("\n\n");
                    closedir(dr);
                    break;
                }
            }
        }
    }
}