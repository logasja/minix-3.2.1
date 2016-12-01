#include "../system.h"
#include <minix/endpoint.h>
#include "../proc.h"
#include "../statlog.h"
#include <minix/sysutil.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool tracking = FALSE;

int do_statlog(struct proc *caller_ptr, message * m_ptr)
{
	int funct, p_id, index;

	char* out;

	funct = m_ptr->m1_i1;
	p_id = m_ptr->m1_i2;
	index = m_ptr->m1_i3;

	int status = EXIT_FAILURE;

	switch (funct) {
	case POLL_LOG:
		status = statlog_poll(out);
	case START_TRACKING:
		status = statlog_start();
	case STOP_TRACKING:
		status = statlog_stop();
	case ADD_PID:
		status = statlog_add(p_id);
	case RM_PID:
		status = statlog_rm(p_id);
	case FORK:
		status = statlog_fork(p_id, index);
	}

	m_ptr->m1_p1 = out;

	return status;
}

int statlog_add(int p_pid)
{
	// Bypass tasks in process table
	int idx = NR_TASKS;

	// Try to find process in proc table
	for (idx; idx < PROCESS_TABLE_LIMIT; ++idx)
	{
		if (proc[idx].p_pid == p_pid)
		{
			proc[idx].tracking = tracking;
			return EXIT_SUCCESS;		// Found the already running process and added it
		}
	}

	// Add a log entry indicating when it was added
	statlog(p_pid, -1, STAT_ADD);
}

int statlog_start()
{
	// Bypass the tasks in the process table
	int idx = NR_TASKS;

	// Start tracking on all labelled processes
	for (idx; idx < PROCESS_TABLE_LIMIT; ++idx)
	{
		if (proc[idx].p_pid != 0)
			proc[idx].tracking = 1;
	}

	tracking = TRUE;

	return EXIT_SUCCESS;	// The p_id was not found
}

int statlog_stop()
{
	// Bypass tasks in process table
	int idx = NR_TASKS;

	// Stop tracking on all labelled processes
	for (idx; idx < PROCESS_TABLE_LIMIT; ++idx)
	{
		if (proc[idx].p_pid != 0)
			proc[idx].tracking = 0;
	}

	tracking = FALSE;

	return EXIT_SUCCESS;
}

int statlog_poll(char * out)
{
	// Polls the log and returns the log entries as a single character array
	int i = 0;
	while (i < logSize)
	{
		++i;
		strcat(out, printState(stateBuffer[logStart++]));
		if (logStart > BUFFER_LENGTH)
			logStart = 0;
	}
	return EXIT_SUCCESS;
}

char* decode(int state)
{
	switch (state) {
	case STAT_RDY: return "RDY";
	case STAT_RUN: return "RUN";
	case STAT_BLK: return "BLK";
	case STAT_TER: return "TER";
	case STAT_ADD: return "ADD";
	default: return "N/A";
	}
}

char* printState(struct statBuf in)
{
	char* str1 = decode(in.prevState);
	char* str2 = decode(in.state);
	char* out;

	//For debug purposes
	printf("DEBUG::PRINTSTATE\tPID%d\t%d\t%s\t%s\n", in.p_id, in.stateTime, str1, str2);

	sprintf(out, "PID%d\t%d\t%s\t%s\n", in.p_id, in.stateTime, str1, str2);
	return out;
}