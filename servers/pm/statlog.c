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
	if (leaf != 0)
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		free(leaf);
	}
}

int getMinBSTValue(node* current) {
	if (current->left == NULL)
		return current->p_id;
	else
		return getMinBSTValue(current->left);
}

node* rmBSTNode(int value, node* parent, node* current)
{
	node* left = current->left;
	node* right = current->right;
	if (value < current->p_id)
	{
		if (left != NULL)
			return rmBSTNode(value, current, left);
		else
			return NULL;
	}
	else if (value > current->p_id)
	{
		if (right != NULL)
			return rmBSTNode(value, current, right);
		else
			return NULL;
	}
	else {
		if (left != NULL && right != NULL)
		{
			current->p_id = getMinBSTValue(right);
			return rmBSTNode(current->p_id, current, right);
		}
		else if (parent->left == current)
		{
			if (left != NULL)
				parent->left = left;
			else
				parent->left = right;
			return current;
		}
		else if (parent->right == current)
		{
			if (left != NULL)
				parent->right = left;
			else
				parent->right = right;
			return current;
		}
	}
}

void insert(int key, node** leaf)
{
	if (*leaf == 0)
	{
		*leaf = (node*)malloc(sizeof(node));
		(*leaf)->p_id = key;
		(*leaf)->left = 0;
		(*leaf)->right = 0;
	}
	else if (key < (*leaf)->p_id)
		insert(key, &(*leaf)->left);
	else if (key >(*leaf)->p_id)
		insert(key, &(*leaf)->right);
}

node* search(int key, node *leaf)
{
	if (leaf != 0)
	{
		if (key == leaf->p_id)
			return leaf;
		else if (key < leaf->p_id)
			return search(key, leaf->left);
		else
			return search(key, leaf->right);
	}
	else return 0;
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
	node* tmp = search(m_in.m1_i2, root);
	if (!tmp)
	{
		insert(m_in.m1_i2, &root);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}


int statlog_rm()
{
	if (root == NULL)
		return EXIT_FAILURE;
	else
	{
		if (root->p_id == m_in.m1_i2)
		{
			node* auxRoot = malloc(sizeof(node));
			auxRoot->left = root;
			node* removedNode = rmBSTNode(m_in.m1_i2, &auxRoot, &root);
			root = auxRoot->left;
			if (removedNode != NULL)
			{
				free(removedNode);
				return EXIT_SUCCESS;
			}
			else
				return EXIT_FAILURE;
		}
		else {
			node* removedNode = rmBSTNode(m_in.m1_i2, NULL, &root);
			if (removedNode != NULL)
			{
				free(removedNode);
				return EXIT_SUCCESS;
			}
			else
				return EXIT_FAILURE;
		}
	}
}

int statlog_clear()
{
	destroy_tree(root);
}