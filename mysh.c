/**
 * @file mysh.c
 * My implementation of a shell
 *
 * @author  Brooks Beverstock
 */
#include "mysh.h"


int lengthArgs = 100;
int sizeArgs = 10;
string args[10];// can't use sizeArgs because of error.
pid_t pid = 1;
int status;
int new_stdout;

boolean redirStdIn = 0;
boolean redirStdOut = 0;
boolean redirStdError = 0;
boolean background = 0;

int main(int argc, char **argv)
{
	// initialize variables
	string promt = "mysh$ ";
	string envPromt = getenv("MYPS");
	string home = getenv("HOME");

	boolean run = 1;
	int sizeInput = 256;
	int index = 0;
	string input = malloc(sizeof(char*)*sizeInput);
	string filename = malloc(20);

	for(index = 0; index < sizeArgs; index++) {
		args[index] = malloc(sizeof(char*)*sizeInput);
	}

	if(envPromt != NULL) { // user prompt
		promt = envPromt;
	}

	while (run)
	{
		fprintf(stdout, "%s", promt);
		getline(&input, (size_t *) &sizeInput, stdin);// please the compiler

		//Tokenize user input
		args[0] = strtok(input, " \n");// " \n" at the delimiters
		for(index = 1; index < sizeArgs; index++) {
			args[index] = strtok(NULL, " \n");
		}

//		//Debugging
//		for(index = 0; index < 3; index++) {
//			fprintf(stdout, "%s\n", args[index]);
//		}

		//main shell loop
		if(args[0] != NULL)
		{
			// sets variable to run in background
			for(index = 0; index < sizeArgs; ++index) {
				if(args[index] != NULL && strcmp(args[index], "&")) {
					background = 1;
				}
			}

			// redirection set
			for(index = 0; index < sizeArgs; index++) {

				if(args[index] != NULL) {
					switch(args[index][0])
					{
						case '<': redirStdIn = index;
							break;
						case '>': redirStdOut = index;
							break;
						case '2':
							if(args[index][1] == '>') {
								redirStdError = index;
							}
							break;
					}
				}
			}

			//if input is exit stop program
			if(strcmp(args[0], "quit") == 0) {
				run = 0;
			}
			// if cd is followed by a path  move to the path else go to home.
			//TODO check path
			else if(strcmp(args[0], "cd") == 0) {
				if(args[1] != NULL) {
					chdir(args[1]);
				} else {
					chdir(home);
				}
			}
			// used to test cd debug prints current working dir
			else if(strcmp(args[0], "cwd") == 0) {
				getcwd(input, sizeInput);
				fprintf(stdout, "%s\n", input);
			} else {
				if(redirStdOut) // User cmd-line has >file in it
				{
					// Open file whose name begins with the _second_ character in cmd_args[i]
					// for writing (create it if necessary), truncate the file to size 0,
					// and give it user-group-other permissions of rw-r--r--
					new_stdout = open(&(args[redirStdOut][1]), O_WRONLY|O_CREAT|O_TRUNC, (mode_t)0644);
					if(new_stdout == -1) {
						// Open failed: error-handling here
					}
				}
				fprintf(stdout, "\n");
				pid = vfork();
				if(background == 0) {
					wait(&status);
				}
			}
		}
		if(pid == 0) {//TODO need to pharse args to remove redirection, and background.
			//sleep(2);
			if(redirStdOut) {
				if(dup2(new_stdout, 1) == -1) { // Put new_stdout on file desc #1
					perror(user_argv[0]);
					_exit(127);
				}
				close(new_stdout);
			}
			if(execvp(args[0], args) == -1) {
				_exit(1);
			}

		}


		if(redirStdIn) {
			close(new_stdout);
			redirStdIn = 0;
		} else if(redirStdOut) {
			close(new_stdout);
			redirStdOut = 0;
		}
		redirStdError = 0;
		background = 0;
	}

	for(index = 0; index < sizeArgs; ++index) {
		free(args[index]);
	}
	free(input);
	return 0;
}
