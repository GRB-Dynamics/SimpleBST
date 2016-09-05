//v0.3 copyright GRB-Dynamics 20160904U2016
//#ifndef IntBST_h
//#define IntBST_h

/////////////////////////////////////////////////
#include <stdbool.h>

/////////////////////////////////////////////////
// Create abstact handle to a binary search tree instance.
typedef struct GIntBST *HIntBST;

////////////////////////////////////////////////
HIntBST IntBSTCreate(void);						// Creates a Binary Search Tree
bool IntBSTDestroy(HIntBST);					// Destroys a Binary Search Tree 
bool IntBSTAdd(HIntBST htree,int val);			// Add an integer to a BST
bool IntBSTIsMember(HIntBST htree,int val);		// Check if val is a member of the BST
bool IntBSTPrint(HIntBST htree);				// Print Out Tree
int IntBSTGetCount(HIntBST htree);				// Find count of items in tree
bool IntBSTLevelTree(HIntBST htree);			// Will create a near complete tree
bool IntBSTUnitTest(void);						// Unit Test Code


// #endif // IntBST_h

