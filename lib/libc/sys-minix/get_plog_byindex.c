#include <lib.h>
#include <unistd.h>

int get_plog_byindex(int index, long* c_time, long* t_time)
{
	message m;

	m.m1_i1 = 3;
	m.m1_i3 = index;

	_syscall(PM_PROC_NR, PLOG, &m);

	*c_time = m.m2_l1;
	*t_time = m.m2_l2;
	return m.m3_i1;
}