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

#define HELP_DIALOGUE "usage: plog [-hsipc] [index...process]\n"

int main(int, char*[]);

int main(int argc, char *argv[])
{
	int status = EXIT_FAILURE;
	if (*argv)
	{
		int ch;
		if ((ch = getopt(argc, argv, "ipcs")) != -1)
		{
			int param = atoi(*argv);
			long start, end;
			switch (ch) {
			case 'p':
				/*if present, gets process by id*/
				status = get_plog_byPID(param, &start, &end);
				if (status)
					fprintf(stderr, "Could not find the specified process log.\n");
				else
					fprintf(stderr, "PID: %d\n\tStart: %ld\n\tEnd: %ld\n", param, start, end);
				break;
			case 'i':
				/*if present, get process by index*/
				status = get_plog_byindex(param, &start, &end);
				if (status)
					fprintf(stderr, "Specified index is not valid.\n");
				else
					fprintf(stderr, "Index: %d\n\tStart: %ld\n\tEnd: %ld\n", param, start, end);
				break;
			case 's':
				/* Starts or stops the plog service */
				if (param == 1)
				{
					status = start_plog();
					fprintf(stderr, "Starting process logger.\n");
				}
				else if (param == 0)
				{
					status = stop_plog();
					fprintf(stderr, "Stopping process logger.\n");
				}
				else
					fprintf(stderr, HELP_DIALOGUE);
			case 'c':
				/*clear the current buffer*/
				status = reset_plog();
				fprintf(stderr, "Resetting logger buffer.\n");
				break;
			default:
				fprintf(stderr, HELP_DIALOGUE);
			}
		}
	}
	exit(status);
}