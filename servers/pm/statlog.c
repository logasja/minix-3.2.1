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

node* findNode(int p_id, node* parent)
{
	node* path = root;
	while (path)
	{
		if (p_id > path->p_id)
		{
			parent = path;
			path = path->right;
		}
		else if (p_id < path->p_id)
		{
			parent = path;
			path = path->left;
		}
		else
			break;
	}
	return path;
}

int statlog_add()
{
	node* parent;
	node* tmp = findNode(m_in.m1_i2, parent);
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
	node* parent;
	node* toDelete = findNode(m_in.m1_i2, parent);
	if (toDelete)
	{
		if (!toDelete->left && !toDelete->right)
			free(toDelete);
		else if (toDelete->left && toDelete->right)
		{
			node* tmp = toDelete->right;
			while (tmp->left)
				tmp = tmp->left;
			toDelete->p_id = tmp->p_id;
			free(tmp);
		}
		else if (toDelete->left)
		{
			if (toDelete->p_id > parent->p_id)
				parent->right = toDelete->left;
			else
				parent->left = toDelete->left;
			free(toDelete);
		}
		else if (toDelete->right)
		{
			if (toDelete->p_id > parent->p_id)
				parent->right = toDelete->right;
			else
				parent->left = toDelete->right;
			free(toDelete);
		}
	}
	return EXIT_FAILURE;
}

int statlog_clear()
{
	
}