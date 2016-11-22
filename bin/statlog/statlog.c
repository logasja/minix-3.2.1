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

	char* op;

	if (argv[1])
		op = argv[1];
	else
		exit(printf(HELP_DIALOGUE));

	if (!strcmp(op, "start"))
	{
		printf("Starting State Logger.\n");
		status = start_statlog();
	}
	else if (!strcmp(op, "pause"))
	{
		printf("Pausing State Logger.\n");
		status = pause_statlog();
	}
	else if (!strcmp(op, "clear"))
	{
		printf("Clearing State Logger.\n");
		status = clear_statlog();
	}

	if (argv[2])
	{
		int param;
		param = atoi(argv[2]);
		if (!strcmp(op, "add"))
		{
			printf("Adding %d...\n", param);
			status = add_statlog(param);
		}
		else if (!strcmp(op, "remove"))
		{
			printf("Removing %d...\n", param);
			status = rm_statlog(param);
		}
	}

	if (status < 0)
	{
		printf(HELP_DIALOGUE);
		status = EXIT_FAILURE;
	}
	else
	{
		if (status == EXIT_FAILURE)
			printf("Errored.\n");
	}

	exit(status);
}