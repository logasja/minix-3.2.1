#include <minix/syslib.h>
#include <minix/gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int b = getpid();
	printf("Starting I/O intensive process on %d...\n", b);
	clock_t start = clock();

	FILE *fpout;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	fpout = fopen("./dataout.txt", "w+");

	if (fpout == NULL)
	{
		printf("One of the files could not be opened.\n");
		exit(EXIT_FAILURE);
	}

	char cmd = ' ';

	printf("Write '-' to stop typing.\n");

	// Get user input and save to file
	while (cmd != '-')
	{
		cmd = getchar();
		fprintf(fpout, "%c", cmd);
		printf("%c", cmd);
	}

	clock_t diff = clock() - start;
	printf("The I/O computation took %d.\n", diff);
	_exit(EXIT_SUCCESS);
}