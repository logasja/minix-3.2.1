#include "fs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void logstat(char* fp, int p_id, int prevState, int state)
{
	int handle;

	handle = open(fp, O_APPEND | O_CREAT);
	char buf[40];
	int time = clock_time();
	sprintf(buf, "PID%d\t%d\t%d\t%d", p_id, time, prevState, state);
	write(handle, buf, strlen(buf));
}