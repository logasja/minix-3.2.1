#include <lib.h>
#include <unistd.h>

int start_statlog()
{
	message m;

	int status;

	m.m1_i1 = 0;

	return _syscall(PM_PROC_NR, STATLOG, &m);
}