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

int main(int argc, char **argv) {
	// initialize variables
	string promt = "mysh$ ";
	string envPromt = NULL;
	string home = NULL;
	envPromt = getenv("MYPS");
	home = getenv("HOME");

	boolean run = 1;
	boolean redirStdIn = 0;
	boolean redirStdOut = 0;
	boolean redirStdError = 0;
	boolean background = 0;
	int sizeInput = 256;
	int index = 0;
	string input = malloc(sizeof(char*)*sizeInput);

	for(index = 0; index < sizeArgs; index++) {
		args[index] = malloc(sizeof(char*)*sizeInput);
	}


	if (envPromt != NULL) {
		promt = envPromt;
	}

	while (run) {

		fprintf(stdout, "%s", promt);
		getline(&input, (size_t *) &sizeInput, stdin);// please the compiler
		//
		//Tokenize user input
		args[0] = strtok(input, " \n");// " \n" at the delimiters
		for (index = 1; index < sizeArgs; index++) {
			args[index] = strtok(NULL, " \n");
		}
		//debuging
		for (index = 0; index < 3; index++) {
			fprintf(stdout, "%s\n", args[index]);
		}
		//main shell loop
		if (args[0] != NULL) {
			//if input is exit stop program
			if (strcmp(args[0], "quit") == 0) {
				run = 0;
			// if cd is followed by a path  move to the path else go to home.
			//TODO check path
			} else if(strcmp(args[0], "cd") == 0) {
				if(args[1] != NULL) {
					chdir(args[1]);
				} else {
					chdir(home);
				}// used to test cd debug prints current working dir
			} else if(strcmp(args[0], "cwd") == 0) {
				getcwd(input, sizeInput);
				fprintf(stdout, "%s\n", input);
			} else {

				fprintf(stdout, "\n");
				pid = vfork();
			}
		}
		if (pid == 0) {//TODO need to pharse args to remove redirection, and background.
			if (execvp(args[0], args) == -1) {
				_exit(1);
			}

			for(index = 0; index < sizeArgs; index++) {

				if (args[index] != NULL) {
					if(args[index][0] == '<') {

					}
					switch(args[index][0]) {

					case '<':
						redirStdIn = 1;
						break;

					case '>':
						redirStdOut = 1;
						break;

					case '2':
						if(args[index][1] == '>') {
							redirStdError = 1;
						}
						break;
					}
				}
			}
		}
		for (index = 0; index < sizeArgs; ++index) {
			if (args[index] != NULL && strcmp(args[index], "&")) {
				background = 1;
			}
		}


		redirStdIn = 0;
		redirStdOut = 0;
		redirStdError = 0;
		background = 0;
	}

	for (index = 0; index < sizeArgs; ++index) {
		free(args[index]);
	}
	free(input);
	return 0;
}
