//v0.2 copyright GRB-Dynamics 20160821U1338
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "IntBST.h"

/////////////////////////////////////////////
// Our node for the tree. Contains left child, right child, and the data itself.
struct GIntNode
	{
	struct IntNode *Left;
	struct IntNode *Right;
	int Value;
	};


/////////////////////////////////////////////
// A special node that serves as the root of the tree.
struct GIntBST
	{
	struct GIntNode *Root;
	};


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
	/* Fill In */
	// To-do:
	// Normally if this was C# we could just destroy the root node and garbage cleanup would destroy the unreachable children.
	// But I'm guessing since C has memory issues we need to go through and destroy each child node?

	/*
		The simplist code is a recursive deletion of the tree. 

		you should emplement a function called
		
		static bool GDeleteTree(struc GIntNode *node);

		The static prefix is to make sure that the function is in inaccessable
		to anyone using the function outside this file.
	*/
	return false;
	}


//////////////////////////////////////////////
// Add a node to the binary tree. 
bool IntBSTAdd(HIntBST htree,int val)
	{
	/* Fill In */
	// Go through each node of the tree determining whether to go left or right.
	// 3 cases...
	return false;
	}


//////////////////////////////////////////////
// Search the tree for a value.
bool IntBSTIsMember(HIntBST htree,int val)
	{
	/* Fill In */
	return false;
	}


//////////////////////////////////////////////
// Print all members of the tree.
bool IntBSTPrint(HIntBST htree)
	{
	/* Fill In */
	return false;
	}

