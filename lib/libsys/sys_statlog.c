#include "syslib.h"

int sys_statlog(int funct, int pid, char* out)
{
	message m;
	m.m1_i1 = funct;
	m.m1_i2 = pid;

	int status = (_kernel_call(SYS_STATLOG, &m));

	out = m.m1_p1;

	return status;
}