#include <lib.h>
#include <unistd.h>

int get_plog_byindex(int index, long* c_time, long* t_time)
{
	message m;

	int status;

	m.m1_i1 = 3;
	m.m1_i3 = index;

	status = _syscall(PM_PROC_NR, PLOG, &m);

	*c_time = m.m2_l1;
	*t_time = m.m2_l2;
	return status;
}