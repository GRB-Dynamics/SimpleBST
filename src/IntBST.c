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

	return false;
	}


//////////////////////////////////////////////
// Add a node to the binary tree. 
bool IntBSTAdd(HIntBST htree,int val)
	{
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
				}
			// The right child isn't empty, so continue traversing the tree.
			else
				{ tempnode = tempnode->Right; }
			}
		}

	// Why are these functions bool and not void? Return true if the function is successful, false if something goes wrong?
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
		printf("Tree is empty."); 
		return false;
		}
	
	// Recursively print the nodes by calling PrintNode on the root.
	GPrintTree(htree->Root);
	printf("\n");
	
	return true;
	}

