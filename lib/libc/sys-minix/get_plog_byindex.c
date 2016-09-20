#include <lib.h>
#include <unistd.h>

int get_plog_byindex(int index, long* c_time, long* t_time, int* pid)
{
	message m;

	int status;

	m.m1_i1 = 3;
	m.m1_i3 = index;

	status = _syscall(PM_PROC_NR, PLOG, &m);

	// Set pointer values to the values found in the system call
	*pid = m.m2_i1;
	*c_time = m.m2_l1;
	*t_time = m.m2_l2;
	// Return the status of the output
	return status;
}