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
	int value = m_in.m1_i2;
	if (root == NULL)
		return EXIT_FAILURE;
	else
	{
		if (root->p_id == value)
		{
			node* auxRoot = malloc(sizeof(node));
			auxRoot->left = root;
			node* removedNode = rmBSTNode(value, &auxRoot, &root);
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
			node* removedNode = rmBSTNode(value, NULL, &root);
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

int getMinBSTValue(node* current) {
	if (current->left == NULL)
		return current->p_id;
	else
		return getMinBSTValue(current->left);
}

void insert(int key, struct node** leaf)
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
	else if (key > (*leaf)->p_id)
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