#include "pm.h"
#include "mproc.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node {
	int p_id;
	struct node* left;
	struct node* right;
} node;

int tracked_table[STATLOG_BUFFER_SIZE] = { 0 };

node* root;

bool running = false;

int do_statlog()
{
	// Switch statement to use passed message as function identifier
	switch (m_in.m1_i1) {
	case STATLOG_START:
		return statlog_start();
	case STATLOG_PAUSE:
		return statlog_pause();
	case STATLOG_ADD:
		return statlog_add();
	case STATLOG_REMOVE:
		return statlog_rm();
	case STATLOG_CLEAR:
		return statlog_clear();
	default:
		return EXIT_FAILURE;
	}
}

int statlog_start()
{
	if (!running)
		running = true;
	else
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

int statlog_pause()
{
	if (running)
		running = false;
	else
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

node* findNode(int p_id)
{
	node* path = root;
	while (path)
	{
		if (p_id > path->p_id)
			path = path->right;
		else if (p_id < path->p_id)
			path = path->left;
		else
			return path;
	}
	return path;
}

int statlog_add()
{
	node* tmp = findNode(m_in.m1_i2);
	if (!tmp)
	{
		tmp = malloc(sizeof(node));
		tmp->p_id = m_in.m1_i2;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int statlog_rm()
{
	node* tmp = findNode(m_in.m1_i2);
	if (tmp)
	{
		node* garbage = tmp;
		if (!tmp->left && !tmp->right)
			free(tmp);
		else if (tmp->left && !tmp->right)
			
	}
	return EXIT_FAILURE;
}

int statlog_clear()
{
	
}