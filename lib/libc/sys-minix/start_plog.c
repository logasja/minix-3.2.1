#include <lib.h>
#include <unistd.h>

int start_plog()
{
	message m;

	m.m1_i1 = 0;

	_syscall(PM_PROC_NR, PLOG, &m);

	return m.m3_i1;
}