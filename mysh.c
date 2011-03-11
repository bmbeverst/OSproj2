/**
 * @file mysh.c
 * My implementation of a shell
 *
 * @author  Brooks Beverstock
 */
#include "mysh.h"


char* promt = "mysh$ ";
const char* envPromt = NULL;
const char* home = NULL;

int main(int argc, char **argv)
{
	// initialize variables
	envPromt = getenv("MYPS");
	home = getenv("HOME");
	boolean run = 1;
	int sizeInput = 256;
	char* input = NULL;


	while(run) {

		fprintf(stdout, "%s", input);
		getline(&input, &sizeInput, stdin);


	}

	return 0;
}
