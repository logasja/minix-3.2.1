#include <lib.h>
#include <unistd.h>

int reset_plog()
{
	message m;

	m.m1_i1 = 2;

	return _syscall(PM_PROC_NR, PLOG, &m);	
}