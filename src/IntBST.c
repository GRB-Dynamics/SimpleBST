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
//  leftsubtree <= currentnode < rightsubtree  
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
static bool GIntBSTAddNode(int val,struct GIntNode *tree)
	{
	assert(tree!=0);
	
	// Create the newnode with val
	struct GIntNode *newnode = (struct GIntNode *)malloc(sizeof(struct GIntNode));
	if(newnode==0)
		{
		fprintf(stderr,"**Unable to alloc memory\n");
		return false;
		}
		
	newnode->Value = val;
	newnode->Left = 0;
	newnode->Right = 0;

	for(struct GIntNode *p=tree; ; )
		{
		if(val <= p->Value)
			{
			if(p->Left!=0){ p=p->Left; continue; }
			p->Left = newnode;  return true;
			}
		else
			{
			if(p->Right!=0) { p=p->Right; continue; }
			p->Right = newnode; return true;
			}
		}
	}


////////////////////////////////////////////
// Deletes a node in a BST and calls itself to delete child nodes.
static void GDeleteTree(struct GIntNode *node)
	{
	if(node==0) { return; }
	GDeleteTree(node->Left);
	GDeleteTree(node->Right);
	
	// Clean up all data from node
	node->Left=0;
	node->Right=0;
	node->Value=0;
	
	free(node);
	}


//////////////////////////////////////////////
// print the values in the tree.
static void GPrintTree(struct GIntNode *node)
	{
	if(node==0) { return; }
	GPrintTree(node->Left);
	printf("%d ", node->Value);
	GPrintTree(node->Right);
	}
	
	
///////////////////////////////////////////////
static int GTreeGetCount(struct GIntNode *node)
	{
	if(node==0) { return 0; }
	return GTreeGetCount(node->Left)+GTreeGetCount(node->Right)+1;
	}
	
	
//////////////////////////////////////////////
static bool GRotateLeft(struct GIntNode *subtree)
	{
	if(subtree==0) { return false; }
	if(subtree->Left==0) { return false; }
	
	/** Since data is very small, we can move the data around */

	// Maybe we should check that this rotate is actually allowable?
	// As in, it won't break the rest of the tree.

	// Do the actual rotate - by switching the variable values.
	int temp = subtree->Value;
	subtree->Value = subtree->Left->Value;
	subtree->Left->Value = temp;

	return true;
	}	


//////////////////////////////////////////////
static bool GRotateRight(struct GIntNode *subtree)
	{
	if(subtree==0) { return false; }
	if(subtree->Right==0) { return false; }
	
	/** Since data is very small, we can move the data around */


	// Maybe we should check that this rotate is actually allowable?
	// As in, it won't break the rest of the tree.

	// Do the actual rotate - by switching the variable values.
	int temp = subtree->Value;
	subtree->Value = subtree->Right->Value;
	subtree->Right->Value = temp;

	return true;
	}	


////////////////////////////////////////////////
static bool GCheckTree(struct GIntNode *subtree)
	{
	if(subtree==0) { return true; }
	
	// Check left side of tree
	if(subtree->Left!=0 && subtree->Left->Value > subtree->Value)
		{
		fprintf(stderr,"**Error: Node %d has left value %d\n",subtree->Value
				,subtree->Left->Value);
		return false;
		}
		
	// Check right side of tree
	if(subtree->Right!=0 && subtree->Right->Value <= subtree->Value )
		{
		fprintf(stderr,"**Error: Node %d has right value %d\n",subtree->Value
				,subtree->Right->Value);
		return false;		
		}
		
	if(GCheckTree(subtree->Left)==false) { return false; }
	if(GCheckTree(subtree->Right)==false) { return false; }
	
	return true;
	}

//*******************************************************
//* Module Interface Functions
//*******************************************************
HIntBST IntBSTCreate(void)
	{
	struct GIntBST *newnode=(struct GIntBST *)malloc(sizeof(struct GIntBST));
	if(newnode==0)
		{
		fprintf(stderr,"Error: Unable to alloc memory\n");
		return 0;
		}
	
	newnode->Root=0;
	return (HIntBST)newnode;
	}


//////////////////////////////////////////////
// Destroy an entire binary tree.
bool IntBSTDestroy(HIntBST htree)
	{
	assert(htree!=0);
	GDeleteTree(htree->Root);
	free(htree);
	return true;
	}



//////////////////////////////////////////////
// Add a node to the binary tree. 
bool IntBSTAdd(HIntBST htree,int val)
	{
	assert(htree!=0);
	
	if(htree->Root == 0)
		{
		// Create the node and allocate space.
		struct GIntNode *newnode = (struct GIntNode *)malloc(sizeof(struct GIntNode));
		if(newnode==0)
			{
			fprintf(stderr,"**Unable to alloc memory\n");
			return false;
			}
			
		newnode->Value = val;
		newnode->Left = 0;
		newnode->Right = 0;
		htree->Root = newnode;
		
		return true;
		}

	return GIntBSTAddNode(val, htree->Root);
	}


//////////////////////////////////////////////
// Search the tree for a value.
bool IntBSTIsMember(HIntBST htree,int val)
	{
	assert(htree!=0);
	struct GIntNode *tempnode=htree->Root;
	
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
	assert(htree!=0);	

	GPrintTree(htree->Root);
	printf("\n");
	return true;
	}


///////////////////////////////////////////////
int IntBSTGetCount(HIntBST htree)
	{
	assert(htree!=0);
	return GTreeGetCount(htree->Root);
	}
	

////////////////////////////////////////////////
bool IntBSTLevelTree(HIntBST htree)
	{
	assert(htree!=0);
	
	// See https://en.wikipedia.org/wiki/Day%E2%80%93Stout%E2%80%93Warren_algorithm
	
	return false;
	}


//**********************************************************
// Unit Testing Code 
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
	if(htree == 0) 
		{
		fprintf(stderr,"**Unable to create BST Instance.\n");
		return false;
		}

	// Check that there are no nodes in the tree yet.
	if(IntBSTGetCount(htree)!=0)
		{
		printf("**Bad Count of nodes in empty tree\n");
		return false;
		}
		
	if(GCheckTree(htree->Root)==false) { return false; }		

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
		
	if(GCheckTree(htree->Root)==false) { return false; }
	
	/// Add the second node.
	if(IntBSTAdd(htree,20)==false)
		{
		fprintf(stderr,"**Unable to add the second node (value 20) to BST\n");
		IntBSTDestroy(htree);
		return false;
		}

	if(GCheckTree(htree->Root)==false) { return false; }


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
		
	if(GCheckTree(htree->Root)==false) { return false; }		


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

	if(GCheckTree(htree->Root)==false) { return false; }
	
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
		
	if(GCheckTree(htree->Root)==false) { return false; }		

	// Print the current tree
	printf("Nodes in tree so far: ");
	IntBSTPrint(htree);

	/////////////////////////////////////////////////
	// 3. Search the tree for a value that isn't there.
	if(IntBSTIsMember(htree, 100) == true)
		{
		fprintf(stderr,"**Able to find 100 in the tree. We're not supposed to find a number we didn't add.\n");
		IntBSTDestroy(htree);
		return false;
		}
		
	if(GCheckTree(htree->Root)==false) { return false; }		
	

	/////////////////////////////////////////////////
	// 4. Search the tree for a value that is there.
	if(IntBSTIsMember(htree, 3) == false)
		{
		fprintf(stderr,"**Unable to find 3 in the tree. It should be there.\n");
		IntBSTDestroy(htree);
		return false;
		}

	///////////////////////////////////////
	// 5. Print the values of the tree.
	printf("Calling IntBSTPrint. Check if the following values are expected: \n");
	if(IntBSTPrint(htree) == false)
		{ 
		printf("Something went wrong trying to use IntBSTPrint.\n");
		return false; 
		}

	if(IntBSTDestroy(htree) == false)
		{ 
		printf("Something went wrong trying to use IntBSTDestroy.\n");
		return false; 
		}

	return true;
	}




//**********************************************************
// Unit Test Code #2
//**********************************************************
static bool GUTMain2(void)
	{
	HIntBST htree=IntBSTCreate();
	if(htree==0)
		{
		fprintf(stderr,"**Unable to create an empty tree\n");
		return false;
		}
		
	// 113 is a prime number - checked with www.archimedes-lab.org/primOmatic.html
	for(int i=0;i<113;++i)
		{
		// 13 and 113 are relatively prime
		const int val =(13*i)%113;
		if(IntBSTAdd(htree,val)==false)
			{
			fprintf(stderr,"Unable to add number to tree");
			return false;
			}

		if(GCheckTree(htree->Root)==false) { return false; }
		}
		
	for(int i=0;i<113;++i)
		{
		if(IntBSTIsMember(htree,i)==false)
			{
			fprintf(stderr,"**Missing member in tree");
			return false;
			}
		}
		
	IntBSTDestroy(htree);
	return true;
	}

