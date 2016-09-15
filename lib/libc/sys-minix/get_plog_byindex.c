#include <lib.h>
#include <unistd.h>

int get_plog_byindex(int index, long* c_time, long* t_time)
{
	message m;

	m.m1_i1 = 3;

	return _syscall(PM_PROC_NR, PLOG, &m);
}