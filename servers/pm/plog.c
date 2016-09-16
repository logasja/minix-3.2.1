#include "pm.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
	int p_id;
	time_t start_t;
	time_t end_t;
} proc;

typedef struct
{
	proc* arr[PLOG_BUFFER_SIZE];
	int cur_index;
	size_t size;
} circularBuffer;

circularBuffer* buffer;

bool started = false;

int do_plog()
{
	switch (m_in.m1_i1) {
	case PLOG_START:
		return plog_start();
	case PLOG_STOP:
		return plog_stop();
	case PLOG_RESETBUF:
		return plog_clear();
	case PLOG_GETBYIDX:
		return plog_IDXget();
	case PLOG_GETBYPID:
		return plog_PIDget();
	case PLOG_GETSIZE:
		return plog_get_size();
	}
	return (EXIT_FAILURE);
}

int plog_start()
{
	if (started)
		return (EXIT_FAILURE);

	plog_clear();
	started = true;
	return EXIT_SUCCESS;
}

int plog_stop()
{
	if (!started)
		return (EXIT_FAILURE);

	started = false;
	return EXIT_SUCCESS;
}

int log_start(int id)
{
	if (!started)
		return EXIT_FAILURE;

	proc* temp = (proc*)calloc(1, sizeof(proc) );
	temp->p_id = id;
	temp->start_t = do_time();
	buffer->arr[buffer->cur_index++] = temp;
	++buffer->size;
	if (buffer->cur_index == PLOG_BUFFER_SIZE)
		buffer->cur_index = 0;
	return (EXIT_SUCCESS);
}

int log_end(int id)
{
	if (!started)
		return EXIT_FAILURE;
	do_time();
	return EXIT_FAILURE;
}

int plog_clear()
{
	/* If the buffer is not null it has previously been initialized*/
	if (buffer)
	{
		/* For each value in the array we want to free the memory */
		for (int i = 0; i < buffer->size - 1; i++)
		{
			/* Sanity check for null pointers (may be unneccesary) */
			if (buffer->arr[i]){free(buffer->arr[i]);}
		}
		/* Finally free the pointer used for the buffer */
		free(buffer);
	}
	/* Allocate memory for the buffer */
	buffer = (circularBuffer*) calloc(1, sizeof(circularBuffer));
	return buffer == NULL;
}

/* Getter for process by PID */
int plog_get_size()
{
	if (!buffer)
		return EXIT_FAILURE;

	m_in.m2_i1 = buffer->size;
	
	return EXIT_SUCCESS;
}

int plog_PIDget()
{
	if (!buffer)
		return EXIT_FAILURE;

	for (int i = 0; i < buffer->size - 1; i++)
	{
		if (m_in.m1_i2 == buffer->arr[i]->p_id)
		{
			m_in.m2_l1 = buffer->arr[i]->start_t;
			m_in.m2_l2 = buffer->arr[i]->end_t;
			return EXIT_SUCCESS;
		}
	}

	return EXIT_FAILURE;
}

int plog_IDXget()
{
	if (!buffer || buffer->size < m_in.m1_i3)
		return EXIT_FAILURE;

	m_in.m2_l1 = buffer->arr[m_in.m1_i3]->start_t;
	m_in.m2_l2 = buffer->arr[m_in.m1_i3]->end_t;
	m_in.m1_i2 = buffer->arr[m_in.m1_i3]->p_id;

	return EXIT_SUCCESS;
}