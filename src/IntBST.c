//v0.2 copyright GRB-Dynamics 20160821U1338
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "IntBST.h"


//*******************************************************
//* Module Elements( Internal to file)
//*  See diagram for Tree structure: /docs/TreeStructure.pdf
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
// Recursively get count of nodes under current node + itself
static int GTreeGetCount(struct GIntNode *node)
	{
	if(node==0) { return 0; }
	return GTreeGetCount(node->Left)+GTreeGetCount(node->Right)+1;
	}

///////////////////////////////////////////////
// Recursively get height of subtree including input node.
static int GTreeGetHeight(struct GIntNode *node)
	{
	if(node == 0) { return 0; }

	int leftHeight = GTreeGetHeight(node->Left);
	int rightHeight = GTreeGetHeight(node->Right);
	
	if(leftHeight > rightHeight)
		{
		return leftHeight+1;
		}	
	else
		{
		return rightHeight+1;
		}

	}
	
//////////////////////////////////////////////
static bool GRotateLeft(struct GIntNode *subtree)
	{
	if(subtree==0) { return false; }

	// My Mistake to check for Right Node
	if(subtree->Right==0) { return false; }
	
	/** Since data is very small, we can move the data around
	We Cannot move the subtree node, as it may be pointed to
	by its own parent node.
	*/

	// Look at image /docs/RotateLeft.pdf
	const int tempdata=subtree->Value;
	subtree->Value=subtree->Right->Value;
	subtree->Right->Value=tempdata;

	struct GIntNode *originalright=subtree->Right;
	subtree->Right=originalright->Right;
	originalright->Right=originalright->Left;
	originalright->Left=subtree->Left;
	subtree->Left=originalright;

	return true;
	}	


//////////////////////////////////////////////
static bool GRotateRight(struct GIntNode *subtree)
	{
	if(subtree==0) { return false; }
	if(subtree->Left==0) { return false; }

	// This should be the reverse of a Left Rotate. 

	// See docs/RotateRight.pdf for a super nice diagram.

	/* (1) */ // Swap the values of A and B
	const int tempdata=subtree->Value;
	subtree->Value=subtree->Left->Value;
	subtree->Left->Value=tempdata;

	/* (2) */ struct GIntNode *originalleft=subtree->Left;	// Create a copy of B, called OL.
	/* (3) */ subtree->Left=originalleft->Left;		// Make A->Left point to C. (B gets lost in space.)
	/* (4) */ originalleft->Left=originalleft->Right;	// Make OL->Right point to D.
	/* (5) */ originalleft->Right=subtree->Right;		// Make OL->Left point to E.
	/* (6) */ subtree->Right=originalleft;			// Make A->Right point to OL.

	// Shouldn't we free up Node B from malloc?

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
// Get the height of the tree.
int IntBSTGetHeight(HIntBST htree)
	{
	if(htree == 0) { return 0; }

	return GTreeGetHeight(htree->Root);
	}


////////////////////////////////////////////////
// Balance the tree using the Day-Stout-Warren algorithm.
bool IntBSTLevelTree(HIntBST htree)
	{
	assert(htree!=0);

	// Helpful resource: https://xuyuanguo.wordpress.com/2013/02/06/dsw-algorithm-balancing-binary-search-tree/
	// 1. Make the tree completely unbalanced (straight) to the right, by doing right rotations on all left children.
	// Should look like:
	// \
	//  \
	//   \
	//    \

	struct GIntNode *currentNode = htree->Root;	// Start at the root.
	int nodecount = 0;				// Count the number of node in the tree. 

	while(currentNode != 0)				// Go through each node from root until the bottom right.
		{
		while(currentNode->Left != 0)		// Call RightRotate on each node until it has no left children.
			{
			GRotateRight(currentNode);
			}
		currentNode = currentNode->Right;	// Update our current node.
		nodecount += 1;				// Add one to our node count.
		}
	
	// Quick test. If the height isn't equal to the number of nodes in the tree, this step failed.
	if(nodecount != IntBSTGetHeight(htree))
		{
		return false;
		}


	// 2. Do enough left rotations for the tree to become balanced.
	// Source: http://www.radford.edu/~mhtay/ITEC360/webpage/Lecture/06_p2_new.pdf
	// It basically goes like this: Do a left rotate on every odd node in the backbone (root = 1).
	// Keep doing that until it's balanced.
	
	int times = nodecount;					// The number of times we rotate the backbone.
	while(times > 1)
		{
		times /= 2;					// Increment the number of times. Every iteration halves the backbone.

		// Do a left rotate on the root.
		GRotateLeft(htree->Root);			// Rotate the root since it's odd.
		struct GIntNode *currentNode = htree->Root;	// This is now the new root (even so don't rotate).

		// Do a left rotate on all the rest of the odd nodes along the backbone.
		for(int i = 0; i < times-1; i++)		// For the length of the backbone...
			{
			GRotateLeft(currentNode->Right);	// Rotate the right of the current node (which will always be odd.)
			currentNode = currentNode->Right;	// Update the current node (which will always be an even one.)
			}		
		}	


	// Quick test. The tree should be balanced. The height of is expected to be log2(# of nodes)
	if(ceil(log2(nodecount)) != IntBSTGetHeight(htree))
		{		
		return false;
		}

	return true;
	}


//**********************************************************
// Unit Testing Code 
//**********************************************************
// Forward reference all the unit tests
static bool GUTMain1(void);
static bool GUTMain2(void);
static bool GUTMain3(void);	// Test GRotateLeft and GRotateRight
static bool GUTMain4(void);	// Test that the tree gets balanced.

////////////////////////////////////////////////////
bool IntBSTUnitTest(void)
	{
	if(GUTMain1()==false) { return false; }
	if(GUTMain2()==false) { return false; }
	if(GUTMain3()==false) { return false; }
	if(GUTMain4()==false) { return false; }
	printf("Testing IntBST : ok\n");
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


//**********************************************************
// Unit Test Code #3
//**********************************************************
// Build tree from diagram /docs/RotateLeft and verify
static bool GUTMain3(void)
	{
	HIntBST htree=IntBSTCreate();
	assert(htree!=0);

	IntBSTAdd(htree,10);
	IntBSTAdd(htree,8);
	IntBSTAdd(htree,12);
	IntBSTAdd(htree,11);
	IntBSTAdd(htree,13);
	
	struct GIntNode *root=htree->Root;
	assert(root!=0 && root->Value==10);
	assert(root->Left!=0 && root->Left->Value==8);
	assert(root->Right!=0 && root->Right->Value==12);
	assert(root->Right->Left!=0 && root->Right->Left->Value==11);
	assert(root->Right->Right!=0 && root->Right->Right->Value==13);

	if(GCheckTree(root)==false)
		{
		fprintf(stderr,"**Bad tree before rotate\n");
		return false;
		}

	if(GRotateLeft(root)==false)
		{
		fprintf(stderr,"**Unable to rotate left\n");
		return false;
		}

	if(GCheckTree(root)==false)
		{
		fprintf(stderr,"**Bad tree after left rotate\n");
		return false;
		}

	// Check if tree values are good
	assert(root!=0 && root->Value==12);
	assert(root->Right!=0 && root->Right->Value==13);
	assert(root->Left!=0 && root->Left->Value==10);
	assert(root->Left->Right!=0 && root->Left->Right->Value==11);
	assert(root->Left->Left!=0 && root->Left->Left->Value==8);


	// Test GRotateRight
	if(GRotateRight(root)==false)
		{
		fprintf(stderr,"**Unable to rotate right\n");
		return false;
		}

	if(GCheckTree(root)==false)
		{
		fprintf(stderr,"**Bad tree after right rotate\n");
		return false;
		}

	// Check if the values are good (they should be exactly the same as before left rotate).
	assert(root!=0 && root->Value==10);
	assert(root->Left!=0 && root->Left->Value==8);
	assert(root->Right!=0 && root->Right->Value==12);
	assert(root->Right->Left!=0 && root->Right->Left->Value==11);
	assert(root->Right->Right!=0 && root->Right->Right->Value==13);

	IntBSTDestroy(htree);
	return true;
	}

//**********************************************************
// Unit Test Code #4
//**********************************************************
// Check that the tree is balanced.
static bool GUTMain4(void)
	{
	// Create a new tree.
	HIntBST htree=IntBSTCreate();
	assert(htree!=0);

	// Add numbers 1 to 100 to tree. Should create a tall tree with all right nodes.
	for(int i = 1; i <= 100; i++)
		{
		IntBSTAdd(htree,i);
		}

	// Get the height of the tree. Should be 100.
	if(IntBSTGetHeight(htree) != 100)
		{
		fprintf(stderr,"**Test Tree original is not expected height of 100.\n");
		IntBSTDestroy(htree);
		return false;
		}
	if(IntBSTGetCount(htree) != 100)
		{
		fprintf(stderr,"**Test Tree original is not expected count of 100.\n");
		IntBSTDestroy(htree);
		return false;
		}

	// Call the balance function.
	bool treeBalanced = IntBSTLevelTree(htree);
	if(treeBalanced == false)
		{
		fprintf(stderr,"**Test Tree could not be balanced.\n");
		IntBSTDestroy(htree);
		return false;
		}

	// Get the height of the new tree. Expected height should be 7.
	int newheight = IntBSTGetHeight(htree);
	if(newheight != 7)
		{
		fprintf(stderr,"**Test Tree balanced is not expected height of 7. The height after calling BalanceTree is %d.\n", newheight);
		IntBSTDestroy(htree);
		return false;
		}

	IntBSTDestroy(htree);

	return true;
	}
