#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <wait.h>

void clear(char * args[]) { //clear command

    pid_t pid; //used to get the process id

    switch (pid = fork()) { //forking and sending the child to the switch cases
        case -1:
            printf("failed to fork\n"); //if the program fails to fork then this error is supplied
        case 0:
            pid = getpid(); // get the childs process is
            execvp(args[0], args); //executing the function with execvp
            printf("failed to exec\n");//if execvp fails error is printed
    }
    int returnStatus;
    waitpid(pid, &returnStatus, 0); //used to wait for the child process to finish before moving on

}

void dir(char * args[], int outp) { //dir command

    pid_t pid; //used to get the process id
    char *a[50]; //array of strings that stops when i/o redirections appears
    int i = 0;
    while(i < outp) {
        a[i] = args[i];
        i++;
    }
    a[i] = NULL; //setting the last value to NULL so it can be used in exec
    switch (pid = fork()) {
        case -1:
            printf("failed to fork\n");
        case 0:
            if(outp != 0) { //if outp isnt 0 there is i/o redirection
                if(strcmp(args[outp], ">>") == 0) { //if its >> the file is open for appending the "a" does this
                    freopen(args[outp + 1], "a", stdout);
                    pid = getpid();
                    execvp(args[0], a); //the output of execvp will go to the opened file
                    printf("failed to exec\n");
                }
                else {
                    freopen(args[outp + 1], "w", stdout); //else if its > we truncate the file with "w"
                    pid = getpid();
                    execvp(args[0], a);
                    printf("failed to exec\n");
                }
            }
            else {
                pid = getpid();
                execvp(args[0], args); //if there is no i/o redirection the commands prints to screen
                printf("failed to exec\n");
            }
    }
    int returnStatus; //waiting for the child process to finish
    waitpid(pid, &returnStatus, 0);

}
void cd(char * args[]) { //cd command

    char *curdir; //curdir is used to get the current path
    if(args[1] == NULL) {
	printf("No directory supplied\n");
    }
    else if(args[1]) { //if there is a file supplied
        if(opendir(args[1])) { //if we are able to open the file
            curdir=(char *)malloc(100*sizeof(char));
            chdir(args[1]); //chdir will change to this directory
            getcwd(curdir,100); //getcwd will set curdir to this path
            printf("%s \n",curdir); //we then print the path
        }
        else { //if we cant open the file an error is printed
            printf("%s is not a valid directory\n", args[1]);
        }
        setenv("PWD",curdir,1); // changing the PWD environment variable
    }
}

void env(char * args[], char * envp[], int outp) { //environ command


    pid_t pid;
    char *a[50];
    int i = 0;
    while(i < outp) { //array of strings that stops when i/o redirections appears
        a[i] = args[i];
        i++;
    }
    a[i] = NULL;
    switch (pid = fork()) {
        case -1:
            printf("failed to fork\n");
        case 0:
            if(outp != 0) { //if i/o redirection has been detected
                if(strcmp(args[outp], ">>") == 0) { //check whether its >> or >
                    freopen(args[outp + 1], "a", stdout); //open the file for appending
                    pid = getpid();
                    execvp("env", a); //append the file
                    printf("failed to exec\n");
                } //both will make the file if the file does not already exist
                else {
                    freopen(args[outp + 1], "w", stdout); //open the file to truncate
                    pid = getpid();
                    execvp("env", a); // truncate the file
                    printf("failed to exec\n");
                }
            }
            else {
                pid = getpid();
                execvp("env", args); //else print to screen
                printf("failed to exec\n");
            }
    }
    int returnStatus;
    waitpid(pid, &returnStatus, 0); //wait for child process to finish

}

void echo(char * args[], int outp) { //echo command

    pid_t pid;
    char *a[50]; //array of strings that stops when i/o redirections appears
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
            if(outp != 0) { //checking for i/o redirection
                if(strcmp(args[outp], ">>") == 0) { //checking if its >> or >
                    freopen(args[outp + 1], "a", stdout); //open the file for appending
                    pid = getpid();
                    execvp(args[0], a); //append file
                    printf("failed to exec\n");
                }
                else {
                    freopen(args[outp + 1], "w", stdout);//open the file to truncate
                    pid = getpid();
                    execvp(args[0], a); //truncate the file
                    printf("failed to exec\n");
                }
            }
            else { //else print the result to screen
                pid = getpid();
                execvp(args[0], args);
                printf("failed to exec\n");
            }
    }

    int returnStatus;
    waitpid(pid, &returnStatus, 0); //wait for child process to finish
}

void pause_until_enter(char * args[]) { //pause command

    printf("Press the enter key to continue\n");
    getchar(); //getchar will only continue when enter is pressed
}

void help(char * args[]) { //help command

    char *a[4]; //making an arr to print the manaul to screen
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
            execvp("more", a); //the more -d command will print the manual to screen and allow the user to quit
            printf("failed to exec\n"); // q or to continue with space
    }
    int returnStatus;
    waitpid(pid, &returnStatus, 0);//wait for child process

}


void other_commands(char * args[], int length, int outp, int inp, int background_exec) { //other commands

    pid_t pid;
    char *a[50]; //array of strings that stops when i/o redirections appears
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
            if(outp != 0 && inp == 0) { //if there is output redirection check if its >> or >
                if(strcmp(args[outp], ">>") == 0) {
                    freopen(args[outp + 1], "a", stdout); //open the file to append
                    pid = getpid();
                    execvp(args[0], a); //append file
                    printf("failed to exec\n");
                }
                else {
                    freopen(args[outp + 1], "w", stdout); //open the file to truncate
                    pid = getpid();
                    execvp(args[0], a); //truncate the file
                    printf("failed to exec\n");
                }
            }
            else if(outp == 0 && inp != 0) { //if there is input redirection
                    freopen(args[inp + 1], "r", stdin); //open the file to read
                    pid = getpid();
                    execvp(args[0], a); //exec will take the use the file as stdin
                    printf("failed to exec\n");
            }
            else if(outp != 0 && inp != 0) { //if there is both i/o redirection
                freopen(args[inp + 1], "r", stdin); //open the file to read as stdin
                if(strcmp(args[outp], ">>") == 0) { //check whether we are appending or truncating the file
                    freopen(args[outp + 1], "a", stdout);
                }
                else {
                    freopen(args[outp + 1], "w", stdout);
                }
                pid = getpid();
                execvp(args[0], a); //exec will take stdin from the first file and send outputs to second file
                printf("failed to exec\n");
            }
            else { //if there is no i/o redirection
                pid = getpid();
                execvp(args[0], a); //exec as normal
                printf("failed to exec\n");
            }
    }
    if(background_exec != 1) { //if the user has not asked for background execacution
        int returnStatus; //wait for child process to complete
        waitpid(pid, &returnStatus, 0);
    }
}
