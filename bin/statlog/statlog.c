#include <sys/param.h>
#include <sys/stat.h>

#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HELP_DIALOGUE "usage: statlog [start|pause|add|remove|clear] [process]\n"

int main(int, char*[]);

int main(int argc, char *argv[])
{
	int status = -1;

	if (argv[1])
	{
		if (!strcmp(argv[1], "start"))
		{
			printf("Starting State Logger.\n");
			status = start_statlog();
		}
		else if (!strcmp(argv[1], "stop"))
		{
			printf("Pausing State Logger.\n");
			status = pause_statlog();
		}
		else if (!strcmp(argv[1], "clear"))
		{
			printf("Clearing State Logger.\n");
			status = clear_statlog();
		}
		else if (!strcmp(argv[1], "add"))
		{
			if (argv[2])
			{
				printf("Adding %d...", argv[2]);
				status = add_statlog(argv[2]);
			}
		}
		else if (!strcmp(argv[1], "remove"))
		{
			if (argv[2])
			{
				printf("Removing %d...", argv[2]);
				status = rm_statlog(argv[2]);
			}
		}
		else
		{
			printf(HELP_DIALOGUE);
			status = EXIT_SUCCESS;
		}
	}

	// Check status of the program
	if (status)
		printf("Error in service.\n");
	exit(status);
}