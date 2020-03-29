/*
* Project: Binary Search Tree
* File : Main.c
* Author : Ton That Quynh Thong
* Reference : professor Linda Zuvich
* Date : 2 / 6 / 2019
* Description : This is the main source file of BST
*/
#include "BST.h"
#include "Node.h"
#include <stdbool.h>
#include <stdlib.h>

//Function prototype
void postOrderDelete(Node* node);
int inOrderList(double* arr, Node* node, int index);
bool recursiveContains(Node* node, double value);
bool recursiveInsert(Node* current, Node*parent, double value);
void deleteNode(BST* tree, Node* node, Node* parent);

/*
 * Function: initializeBST
 * Description: Creates a dynamic BST struct object and returns
 *              a pointer to it.
 * Output:
 *     BST* - a pointer to the BST struct object
 */
BST* initializeBST()
{
	BST* tree = malloc(sizeof(BST));
	tree->count = 0;
	tree->root = NULL;
	return tree;
}

/*
 * Function: deleteBST
 * Description: Frees the dynamic memory for all nodes in the BST
				and then deletes the BST itself from memory.
 * Input:
 *    tree - a pointer to the BST struct object to be deleted
 */
void deleteBST(BST* tree)
{
	//post order traversal to delete each node
	if (tree->count > 0)
		postOrderDelete(tree->root);
	//delete BST
	free(tree);	
}

/*
* Function: postOrderDelete
* Description: Recursively travere and delete node
* Input:
*	Node* node: a node want to delete
*/
void postOrderDelete(Node* node)
{
	//TODO - Write a post-order traversal that deletes each node from memory
	//1-Traverse the left subtree, 2-Traverse the right subtree, 3-reach root
	if (node == NULL)//Base case
		return;
	else
	{
		postOrderDelete(node->left);
		postOrderDelete(node->right);
		free(node);
		node = NULL;
	}
}

/*
 * Function: list
 * Description: Creates a dynamic array of all the values in the
 *              given BST in sorted order. NOTE: This function passes
 *              the responsibility to the caller to free the memory
 *              reserved for this array.
 * Input:
 *     tree - a pointer to the BST struct object
 * Output:
 *     double* - a pointer to the array
 */
double* list(BST* tree)
{
	if (tree->count == 0)
		return NULL;
	double* arr = calloc(tree->count, sizeof(double));
	inOrderList(arr, tree->root, 0);
	return arr;
}

/*
 * Function: inOrderList
 * Description: An in-order traversal that places each value in the given array
 * Input:
 *     double* arr: dynamic array from list function
 *	   Node* node: current node
 *	   int index: current index
 * Output:
 *	   return an array which held all of node's value from small->high
 */
int inOrderList(double* arr, Node* node, int index)
{
	//1-Traverse the left subtree, 2-reach root, 3-Traverse the right subtree
	if (node != NULL)
	{
		index = inOrderList(arr, node->left, index);
		arr[index] = node->value;
		index++;
		index = inOrderList(arr, node->right, index);
	}
	return index;
}

/*
 * Function: contains
 * Description: Checks if the given value exists in the given BST.
 * Input:
 *     tree - a pointer to the BST struct object to be deleted
 *     value - the value to search for
 * Output:
 *     bool - true if the tree contains the value, false if not
 */
bool contains(BST* tree, double value)
{
	return recursiveContains(tree->root, value);
}

/*
 * Function: recursiveContains
 * Description: Checks if the given value exists in the given BST.
 * Input:
 *     node - current node
 *     value - the value to search for
 * Output:
 *     bool - Return true if it's found, false if not
 */
bool recursiveContains(Node* node, double value)
{
	// Base case
	if (node == NULL)
		return false;
	// Found value
	if (node->value == value)
		return true;
	// Value is greater than node's value
	if (node->value < value)
		return recursiveContains(node->right, value);
	// Value is smaller than node's value
	else if (node->value > value)
		return recursiveContains(node->left, value);
	// Not found value
	return false;
}

/*
 * Function: insert
 * Description: Adds the given value to the given BST if the value
				does not already exist in the tree.
 * Input:
 *     tree - a pointer to the BST struct object
 *     value - the value to add
 * Output:
 *     bool - true if the value was added, false if not (no duplicates allowed)
 */
bool insert(BST* tree, double value)
{
	//if there are no nodes yet, make this value the root
	if (tree->count == 0)
	{
		tree->root = malloc(sizeof(Node));
		tree->root->value = value;
		tree->root->left = NULL;
		tree->root->right = NULL;
		tree->count++;
		return true;
	}
	//call recursive insert to handle the rest
	if (recursiveInsert(tree->root, NULL, value))
	{
		tree->count++;
		return true;
	}
	else
		return false;
}

/*
* Function: recursiveInsert
* Description: recurively travel throught the tree to add new node
* Input:
*	Node* current: the current node
*	Node* parent: the parent node of current node
*	double value: the value of current node
* Ouput:
*	returns true if the value was added, false if not
*/
bool recursiveInsert(Node* current, Node* parent, double value)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	if (current == NULL)
	{
		if (parent == NULL)
			current = newNode;
		else
		{
			if (newNode->value < parent->value)
				parent->left = newNode;
			else if (newNode->value > parent->value)
				parent->right = newNode;
		}
		return true;
	}
	else if (newNode->value == current->value)
		return false;
	else if (newNode->value < current->value)
		recursiveInsert(current->left, current, newNode->value);
	else if (newNode->value > current->value)
		recursiveInsert(current->right, current, newNode->value);
}

/*
 * Function: delete
 * Description: Removes the given value from the given BST if the value
				exists in the tree.
 * Input:
 *     tree - a pointer to the BST struct object
 *     value - the value to remove
 * Output:
 *     bool - true if the value was removed, false if not (not found)
 */
bool delete(BST* tree, double value)
{
	//handle if tree is empty
	if (tree->count == 0)
		return false;
	//find the value in the tree and its parent
	Node* node = tree->root;
	Node* parent = NULL;
	bool foundIt = (node->value == value);
	while (node != NULL && !foundIt)
	{
		if (value < node->value)
		{
			parent = node;
			node = node->left;
		}
		else if (value > node->value)
		{
			parent = node;
			node = node->right;
		}
		else
		{
			foundIt = true;
		}
	}
	if (!foundIt)
		return false;
	//call the deleteNode function to delete the found node
	deleteNode(tree, node, parent);
	tree->count--;
	return true;
}

/*
 * Function: deleteNode
 * Description: Delete each node from the tree
 * Input:
 *     tree - a pointer to the BST struct object
 *	   node - node to be deleted
 * Output:
 *     a node is deleted from tree given
 */
void deleteNode(BST* tree, Node* node, Node* parent)
{
	//No children
	if (node->left == NULL && node->right == NULL)
	{
		//Delete root the node reach to the root
		if (parent == NULL)
		{
			free(tree->root);
			tree->root = NULL;
		}
		//Condition to point current node to a node after deleted node
		else
		{
			if (parent->left == node)
				parent->left = NULL;
			else if (parent->right == node)
				parent->right = NULL;
			free(node);
			node = NULL;
		}
	}
	//One right chill
	else if (node->left == NULL)
	{
		//If right node link to root the root
		if (parent == NULL)
			tree->root = node->right;
		//Condition to point current node to a node after deleted-node
		else if (parent->left == node)
			parent->left = node->right;
		else if (parent->right == node)
			parent->right = node->right;
		//Delete node
		free(node);
		node = NULL;
	}
	//One left chill
	else if (node->right == NULL)
	{
		//If left node link to root the root
		if (parent == NULL)
			tree->root = node->left;
		//Condition to point current node to a node after deleted-node
		else if (parent->left == node)
			parent->left = node->left;
		else if (parent->right == node)
			parent->right = node->left;
		//delete node;
		free(node);
		node = NULL;
	}
	//Two child case
	else
	{
		Node* temp = node;
		//Two chilldren of left-subtree
		if (node->left->right != NULL)
		{
			//Finding the right max node of the left-subtree
			temp = temp->left;
			while (temp->right != NULL)
			{
				parent = temp;
				temp = temp->right;
			}
			//replace value with found max
			node->value = temp->value;
			//Delete max node of left-subtree
			free(parent->right);
			parent->right = NULL;
		}
		//No children of left-subtree
		else if (node->left->right == NULL)
		{
			//Replace value with found max
			node->value = temp->left->value;
			//Set the deleted node to parent
			parent = temp->left;
			//Left node point to the left node of deleted node
			node->left = temp->left->left;
			//Delele max node of left-subtree
			free(parent);
			parent = NULL;
		}
	}
}

/*
 * Function: isEmpty
 * Description: Reports if the given BST currently has any values in it.
 * Input:
 *     tree - a pointer to the BST struct object
 * Output:
 *     bool - true if the tree is empty, false if not
 */
bool isEmpty(BST* tree)
{
	return (tree->count == 0);
}

/*
 * Function: size
 * Description: Reports the number of values currently stored in the given BST.
 * Input:
 *     tree - a pointer to the BST struct object
 * Output:
 *     int - the number of values in the tree
 */
int size(BST* tree)
{
	return tree->count;
}
