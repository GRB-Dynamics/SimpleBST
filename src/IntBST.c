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
//////////////////////////////////////////////
// Recursively go through tree to find where a node belongs.
// If it belongs, add it.
static bool GIntBSTAddNode(int val,struct GIntNode *node)
	{
	bool valueWasAdded = false;
	
	// Check if the value is equal to current node.
	// Means we can't add it so return false.
	if(node->Value == val)
		{ return false; }

	// If the value is smaller...
	if(node->Value > val)
		{
		// If the left child is empty, add the node there.
		if(node->Left == 0)
			{  

			// Create the node and allocate space.
			struct GIntNode *newnode = (struct GIntNode *)malloc(sizeof(struct GIntNode));
			newnode->Value = val;
			newnode->Left = 0;
			newnode->Right = 0;

			// Make the current node point to the new node.
			node->Left = newnode;

			return true; // Note: 90210
			}
		// The left child isn't empty, so continue traversing the tree.
		else
			{ valueWasAdded = GIntBSTAddNode(val,node->Left); }
		}
	// If the value is larger...
	else
		{
		// If the right child is empty, add the node there.
		if(node->Right == 0)
			{  
			// Create the node and allocate space.
			struct GIntNode *newnode = (struct GIntNode *)malloc(sizeof(struct GIntNode));
			newnode->Value = val;
			newnode->Left = 0;
			newnode->Right = 0;

			// Make the current node point to the new node.
			node->Right = newnode;
			
			return true;
			}
		// The left child isn't empty, so continue traversing the tree.
		else
			{ valueWasAdded = GIntBSTAddNode(val,node->Right); }
		}


	return valueWasAdded;
	}


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
	// If the tree is empty add the first node to the root.
	if(htree->Root == 0)
		{
		// Create the node and allocate space.
		struct GIntNode *newnode = (struct GIntNode *)malloc(sizeof(struct GIntNode));
		newnode->Value = val;
		newnode->Left = 0;
		newnode->Right = 0;

		// Make the current node point to the new node.
		htree->Root = newnode;
		
		return true;
		}

	// Otherwise recursively search the tree for where the value should go.
	return GIntBSTAddNode(val, htree->Root);
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
// Forward reference all the unit tests
static bool GUTMain1(void);
static bool GUTMain2(void);

////////////////////////////////////////////////////
bool IntBSTUnitTest(void)
	{
	if(GUTMain1()==false) { return false; }
	if(GUTMain2()==false) { return false; }
	return true;
	}


//**********************************************************
// Unit Test Code #1
//**********************************************************
static bool GUTIsSubTreeLargerThan(int value,struct GIntNode *node);
static bool GUTIsSubTreeSmallerThan(int value,struct GIntNode *node);
static bool GUTIsTreeOK(HIntBST htree);
static bool GUTGetCount(struct GIntNode *node);


////////////////////////////////////////////////
// Run a unit test to check the functions in this file.
static bool GUTMain1(void)
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
	///// ADD NODE 1
	// Add it.
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
		printf("Successfully counted one nodes.\n");
		}

	// Print the current tree (should only be one node.)
	printf("Nodes in tree so far: ");
	IntBSTPrint(htree);

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
/*
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
*/

	// Print the current tree
	printf("Nodes in tree so far: ");
	IntBSTPrint(htree);


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
/*
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
*/
	// Print the current tree
	printf("Nodes in tree so far: ");
	IntBSTPrint(htree);

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
/*
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
*/
	// Print the current tree
	printf("Nodes in tree so far: ");
	IntBSTPrint(htree);

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

	// Print the current tree
	printf("Nodes in tree so far: ");
	IntBSTPrint(htree);
/*
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
*/
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
		printf("Something went wrong trying to use IntBSTPrint.\n");
		return false; 
		}
	else
		{
		printf("Successfully printed the values in the tree.\n");
		}

	///////////////////////////////////////
	// 6. Delete a node.
	/* Didn't write code to do this yet...It's on the to-do */

	///////////////////////////////////////
	// 7. Destroy the tree.
	if(IntBSTDestroy(htree) == false)
		{ 
		printf("Something went wrong trying to use IntBSTDestroy.\n");
		return false; 
		}
	else
		{
		printf("Successfully destroyed the tree.\n");
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


//**********************************************************
// Unit Test Code #2
//**********************************************************
static bool GUTMain2(void)
	{
	/* Fill More Unit Tests */
	return true;
	}

