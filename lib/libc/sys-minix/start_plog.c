#include <lib.h>
#include <unistd.h>

int start_plog()
{
	message m;

	m.m1_i1 = 0;

	// Returns the success or failure status of the system call
	return _syscall(PM_PROC_NR, PLOG, &m);
}