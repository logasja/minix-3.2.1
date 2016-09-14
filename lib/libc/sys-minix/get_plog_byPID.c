#include <lib.h>
#include <unistd.h>

int get_plog_byPID(int pid, long* c_time, long* t_time)
{
	message m;
	return _syscall(PM_PROC_NR, GETPLOGBYPID, &m);
}