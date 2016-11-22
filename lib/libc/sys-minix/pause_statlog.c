#include <lib.h>
#include <unistd.h>

int pause_statlog()
{
	message m;

	int status;

	m.m1_i1 = 1;

	return _syscall(PM_PROC_NR, STATLOG, &m);
}