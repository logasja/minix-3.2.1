#include <lib.h>
#include <unistd.h>

void start_plog()
{
	message m;
	return _syscall(PM_PROC_NR, STARTPLOG, &m);
}