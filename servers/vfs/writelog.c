#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void writelog(char* fp, char* buf, int buflen)
{
	printf("\tOpening file.\n");
	int handle = open(fp, O_APPEND | O_CREAT, S_IWRITE);
	printf("\tFile open returned %d.\n", handle);
	int time = 1;
	printf("Making entry.\n");
	write(handle, buf, strlen(buf));
}