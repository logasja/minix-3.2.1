#include <lib.h>
#include <unistd.h>

int get_plog_size()
{
	message m;

	m.m1_i1 = 5;

	_syscall(PM_PROC_NR, PLOG, &m);

	// Returns the size of the buffer
	return m.m2_i1;
}