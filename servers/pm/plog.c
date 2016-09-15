#include "pm.h"
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define START 0
#define STOP 1
#define CLEARBUF 2

/* A reduced process structure to hold fork/exit and id */
typedef struct
{
	int p_id;
	time_t start_t;
	time_t end_t;
} proc;

/* Circular buffer */
typedef struct
{
	struct proc* arr[BUFFER_SIZE];
	int cur_index;
	size_t size;
} circularBuffer;

circularBuffer* buffer;

bool started;

/* Error with -1 */
int do_plog()
{
	switch (m_in.m1_i1) {
	case START :
		return plog_start();
	case STOP:
		return plog_stop();
	case CLEARBUF:
		return plog_clear();
	}
	/* Get info about process */
	return (EXIT_FAILURE);
}

int plog_start()
{
	if (started)
		return (EXIT_FAILURE);

	started = true;
}

int plog_stop()
{
	if (!started)
		return (EXIT_FAILURE);

	started = false;
}

int log_start(int id)
{
	proc* temp = (proc*)calloc(1, sizeof(proc) );
	temp->p_id = id;
	temp->start_t = do_time();
	buffer->arr[buffer->cur_index++] = temp;
	++buffer->size;
	if (buffer->cur_index == BUFFER_SIZE)
		buffer->cur_index = 0;
	return (EXIT_SUCCESS);
}

int log_end(int id)
{
	do_time();
	return -1;
}

/* Returns 0 on successful initialization and 1 on error */
int plog_clear()
{
	/* If the buffer is not null it has previously been initialized*/
	if (buffer != NULL)
	{
		/* For each value in the array we want to free the memory */
		for (int i = 0; i < buffer->size - 1; i++)
		{
			/* Sanity check for null pointers (may be unneccesary) */
			if (buffer->arr[i] != NULL){free(buffer->arr[i]);}
		}
		/* Finally free the pointer used for the buffer */
		free(buffer);
	}
	/* Allocate memory for the buffer */
	buffer = (circularBuffer*) calloc(1, sizeof(circularBuffer));
	return buffer == NULL;
}

/* Getter for process by PID */