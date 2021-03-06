#include "pm.h"
#include "mproc.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node {
	int p_id;
	uint16_t prev_state;
	struct node* left;
	struct node* right;
} node;

node* root = 0;

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

/*===========================================================================*
*				mproc_dmp				     *
*===========================================================================*/
char *flags_str(int flags)
{
	char* str = (char*)malloc(sizeof(char));
	str[0] = (flags & IN_USE) ? 'R' : '-';
	str[1] = (flags & WAITING) ? 'W' : '-';
	str[2] = (flags & ZOMBIE) ? 'Z' : '-';
	str[3] = (flags & PAUSED) ? 'P' : '-';
	str[4] = (flags & ALARM_ON) ? 'A' : '-';
	str[5] = (flags & EXITING) ? 'E' : '-';
	str[6] = (flags & STOPPED) ? 'S' : '-';
	str[7] = (flags & SIGSUSPENDED) ? 'U' : '-';
	str[8] = (flags & VFS_CALL) ? 'F' : '-';
	str[9] = (flags & REPLY) ? 'r' : '-';
	str[10] = (flags & PM_SIG_PENDING) ? 's' : '-';
	str[11] = (flags & PRIV_PROC) ? 'p' : '-';
	str[12] = (flags & PARTIAL_EXEC) ? 'x' : '-';
	str[13] = (flags & DELAY_CALL) ? 'd' : '-';
	str[14] = '\0';

	return str;
}

/*****************************************************************/
/************************BST**************************************/
/*****************************************************************/
void destroy_tree(node* leaf)
{
	if (leaf)
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		free(leaf);
	}
}

node* findMin(node* current)
{
	if (!current)
		/* No element */
		return NULL;
	if (current->left)
		/* Follow left to find minimum */
		return findMin(current->left);
	else
		return current;
}

node* findMax(node* current)
{
	if (!current)
		/* No element */
		return NULL;
	if (current->right)
		/* Follow right to find maximum */
		return findMax(current->right);
	else
		return current;
}

node* insert(node** current, int value)
{
	if (!*current)
	{
		*current = (node*)malloc(sizeof(node));
		(*current)->p_id = value;
		(*current)->prev_state = 0u;
		(*current)->left = NULL;
		(*current)->right = NULL;
		return *current;
	}

	if (value > (*current)->p_id)
		return insert(&(*current)->right, value);
	else if (value < (*current)->p_id)
		return insert(&(*current)->left, value);
	// Otherwise nothing to do as data already present
	return NULL;
}

node* delete(node** current, int value)
{
	node* tmp;
	if (!*current)
		printf("Element not found");
	else if (value < (*current)->p_id)
		(*current)->left = delete(&(*current)->left, value);
	else if (value >(*current)->p_id)
		(*current)->right = delete(&(*current)->right, value);
	else
	{
		//Able to delete node and replace it with right sub-tree or max element on left
		if ((*current)->right && (*current)->left)
		{
			// Replace with minimum element in right tree
			tmp = findMin((*current)->right);
			(*current)->p_id = tmp->p_id;
			// As we replaced it with another node, the node needs to be deleted
			(*current)->right = delete(&(*current)->right, tmp->p_id);
		}
		else
		{
			// If only one or 0 children we directly remove it from tree and connect parent to child
			tmp = *current;
			if (!tmp->left)
				*current = tmp->right;
			else if (!tmp->right)
				*current = tmp->left;

			free(tmp);
		}
	}
	return *current;
}

node* find(node* current, int value)
{
	if (!current)
		return NULL;
	if (value > current->p_id)
		return find(current->right, value);
	else if (value < current->p_id)
		return find(current->left, value);
	else
		return current;
}


void PrintInorder(node* current)
{
	if (current == NULL)
	{
		return;
	}
	PrintInorder(current->left);
	printf("%d ", current->p_id);
	PrintInorder(current->right);
}

void PrintPreorder(node* current)
{
	if (current == NULL)
	{
		return;
	}
	printf("%d ", current->p_id);
	PrintPreorder(current->left);
	PrintPreorder(current->right);
}

void PrintPostorder(node* current)
{
	if (current == NULL)
	{
		return;
	}
	PrintPostorder(current->left);
	PrintPostorder(current->right);
	printf("%d ", current->p_id);
}

/**********************************************************/
/**********************Statlog*****************************/
/**********************************************************/
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

int statlog_add()
{
	insert(&root, m_in.m1_i2);
	PrintInorder(root);
	printf("\n");
	return EXIT_SUCCESS;
}


int statlog_rm()
{
	delete(&root, m_in.m1_i2);
	PrintInorder(root);
	printf("\n");
	return EXIT_SUCCESS;
}

int statlog_clear()
{
	destroy_tree(root);
	return EXIT_SUCCESS;
}

int log_stat(int p_id, int state)
{
	if (running)
	{
		node* found = find(root, p_id);
		
		if (!found)
			return EXIT_FAILURE;

		do_time();
		int time = mp->mp_reply.m2_l1;
		
		char* prev = flags_str(found->prev_state);
		char* cur = flags_str(state);

		printf("PID%d\t%d\t%s\t%s\n",p_id, time, prev, cur);
		free(prev); free(cur);
		found->prev_state = state;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}