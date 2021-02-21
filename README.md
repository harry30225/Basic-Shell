# Cr4ck 5h3ll

# Basic Shell Using C

## Requirements
* Shell Intro
   1. The Shell is initiated from main.c .  
   1. All the headers are included in headers.h .  
   1. prompt.c is called from main.c , it shows the prompt which has username and hostname along with current working directory.
   1. takeinput.c is used to take command input and handle spaces and ; separated commands.
   1. From here the generalcommand.h fill is called and it takes care of all the commands.
   1. An extra main.h file is also made for home directory address, backgroundpid info and no of background pids.
* General User Defined Commands
   1. pwd , echo , cd commands are implemented in generalcommand.c itself.
* ls    
   1. ls command and all its flags are implemented in ls.c file.
   1. It supports flags of ls like ls ~, ls .. , ls -a, ls -l ,ls -la, ls <directory_name> etc.
* pinfo    
   1. pinfo is implemented using /proc/pid/stat it is read and required information is extracted.
   1. pinfo tells the information like process status, memory, executable path and name of process.
* Foreground and Background Process   
   1. In file named systemcommand.c background processes and foreground processes of system commands are taken care of.
   1. The commmands ending with a & are referred to as background process.
* History   
   1. For history command first the input taken in takeinput.c is written in a file using write() system call and it is taken care that no more than 20 commands are stored at a time and history.c reads history.txt and give suitable output. (BONUS)
* IO redirection and Piping
   1. IO redirection is implemented in io.c where commands like cat < file.txt , echo content > h.txt etc. which contains io redirection is dealt with.
   1. IO redirection is also implemented for background processes.
   1. Piping is implemented in piping.c where commands like cmd1 | cmd2  etc. are dealt with.
   1. Piping is also implemented with io redirection where both are used.
* User defined Commands
   1. setenv envvar value is used for creating environment variable.
   1. unsetenv envvar is used to delete existing environment variable.
   1. jobs displays current stopped and running background processes.
   1. kjob job_no. signal_no. , this command is used to give a particular job a signal using the particular signal number.
   1. fg job_no. , this brings the background process to foreground and changes its status from stopped to running.
   1. bg job_no. , this change the state of stopped background process to running.
   1. overkill , it kills all background processes.
   1. quit, it is used to quit the shell and CTRL + D could also be used for the same.
* Signal Handling
   1. Ctrl + z
      * It pushed any current running foreground process to background and change its status from running to stopped.
   1. Ctrl + c
      * It should interrupt any current running foreground process by sending the signal of SIGINT. The shell would not quit on clicking Ctrl + c.      

1. Makefile is used for execution of commands.

### Developed by :heart: and :coffee: by Harshit Sharma
