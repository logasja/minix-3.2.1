#include <lib.h>
#include <unistd.h>

int start_plog()
{
	message m;

	m.m1_i1 = 0;

	return _syscall(PM_PROC_NR, PLOG, &m);
}