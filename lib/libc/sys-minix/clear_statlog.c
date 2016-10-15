#include <lib.h>
#include <unistd.h>

int clear_statlog()
{
	message m;

	int status;

	m.m1_i1 = 4;

	return _syscall(PM_PROC_NR, STATLOG, &m);
}