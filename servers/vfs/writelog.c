#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int writelog(char* fp, char* buf, int buflen)
{
	int handle = open(fp, O_APPEND | O_CREAT);
}