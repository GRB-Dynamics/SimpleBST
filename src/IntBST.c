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
	// Shouldn't these be GIntNode's? Don't they point to other nodes?
	// See the documentation pdf image
	/*
	struct IntNode *Left;
	struct IntNode *Right;
	*/
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
static bool GDeleteTree(struct GIntNode *node)
	{
	// If the node has a left child, call GDeleteTree on it.
	if(node->Left != 0)
		{ GDeleteTree(node->Left); }

	// If the node has a right child, call GDeleteTree on it.
	if(node->Right != 0)
		{ GDeleteTree(node->Right); }

	// Now delete the node.
	// Just freeing it from memory may work?
	free(node);

	return true;
	}


//////////////////////////////////////////////
// Prints the value of a node, then calls PrintNode on it's left and right children if they exist.
// Should work Depth-First.
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
		GDeleteTree(htree->Root); // I think "htree.Root" is what we use to pass a GIntNode? These pointers are killing me.
		}

	// Free the GIntBST Node
	free(htree);

	return false;
	}


//////////////////////////////////////////////
// Add a node to the binary tree. 
bool IntBSTAdd(HIntBST htree,int val)
	{
	/* Fill In */
	// Go through each node of the tree determining whether to go left or right.
	return false;
	}


//////////////////////////////////////////////
// Search the tree for a value.
bool IntBSTIsMember(HIntBST htree,int val)
	{
	// Start at the root node. If the value is equal, return true.
	// If the value is less, look at the left child. If the value is greater, look at the right child. 
	
	// Create a temporary node to traverse the tree to look for the value.
	struct GIntNode *tempnode;

	// Start tempnode off at the root node.
	tempnode = htree->Root;
	
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
		printf("Tree is empty."); 
		return false;
		}

	/*	
	// Otherwise it must have members so print the value of each one.
	else

	** No Need for else
	*/
	
	// Since there aren't queue's or stacks in C...
	// Recursively print the nodes by calling PrintNode on the root.
	GPrintTree(htree->Root);
	printf("\n");
	
	return true;
	}

