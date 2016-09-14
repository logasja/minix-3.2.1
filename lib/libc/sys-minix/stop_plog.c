#include <lib.h>
#include <unistd.h>

void stop_plog()
{
	message m;
	return _syscall(PM_PROC_NR, STOPPLOG, &m);
}