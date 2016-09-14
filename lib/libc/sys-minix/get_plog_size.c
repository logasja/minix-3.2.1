#include <lib.h>
#include <unistd.h>

int get_plog_size()
{
	message m;
	return _syscall(PM_PROC_NR, GETPLOGSIZE, &m);
}