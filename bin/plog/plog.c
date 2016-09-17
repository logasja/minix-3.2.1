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

int fflag;

int main(int, char*[]);

int main(int argc, char *argv[])
{
	int status = -1;
	if (*argv)
	{
		if (!strcmp(*argv, "start"))
		{
			status = start_plog();
			fprintf(stderr, "Starting process logger.\n");
		}
		else if (!strcmp(*argv, "stop"))
		{
			status = stop_plog();
			fprintf(stderr, "Stopping process logger.\n");
		}
		else if (!strcmp(*argv, "help"))
		{
			fprintf(stderr, "usage: plog [start | stop | help] [-ipc] [index...process]\n");
			status = EXIT_FAILURE;
		}
		if (status >= 0)
			exit(status);

		int ch;

		if ((ch = getopt(argc, argv, "ipc")) != -1)
		{
			int param = atoi(*argv);
			long start, end;
			switch (ch) {
			case 'p':
				/*if present, gets process by id*/
				status = get_plog_byPID(param, &start, &end);
				fprint(stderr, "PID: %d\n\tStart: %ld\n\tEnd: %ld\n", param, start, end);
				break;
			case 'i':
				/*if present, get process by index*/
				status = get_plog_byindex(param, &start, &end);
				fprint(stderr, "Index: %d\n\tStart: %ld\n\tEnd: %ld\n", param, start, end);
				break;
			case 'c':
				/*clear the current buffer*/
				status = reset_plog();
				break;
			}
		}
	}
}