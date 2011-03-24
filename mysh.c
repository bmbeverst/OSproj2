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
pid_t pid;
string binaryPath;

int main(int argc, char **argv) {
	// initialize variables
	string promt = "mysh$ ";
	string envPromt = NULL;
	string home = NULL;
	envPromt = getenv("MYPS");
	home = getenv("HOME");

	boolean run = 1;
	int sizeInput = 256;
	int index;
	string input = malloc(sizeof(char*)*sizeInput);
	for(index = 0; index < sizeArgs; index++) {
		args[index] = malloc(sizeof(char*)*sizeInput);
	}


	if (envPromt != NULL) {
		promt = envPromt;
	}

	//	pid = vfork();
	//	if (pid == 0) {
	//
	//		fprintf(stdout, "FORKED");
	//		//if (execvp(args[0], args) == -1) {
	//			// Error logic
	//		//}
	//	} forks forever.
	while (run) {

		fprintf(stdout, "%s", promt);
		getline(&input, (size_t *) &sizeInput, stdin);// please the compiler
		args[0] = strtok(input, " \n");

		for (index = 1; index < sizeArgs; index++) {
			args[index] = strtok(NULL, " \n");
		}
		for (index = 0; index < 3; index++) {
			fprintf(stdout, "%s\n", args[index]);
		}
		if (args[0] != NULL) {
			if (strcmp(args[0], "exit") == 0) {
				run = 0;
			} else if(strcmp(args[0], "cd") == 0) {
				if(args[1] != NULL) {
					chdir(args[1]);
				} else {
					chdir(home);
				}// used to test cd
			} else if(strcmp(args[0], "cwd") == 0) {
				getcwd(input, sizeInput);
				fprintf(stdout, "%s\n", input);
			} else if(0) {

			} else {
				string temp = binaryPath;
				strcat(binaryPath, args[0]);
				FILE *filep = fopen(temp, "r");
				if(ferror(filep) || filep == NULL)
				{
					fprintf(stderr, "Cannot open file: %s\n", argv[1]);
					exit(1);
				}
			}
		}

	}

	return 0;
}
