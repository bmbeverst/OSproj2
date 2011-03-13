/**
 * @file mysh.c
 * My implementation of a shell
 *
 * @author  Brooks Beverstock
 */
#include "mysh.h"

int sizeArgs = 10;
string args[10];// can't use sizeArgs because of error.
pid_t pid;
string binaryPath;

int main(int argc, char **argv) {
	// initialize variables
	string promt = "mysh$ ";
	string envPromt = NULL;
	string home = NULL;
	envPromt = getenv("MYPS");
	home = getenv("HOME");
	binaryPath = "/bin/";

	boolean run = 1;
	int sizeInput = 256;
	string input = NULL;
	int index;

	if (envPromt != NULL) {
		promt = envPromt;
	}

//		pid = vfork();
//		if (pid == 0) {
//
//			fprintf(stdout, "FORKED");
//			//if (execvp(args[0], args) == -1) {
//				// Error logic
//			//}
//		}// forks forever.
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
			}
//			else { // My try at forking :'( I had an infinate loop of forks
			// You need tocheck that the command is executable, fork and pass command, continue.
			// Are we suppose to run any command???????????
			// If yes that mean you have to parse the whole $PATH
//				string temp = binaryPath;
//				strcat(binaryPath, args[0]);
//				FILE *filep = fopen(temp, "r");
//				if(ferror(filep) || filep == NULL)
//				{
//					fprintf(stderr, "Cannot open file: %s\n", argv[1]);
//					exit(1);
//				}
//			}
		}

	}

	return 0;
}
