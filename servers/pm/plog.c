#include "pm.h"

#define BUFFER_SIZE 1024

/* A reduced process structure to hold fork/exit and id */
struct proc
{
	int p_id;
	time_t start_t;
	time_t end_t;
};

/* Circular buffer */
struct circularBuffer
{
	struct proc* arr[BUFFER_SIZE];
	int cur_index;
	size_t size;
};

struct circularBuffer* buffer;

int do_plog()
{
	return -1;
}

int log_start(int id)
{
	do_time();
}

int log_end(int id)
{
	do_time();
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
	buffer = (struct circularBuffer*) calloc(sizeof(struct circularBuffer));
	return buffer == NULL;
}

/* Getter for process by PID */