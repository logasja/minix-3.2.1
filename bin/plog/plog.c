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

#define HELP_DIALOGUE "usage: plog [start|stop] [-sip] [index...process]\n"

int main(int, char*[]);

int main(int argc, char *argv[])
{
	int status = -1;

	if (argv[1])
	{
		if (!strcmp(argv[1],"start"))
		{
			fprintf(stderr, "Starting process logger.\n");
			status = start_plog();
		}
		else if (!strcmp(argv[1],"stop"))
		{
			fprintf(stderr, "Stopping process logger.\n");
			status = stop_plog();
		}
		else if (!strcmp(argv[1], "clear"))
		{
			fprintf(stderr, "Clearing buffer.\n");
			status = reset_plog();
		}
	}

	if (status > -1)
	{
		if (status)
		{
			fprintf(stderr, "Error starting or stopping service.\n");
			exit(status);
		}
	}

	int ch;
	if ((ch = getopt(argc, argv, "sip")) != -1)
	{
		int param;
		if (argv[2])
		{
			param = atoi(argv[2]);
		}
		long start, end = 0;
		int size;
		switch (ch) {
		case 'p':
			status = get_plog_byPID(param, &start, &end);
			if (status)
				fprintf(stderr, "Could not find the specified process log.\n");
			else
				fprintf(stderr, "PID: %d\n\tStart: %ld\n\tEnd: %ld\n", param, start, end);
			break;
		case 'i':
			status = get_plog_byindex(param, &start, &end);
			if (status)
				fprintf(stderr, "Specified index is not valid.\n");
			else
				fprintf(stderr, "Index: %d\n\tStart: %ld\n\tEnd: %ld\n", param, start, end);
			break;
		case 's':
			size = get_plog_size();
			fprintf(stderr, "Buffer has a size of %d items.\n", size);
			status = EXIT_SUCCESS;
			break;
		}
	}
	if (status < 0)
	{
		fprintf(stderr, HELP_DIALOGUE);
		status = EXIT_FAILURE;
	}
	exit(status);
}