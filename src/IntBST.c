//v0.2 copyright GRB-Dynamics 20160821U1338
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "IntBST.h"


//*******************************************************
//* Module Elements( Internal to file)
//*******************************************************
// Our node for the tree. Contains left child, right child, and the data itself.
struct GIntNode
	{
	struct GIntNode *Left;
	struct GIntNode *Right;
	int Value;
	};


/////////////////////////////////////////////
// A special node that serves as a pointer to the root of the tree. (see doc image)
struct GIntBST
	{
	struct GIntNode *Root;
	};


//////////////////////////////////////////////
// Deletes a node in a BST and calls itself to delete child nodes.
static void GDeleteTree(struct GIntNode *node)
	{
	// If the node has a left child, call GDeleteTree on it.
	if(node->Left != 0)
		{ GDeleteTree(node->Left); }

	// If the node has a right child, call GDeleteTree on it.
	if(node->Right != 0)
		{ GDeleteTree(node->Right); }

	// Now delete the node itself.
	free(node);
	}


//////////////////////////////////////////////
// Recursively print the values in the tree.
/** Converted to inorder traversal **/
static void GPrintTree(struct GIntNode *node)
	{
	if(node==0) { return; }

	// Print Left
	GPrintTree(node->Left);

	// Print the value of the current node.
	printf("%d ", node->Value);

	// Print Right
	GPrintTree(node->Right);
	}




//*******************************************************
//* Module Interface Functions
//*******************************************************

/////////////////////////////////////////////
// HIntBST structure that returns the parent node of a binary tree?
HIntBST IntBSTCreate(void)
	{
	struct GIntBST *newnode=(struct GIntBST *)malloc(sizeof(struct GIntBST));
	if(newnode==0)
		{
		fprintf(stderr,"Error: Unable to alloc memory\n");
		return 0;
		}
	
	// Empty Node List
	newnode->Root=0;

	return (HIntBST)newnode;
	}


//////////////////////////////////////////////
// Destroy an entire binary tree.
bool IntBSTDestroy(HIntBST htree)
	{
	// If the htree (root node) isn't null, then call GDeleteTree to recursively delete it and call GDeleteTree on it's childnodes.
	if(htree != 0)
		{		
		GDeleteTree(htree->Root); 
		}

	// Free the GIntBST Node
	free(htree);

	return true;
	}


//////////////////////////////////////////////
// Add a node to the binary tree. 
bool IntBSTAdd(HIntBST htree,int val)
	{
	printf("Inside IntBSTAdd function.\n");

	// Go through the tree checking whether each value is < or >
	struct GIntNode *tempnode; 	// Create a temporary node to traverse the tree to look for the value.
	tempnode = htree->Root;		// Start tempnode off at the root node.

	while(tempnode != 0)
		{
		// If value is equal then we can't add it.
		if(val == tempnode->Value) { break; }
		
		// If the value is less...
		if(val < tempnode->Value)
			{
			// If the left child is empty, add the node there.
			if(tempnode->Left == 0)
				{  
				// Create the node.
				struct GIntNode *newnode;
				newnode->Value = val;
				newnode->Left = 0;
				newnode->Right = 0;

				// Change the tempnode to point to this new node.
				tempnode->Left = newnode;
				return true;
				}
			// The left child isn't empty, so continue traversing the tree.
			else
				{ tempnode = tempnode->Left; }
			}

		// If the value is greater...
		else
			{
			// If the right child is empty, add the node there.
			if(tempnode->Right == 0)
				{  
				// Create the node.
				struct GIntNode *newnode;
				newnode->Value = val;
				newnode->Left = 0;
				newnode->Right = 0;

				// Change the tempnode to point to this new node.
				tempnode->Right = newnode;
				return true;
				}
			// The right child isn't empty, so continue traversing the tree.
			else
				{ tempnode = tempnode->Right; }
			}
		}

	// Handle if it's the first item in the tree
	/* Not sure if this is even necessary. */
	if(tempnode == 0)
		{  
		printf("Adding the very first node.\n"); 
		// Create the node.
		struct GIntNode *newnode;
		newnode->Value = val;
		newnode->Left = 0;
		newnode->Right = 0;

		htree->Root = newnode;

		return true;
		}

	// Only get to this point if we didn't add the node, so return false.
	return false;
	}


//////////////////////////////////////////////
// Search the tree for a value.
bool IntBSTIsMember(HIntBST htree,int val)
	{
	struct GIntNode *tempnode; 	// Create a temporary node to traverse the tree to look for the value.
	tempnode = htree->Root;		// Start tempnode off at the root node.
	
	// While we still have a node to check (because the tree isn't empty or we didn't pass over the value)...
	while(tempnode != 0)
		{
		// If the value of this node is what we want, return true and break.
		if(val == tempnode->Value) { return true; }
		
		// If the value is smaller and there's a left child to this node, set tempnode to the left child for the next iteration of this while loop.
		if(val < tempnode->Value)
			{ tempnode = tempnode->Left; }
		else
			{ tempnode = tempnode->Right; }
		}

	return false;
	}


//////////////////////////////////////////////
// Print all members of the tree.
bool IntBSTPrint(HIntBST htree)
	{
	// If the tree is empty print that it's empty.
	if(htree == 0) 
		{ 
		printf("Tree is empty.\n"); 
		}
	
	// Recursively print the nodes by calling PrintNode on the root.
	GPrintTree(htree->Root);
	printf("\n");
	
	return true;
	}


//**********************************************************
// Unit Test Code
//**********************************************************

static bool GUTIsSubTreeLargerThan(int value,struct GIntNode *node);
static bool GUTIsSubTreeSmallerThan(int value,struct GIntNode *node);
static bool GUTIsTreeOK(HIntBST htree);
static bool GUTGetCount(struct GIntNode *node);


////////////////////////////////////////////////
// Run a unit test to check the functions in this file.
bool IntBSTUnitTest(void)
	{
	/* What we're testing:

	1. Create the tree.
	2. Add 5 nodes and verify the node count.
	3. Search the tree for a value that isn't there.
	4. Search the tree for a value that is there.
	5. Print the nodes.
	6. Delete a node.
	7. Destroy the entire tree.

	*/


	printf("Testing IntBST\n");

	/////////////////////////////////
	// 1. CREATE THE TREE.
	HIntBST htree;

	// Initialize htree to an empty tree.
	htree=IntBSTCreate();

	// Check that the tree was created.
	if(GUTIsTreeOK(htree) == false) 
		{
		printf("**Unable to create BST Instance.\n");
		}
	else
		{
		printf("Successfully created the BST Instance.\n");
		}

	// Check that there are no nodes in the tree yet.
	if(GUTGetCount(htree->Root)!=0)
		{
		printf("**Bad Count of nodes in empty tree\n");
		return false;
		}
	else
		{
		printf("Tree is successfully initialized with zero nodes.\n");
		}

	/////////////////////////////////
	// 2. Add nodes to the tree and verify the node count.
	// Add the very first node.
	if(IntBSTAdd(htree,10)==false)
		{
		printf("**Unable to add node to BST\n");
		IntBSTDestroy(htree);
		return false;
		}
	else
		{
		printf("Successfully added the very first node (value of 10) to the tree.\n");
		}

	// Check that there's one node in the tree.
	if(GUTGetCount(htree->Root)!=1)
		{
		printf("**Bad Count of nodes in tree with one node.\n");
		IntBSTDestroy(htree);
		return false;
		}
	else
		{
		printf("Tree is successfully counted one nodes.\n");
		}

	/// Add the second node.
	if(IntBSTAdd(htree,20)==false)
		{
		printf("**Unable to add the second node (value 20) to BST\n");
		IntBSTDestroy(htree);
		return false;
		}
	else
		{
		printf("Successfully added the second node (value of 20) to the tree.\n");
		}

	// Check that there's two nodes in the tree.
	if(GUTGetCount(htree->Root)!=2)
		{
		printf("**Bad Count of nodes in tree with two nodes.\n");
		IntBSTDestroy(htree);
		return false;
		}
	else
		{
		printf("Tree is successfully counted two nodes.\n");
		}

	/// Add the third node.
	if(IntBSTAdd(htree,5)==false)
		{
		printf("**Unable to add the third node (value 5) to BST\n");
		IntBSTDestroy(htree);
		return false;
		}
	else
		{
		printf("Successfully added the third node (value of 5) to the tree.\n");
		}

	// Check that there's three nodes in the tree.
	if(GUTGetCount(htree->Root)!=3)
		{
		printf("**Bad Count of nodes in tree with three nodes.\n");
		IntBSTDestroy(htree);
		return false;
		}
	else
		{
		printf("Tree is successfully counted three nodes.\n");
		}

	// Add the fourth node.
	if(IntBSTAdd(htree,12)==false)
		{
		printf("**Unable to add the fourth node (value 12) to BST\n");
		IntBSTDestroy(htree);
		return false;
		}
	else
		{
		printf("Successfully added the fourth node (value of 12) to the tree.\n");
		}

	// Check that there's four nodes in the tree.
	if(GUTGetCount(htree->Root)!=4)
		{
		printf("**Bad Count of nodes in tree with fourth nodes.\n");
		IntBSTDestroy(htree);
		return false;
		}
	else
		{
		printf("Tree is successfully counted four nodes.\n");
		}

	// Add the fifth node.
	if(IntBSTAdd(htree,3)==false)
		{
		printf("**Unable to add the fifth node (value 3) to BST\n");
		IntBSTDestroy(htree);
		return false;
		}
	else
		{
		printf("Successfully added the fifth node (value of 3) to the tree.\n");
		}

	// Check that there's five nodes in the tree.
	if(GUTGetCount(htree->Root)!=5)
		{
		printf("**Bad Count of nodes in tree with five node.\n");
		IntBSTDestroy(htree);
		return false;
		}
	else
		{
		printf("Tree is successfully counted five nodes.\n");
		}

	/////////////////////////////////////////////////
	// 3. Search the tree for a value that isn't there.
	if(IntBSTIsMember(htree, 100) == true)
		{
		printf("**Able to find 100 in the tree. We're not supposed to find a number we didn't add.\n");
		IntBSTDestroy(htree);
		return false;
		}
	else
		{
		printf("Successfully did not find 100 in the tree. (It's not supposed to be there.)\n");
		}
	

	/////////////////////////////////////////////////
	// 4. Search the tree for a value that is there.
	if(IntBSTIsMember(htree, 3) == false)
		{
		printf("**Unable to find 3 in the tree. It should be there.\n");
		IntBSTDestroy(htree);
		return false;
		}
	else
		{
		printf("Successfully found 3 in the tree.\n");
		}

	///////////////////////////////////////
	// 5. Print the values of the tree.
	if(IntBSTPrint(htree) == false)
		{ 
		printf("Something went wrong trying to use IntBSTPrint.");
		return false; 
		}
	else
		{
		printf("Successfully printed the values in the tree.");
		}

	///////////////////////////////////////
	// 6. Delete a node.
	/* Didn't write code to do this yet...It's on the to-do */

	///////////////////////////////////////
	// 7. Destroy the tree.
	if(IntBSTDestroy(htree) == false)
		{ 
		printf("Something went wrong trying to use IntBSTDestroy.");
		return false; 
		}
	else
		{
		printf("Successfully destroyed the tree..");
		}	

	return true;
	}


/////////////////////////////////////////////////
// check if subtree has values greater than value
static bool GUTIsSubTreeLargerThan(int value,struct GIntNode *node)
	{
	if(node==0) { return true; }

	// check if node value is greater than value
	if(node->Value<=value)
		{
		printf("**Found value %d in node which is not greater than %d\n",node->Value,value);
		return false;
		}

	// Recursively check the children
	if(GUTIsSubTreeLargerThan(value,node->Right)==false) { return false; }
	if(GUTIsSubTreeLargerThan(value,node->Left)==false) { return false; }

	return true;
	}


/////////////////////////////////////////////////
// Check if subtree has values smaller than value
static bool GUTIsSubTreeSmallerThan(int value,struct GIntNode *node)
	{
	if(node==0) { return true; }

	// check if node value is grater than value
	if(node->Value>=value)
		{
		printf("**Found value %d in node which is not smaller than %d\n",node->Value,value);
		return false;
		}

	// Recursively check the children
	if(GUTIsSubTreeSmallerThan(value,node->Right)==false) { return false; }
	if(GUTIsSubTreeSmallerThan(value,node->Left)==false) { return false; }

	return true;
	}


/////////////////////////////////////////////////
// Check that the tree handler exists.
static bool GUTIsTreeOK(HIntBST htree)
	{
	if(htree==0)
		{
		printf("**Handle to BST is bad\n");
		return false;
		}

	return true;
	}

/////////////////////////////////////////////////
// Get Total count of nodes
static bool GUTGetCount(struct GIntNode *node)
	{
	if(node==0) { return 0; }
	return GUTGetCount(node->Left)+GUTGetCount(node->Right)+1;
	}
