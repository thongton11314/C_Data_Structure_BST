/*
* Project: Binary Search Tree
* File: Main.c
* Author: Ton That Quynh Thong
* Reference: professor Linda Zuvich
* Date: 2/6/2019
* Description: This is the main source file of BST
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Node.h"
#include "BST.h"

//Function prototype
void testStartEnd();
void testEmpty();
void testSorted();
void testReverseSorted();
void testBalanced();
void printTree(BST* tree);
void printList(BST* tree);
void printNodes(Node* node, int spaces);

/*
* Function: main
* Description: Testing all the function 1 = true, 0 = false
*/
int main()
{
	printf("%s\n", "==========================================");
	printf("%s\n", "             TESTING BST");
	printf("%s\n", "         1 = true, 0 = false");
	printf("%s\n", "==========================================");
	//Test tree hasn't node/has nodes
	testStartEnd();
	printf("%s\n", "==========================================");
	//Test tree empty
	testEmpty();
	printf("%s\n", "==========================================");
	//Test tree with acessding
	testSorted();
	printf("%s\n", "==========================================");
	//Test tree with decessding
	testReverseSorted();
	printf("%s\n", "==========================================");
	//Test balance tree
	testBalanced();	
	//end
	getchar();
	return;
}

/*
* Function: testStartEnd
* Description: Test initialized/delte BST
* Output: tree - initialzied and tree is deleted
*/
void testStartEnd()
{
	//test initializeBST
	BST* tree = initializeBST();
	printf("%s\n", "POST BST INITIALIZATION");
	printf("tree is initialized |%i\n", (tree->count == 0));
	//test deleteBST
	deleteBST(tree);
	printf("%s\n", "POST BST DELETE");
	printf("tree is initialized |%i\n", (tree->count == 0));
}

/*
* Function: testEmpty
* Description: Test tree is empty or not
* Output: tree is empty has value 1, tree is not empty has value 0
*/
void testEmpty()
{
	//start
	BST* tree = initializeBST();
	//testing with no nodes
	printf("%s\n", "WITHOUT NODES:");
	//test list
	double* arr1 = list(tree);
	printf("Testing tree list is empty \t|%i\n", (arr1 == NULL));
	//test contains
	printf("Testing contains \t\t|%i\n", contains(tree, 7));
	//test delete
	printf("Testing deleted \t\t|%i\n", delete(tree, 7));
	//test isEmpty
	printf("Testing tree is empty \t\t|%i\n", isEmpty(tree));
	//test size
	printf("count = %i\n", size(tree));
	//end
	deleteBST(tree);
}

/*
* Function: testSorted
* Description: Test tree is empty or not
*/
void testSorted()
{
	//start
	BST* tree = initializeBST();
	printf("%s\n", "WITH SORTED NODES:");
	//test adding unique values   	
	printf("- Test add value \n");
	printf("  + add 30 | %i\n", insert(tree, 30));
	printf("  + add 40 | %i\n", insert(tree, 40));
	printf("  + add 50 | %i\n", insert(tree, 50));
	printf("  + add 60 | %i\n", insert(tree, 60));
	printf("  + add 70 | %i\n", insert(tree, 70));
	printf("  + add 35 | %i\n", insert(tree, 35));
	printf("  + add 25 | %i\n", insert(tree, 25));
	printf("  + add 20 | %i\n", insert(tree, 20));
	printf("  + add 15 | %i\n", insert(tree, 15));	
	printf("  + add 16 | %i\n", insert(tree, 16));
	printf("  + add 17 | %i\n", insert(tree, 17));
	printf("  + add 10 | %i\n", insert(tree, 10));
	printf("  + add 11 | %i\n", insert(tree, 11));
	printf("  + add 12 | %i\n", insert(tree, 12));
	printf("  + add 5  | %i\n", insert(tree, 5));
	printf("- Test size adding | %d\n", (size(tree) == tree->count));
	//Test print tree
	printf("- Current tree structure:\n");
	printTree(tree);
	//Test print list
	printf("- Test print List:\n");
	printList(tree);
	//test the size function
	printf("- Count list = %i\n", size(tree));
	//test adding a duplicate
	printf("- Testing duplicate:\n");
	printf("  + Add 30 again | %i\n", insert(tree, 30));
	printf("  + Add 40 again | %i\n", insert(tree, 40));
	printf("  + Add 50 again | %i\n", insert(tree, 50));
	//test contains with an existing value
	printf("- Testing existing value:\n");
	printf("  + Contain 0   | %d\n", contains(tree, 0));
	printf("  + Contain 30  | %d\n", contains(tree, 30));
	printf("  + Contain 100 | %d\n", contains(tree, 100));
	//Test delete node
	printf("- Test delete node\n");
	printf("  + Case 1: No child (70)  | %d\n", delete(tree, 70));
	printf("  + Case 2-1: Two child with left-subtree's max right (15)        | %d\n", delete(tree, 15));
	printf("  + Case 2-2: Two child with left-subtree without max right (40)  | %d\n", delete(tree, 40));
	printf("  + Case 3: One right (50) | %d\n", delete(tree, 50));
	printf("  + Case 4: One left (20)  | %d\n", delete(tree, 20));
	printf("- Current tree after delete\n");
	printTree(tree);
	printf("- Test size delete-tree | %d\n", (size(tree) == tree->count));
	//Delete whole tree
	deleteBST(tree);
	//end    	
}

/*
* Function: testBalanced
* Description: Testing balance tree
* Output: A balance tree
*/
void testBalanced()
{
	//Test balance
	BST* tree = initializeBST();
	printf("TEST BALANCED TREE\n");
	insert(tree, 0);
	insert(tree, 1);
	insert(tree, 1.5);
	insert(tree, 1.25);
	insert(tree, 1.75);
	insert(tree, 0.5);
	insert(tree, 0.25);
	insert(tree, 0.75);
	insert(tree, -1);
	insert(tree, -1.5);
	insert(tree, -1.25);
	insert(tree, -1.75);
	insert(tree, -0.5);
	insert(tree, -0.25);
	insert(tree, -0.75);
	//Print tree
	printTree(tree);
	//Print list
	printf("List of value:\n");
	printList(tree);
	printf("\n");
}

/*
* Function: testReverseSorted
* Description: Testing reverse tree
*/
void testReverseSorted()
{
	BST* tree = initializeBST();
	printf("TEST Reverse Sorted TREE\n");
	insert(tree, 0);
	insert(tree, -1);
	insert(tree, -1.5);
	insert(tree, -2);
	insert(tree, -1.75);
	insert(tree, -1.65);
	//Print tree
	printTree(tree);
	//Print list
	printf("List of value:\n");
	printList(tree);
	printf("\n");
}

/*
 * The following functions can be used to print out the entire tree structure horizontally
 * using a simple recursive function. It is good for testing correct insertion and deletion.
 */

 /*
 * Function: printTree
 * Description: Use to print a whole tree
 * Input:
 *	BST* tree: tree which input in
 */
void printTree(BST* tree)
{
	printNodes(tree->root, 4);
	printf("\n");
}

/*
* Function: printNodes
* Description: Use to print each node attched to tree 
* Input:
*	Node* node: node in
*	int spaces: space between each node
* Output:
*	node which put in
*/
void printNodes(Node* node, int spaces)
{
	int i;
	if (node != NULL)
	{
		printNodes(node->right, spaces + 10);
		for (i = 0; i < spaces; i++)
			printf(" ");
		printf("%.02f\n", node->value);
		printNodes(node->left, spaces + 10);
	}
}

/*
* Function: printList
* Description: Use to print list
* Input:
*	BST* tree: tree which input in
* Output:
*	all value of each node from tree
*/
void printList(BST* tree)
{
	double* arr = list(tree);
	for (int i = 0; i < size(tree); i++)
		printf("%.2f ", arr[i]);
	printf("\n");
	free(arr);
}