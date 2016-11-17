#include <lib.h>
#include <unistd.h>

int rm_statlog(int p_id)
{
	message m;

	int status;

	m.m1_i1 = 3;
	m.m1_i2 = p_id;

	return _syscall(PM_PROC_NR, STATLOG, &m);
}