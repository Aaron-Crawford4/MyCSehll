#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <wait.h>
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators

void clear(char * args[]);
void dir(char * args[], int outp);
void cd(char * args[]);
void env(char * args[], char * envp[], int outp);
void echo(char * args[], int outp);
void pause_until_enter(char * args[]);
void help(char * args[]);
void other_commands(char * args[], int length, int outp, int inp, int background_exec);

/*void clear(char * args[]) {

    pid_t pid;

    switch (pid = fork()) {
        case -1:
            printf("failed to fork\n");
        case 0:
            pid = getpid();
            execvp(args[0], args);
            printf("failed to exec\n");
    }
    int returnStatus;
    waitpid(pid, &returnStatus, 0);

}

void dir(char * args[], int outp) {

    pid_t pid;
    char *a[50];
    int i = 0;
    while(i < outp) {
	a[i] = args[i];
	i++;
    }
    a[i] = NULL;
    switch (pid = fork()) {
        case -1:
	    printf("failed to fork\n");
        case 0:
	    if(outp != 0) {
		if(strcmp(args[outp], ">>") == 0) {
		    freopen(args[outp + 1], "a", stdout);
	            pid = getpid();
        	    execvp(args[0], a);
	    	    printf("failed to exec\n");
		}
		else {
		    freopen(args[outp + 1], "w", stdout);
                    pid = getpid();
                    execvp(args[0], a);
                    printf("failed to exec\n");
		}
	    }
	    else {
		pid = getpid();
                execvp(args[0], args);
                printf("failed to exec\n");
	    }
    }
    int returnStatus;
    waitpid(pid, &returnStatus, 0);

}
void cd(char * args[]) {

    char *curdir;
    size_t s = strlen(args[1]);
    if (s && (args[1][s-1] == '\n')) args[1][--s] = 0;
    if(args[1]) {
        if(opendir(args[1])) {
            curdir=(char *)malloc(100*sizeof(char));
            chdir(args[1]);
            getcwd(curdir,100);
            printf("%s \n",curdir);
        }
        else {
            printf("%s is not a valid directory\n", args[1]);
        }
    }
    else {
	chdir("~");
	getcwd(curdir,100);
        printf("%s \n",curdir);
    }
    setenv("PWD",curdir,1);
}

void env(char * args[], char * envp[], int outp) {


    pid_t pid;
    char *a[50];
    int i = 0;
    while(i < outp) {
        a[i] = args[i];
        i++;
    }
    a[i] = NULL;
    switch (pid = fork()) {
        case -1:
            printf("failed to fork\n");
        case 0:
            if(outp != 0) {
                if(strcmp(args[outp], ">>") == 0) {
                    freopen(args[outp + 1], "a", stdout);
                    pid = getpid();
                    execvp("env", a);
                    printf("failed to exec\n");
                }
                else {
                    freopen(args[outp + 1], "w", stdout);
                    pid = getpid();
                    execvp("env", a);
                    printf("failed to exec\n");
                }
            }
            else {
                pid = getpid();
                execvp("env", args);
                printf("failed to exec\n");
            }
    }
    int returnStatus;
    waitpid(pid, &returnStatus, 0);

}

void echo(char * args[], int outp) {

    pid_t pid;
    char *a[50];
    int i = 0;
    while(i < outp) {
        a[i] = args[i];
        i++;
    }
    a[i] = NULL;
    switch (pid = fork()) {
        case -1:
            printf("failed to fork\n");
        case 0:
            if(outp != 0) {
                if(strcmp(args[outp], ">>") == 0) {
                    freopen(args[outp + 1], "a", stdout);
                    pid = getpid();
                    execvp(args[0], a);
                    printf("failed to exec\n");
                }
                else {
                    freopen(args[outp + 1], "w", stdout);
                    pid = getpid();
                    execvp(args[0], a);
                    printf("failed to exec\n");
                }
            }
            else {
                pid = getpid();
                execvp(args[0], args);
                printf("failed to exec\n");
            }
    }

    int returnStatus;
    waitpid(pid, &returnStatus, 0);
}

void pause_until_enter(char * args[]) {

    printf("Press the enter key to continue\n");
    getchar();
}

void help(char * args[]) {

    char *a[4];
    a[0] = "more";
    a[1] = "-d";
    a[2] = "../manual/readme.md";
    a[3] = NULL;
    pid_t pid;
    switch (pid = fork()) {
        case -1:
            printf("failed to fork\n");
        case 0:
            pid = getpid();
            execvp("more", a);
            printf("failed to exec\n");
    }
    int returnStatus;
    waitpid(pid, &returnStatus, 0);

}


void other_commands(char * args[], int length, int outp, int inp, int background_exec) {

    pid_t pid;
    char *a[50];
    int i = 0;
    while(i <= length && strcmp(args[i], "<") != 0 && strcmp(args[i], ">") != 0 && strcmp(args[i], ">>") != 0 && strcmp(args[i], "&") != 0) {
	a[i] = args[i];
	i++;
    }
    a[i] = NULL;
    switch (pid = fork()) {
        case -1:
            printf("failed to fork\n");
        case 0:
            if(outp != 0 && inp == 0) {
                if(strcmp(args[outp], ">>") == 0) {
                    freopen(args[outp + 1], "a", stdout);
                    pid = getpid();
                    execvp(args[0], a);
                    printf("failed to exec\n");
                }
                else {
                    freopen(args[outp + 1], "w", stdout);
                    pid = getpid();
                    execvp(args[0], a);
                    printf("failed to exec\n");
                }
            }
	    else if(outp == 0 && inp != 0) {
		    freopen(args[inp + 1], "r", stdin);
		    pid = getpid();
		    execvp(args[0], a);
		    printf("failed to exec\n");
            }
	    else if(outp != 0 && inp != 0) {
		freopen(args[inp + 1], "r", stdin);
		if(strcmp(args[outp], ">>") == 0) {
                    freopen(args[outp + 1], "a", stdout);
		}
		else {
                    freopen(args[outp + 1], "w", stdout);
		}
		pid = getpid();
		execvp(args[0], a);
		printf("failed to exec\n");
	    }
            else {
                pid = getpid();
                execvp(args[0], a);
                printf("failed to exec\n");
            }
    }
    if(background_exec != 1) {
        int returnStatus;
        waitpid(pid, &returnStatus, 0);
    }
}
*/
int commands(char * args[], char * envp[], int length, int inp, int outp, int background_exec) {

    if (!strcmp(args[0],"clr")) { // "clear" command
        clear(args);
    }
    else if (!strcmp(args[0], "dir")) { //"dir" command
        dir(args, outp);
    }
    else if (!strcmp(args[0], "cd")) { //"cd" command
        cd(args);
    }
    else if(!strcmp(args[0], "environ")) { //"env" command
        env(args, envp, outp);
    }
    else if(!strcmp(args[0], "echo")) { //"echo" command
        echo(args, outp);
    }
    else if(!strcmp(args[0], "pause")) { //"pause" command
        pause_until_enter(args);
    }
    else if(!strcmp(args[0], "help")) { //"help" command
	help(args);
    }
    else if (!strcmp(args[0],"quit")) {   // "quit" command
        return(1);                     // break out of 'while' loop by sending one back
    }
    /* else pass command onto OS */
    else {
	other_commands(args, length, outp, inp, background_exec);
    }
}

int main (int argc, char ** argv, char * envp[])
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    int length = argc - 1;
    /* keep reading input until "quit" command or eof of redirected input */

    if(length > 0) { // checking if there is any arguments after ./myshell
	FILE *file = fopen(argv[1], "r"); //attempt to read the file if unable to print error
	if(file == NULL) {
	    printf("Unable to open file");
	}
	else {
	    while (fgets (buf, MAX_BUFFER, file )) { // read a line
            /* tokenize the input into args array */
                arg = args;
                *arg++ = strtok(buf,SEPARATORS);   // tokenise input
                while ((*arg++ = strtok(NULL,SEPARATORS)));
                // last entry will be NULL
		if(args[0] == NULL) {
                    break;
                }
       	        int i = 0;
                while(args[i] != NULL) {
                    i++;
                }
                i = i - 1; //getting the length of the input as i
                int checker = commands(args, envp, i, 0, 0, 0); /* sending arguments to commands
if they are sent to quit 1 is returned else 0 is returned */
                if(checker == 1) { //if 1 is returned quit the while loop
                    break;
                }
	    }
	}
	fclose(file); //closing the file once all inputs have been read or quit has been reached
    }
    else { //if no batchfile is supplied go to take user inputs
    while (1) { //will continue looping until quit breaks out of the loop
        /* get command line from input */
	char* curdir; //curidr will be a string of the current directory
	curdir=(char *)malloc(100*sizeof(char));
	getcwd(curdir,100); //getting the current directory
        fputs (curdir, stdout); // write prompt of the current directory followed by $ and a space
	fputs ("$ ", stdout);
        if (fgets (buf, MAX_BUFFER, stdin )) { // read a line
            /* tokenize the input into args array */
            arg = args;
            *arg++ = strtok(buf,SEPARATORS);   // tokenise input
            while ((*arg++ = strtok(NULL,SEPARATORS)));
	    int i = 0;
            // last entry will be NULL

            if (args[0]) {                     // if there's anything there
		int inp, outp = 0; //int inp and outp are used to find any i/o redirection characters
		i = 0;
		while(args[i] != NULL) { //looping through all arguments supplied
		    if(strcmp(args[i], "<") == 0) {
			inp = i; // if < is found set inp to its position
		    }
		    if(strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0) {
			outp = i; // if > or >> is found set outp to its position
		    }
		    i++;
		}
		i = i - 1; //minus 1 from i to get the lenght
                int background_exec = 0;
		if(strcmp(args[i], "&") == 0) { //getting if theres an & at the end for background execution
		    background_exec = 1; //if there is background_exec is set to 1 else it stays 0
		}
	        int checker = commands(args, envp, i, inp, outp, background_exec);
/* checker is used to check if quit has been supplied by user if so checker will be set to 1 */
		if(checker == 1) {
		    break; // if checker is one the we exit the while loop and the program ends
		}
	    }
        }
    }}
}
