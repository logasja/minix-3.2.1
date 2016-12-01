#include "../system.h"
#include <minix/endpoint.h>
#include "../proc.h"
#include "../statlog.h"
#include <minix/sysutil.h>
#include <stdlib.h>

int do_statlog(struct proc *caller_ptr, message * m_ptr)
{
	int idx, p_id;

	int procTableIndex = 5;
	int procTableLim = 261;

	idx = m_ptr->m1_i1;
	p_id = m_ptr->m1_i2;

	if (idx == -2)
	{
		statlog(p_id, STAT_RUN, STAT_TER);
		return EXIT_SUCCESS;
	}

	// Turning tracking on
	if (idx == -5)
		if (p_id == -9)
		{
			int y = BUFFER_LENGTH - 1;
			for (int x = BUFFER_LENGTH - 11; x < BUFFER_LENGTH - 1; ++x)
			{
				if (--y <= 0)
					return BUFFER_LENGTH;
				printf("PID %d time %d", stateBuffer[x].p_id, stateBuffer[x].stateTime);
				printStates(stateBuffer[x].prevState, stateBuffer[x].state);
			}
		}
}


char* decode(int state)
{
	switch (state) {
	case STAT_RDY: return "Ready";
	case STAT_RUN: return "Running";
	case STAT_BLK: return "Blocked";
	case STAT_TER: return "Terminated";
	default: return "N/A"; break;
	}
}

void printStates(int state0, int state1)
{
	char* str1 = decode(state0);
	char* str2 = decode(state1);
}