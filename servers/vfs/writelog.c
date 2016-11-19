#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

char* fp = "/usr/tmp/log.txt";

void writelog(char* buf)
{
	printf("\tOpening file.\n");
	int handle = open(fp, O_APPEND | O_CREAT, S_IWRITE);
	printf("\tFile open returned %d.\n", handle);
	printf("\tWriting to file.\n");
	write(handle, buf, strlen(buf));
	printf("\tWriting finished.\n");
}