#include <lib.h>
#include <unistd.h>

int stop_plog()
{
	message m;

	m.m1_i1 = 1;

	return _syscall(PM_PROC_NR, PLOG, &m);
}