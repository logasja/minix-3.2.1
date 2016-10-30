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

node* insert(node* current, int value)
{
	if (!current)
	{
		node* tmp;
		tmp = (node*)malloc(sizeof(node));
		tmp->p_id = value;
		tmp->left = NULL;
		tmp->right = NULL;
		return tmp;
	}

	if (value > current->p_id)
		current->right = insert(current->right, value);
	else if (value < current->p_id)
		current->left = insert(current->left, value);
	// Otherwise nothing to do as data already present
	return current;
}

node* delete(node* current, int value)
{
	node* tmp;
	if (!current)
		printf("Element not found");
	else if (value < current->p_id)
		current->left = delete(current->left, value);
	else if (value > current->p_id)
		current->right = delete(current->right, value);
	else
	{
		//Able to delete node and replace it with right sub-tree or max element on left
		if (current->right && current->left)
		{
			// Replace with minimum element in right tree
			tmp = findMin(current->right);
			current->p_id = tmp->p_id;
			// As we replaced it with another node, the node needs to be deleted
			current->right = delete(current->right, tmp->p_id);
		}
		else
		{
			// If only one or 0 children we directly remove it from tree and connect parent to child
			tmp = current;
			if (!current->left)
				current = current->right;
			else if (!current->right)
				current = current->left;
			free(tmp);
		}
	}
	return current;
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
	insert(root, m_in.m1_i2);
	return EXIT_SUCCESS;
}


int statlog_rm()
{
	delete(root, m_in.m1_i2);
	return EXIT_SUCCESS;
}

int statlog_clear()
{
	destroy_tree(root);
	return EXIT_SUCCESS;
}