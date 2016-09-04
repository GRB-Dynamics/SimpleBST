//v0.2 copyright GRB-Dynamics 20160821U1338
//#ifndef IntBST_h
//#define IntBST_h

/////////////////////////////////////////////////
#include <stdbool.h>

/////////////////////////////////////////////////
// Create abstact handle to a binary search tree instance.
typedef struct GIntBST *HIntBST;

////////////////////////////////////////////////
/*  Creates a Binary Search Tree */
HIntBST IntBSTCreate(void);


////////////////////////////////////////////////
/*  Destroys a Binary Search Tree   */
bool IntBSTDestroy(HIntBST);


////////////////////////////////////////////////
/*  Add an integer to a BST  */
bool IntBSTAdd(HIntBST htree,int val);


///////////////////////////////////////////////
/*  Check if val is a member of the BST */
bool IntBSTIsMember(HIntBST htree,int val);


//////////////////////////////////////////////
/*  Print Out Tree  */
bool IntBSTPrint(HIntBST htree);


//////////////////////////////////////////////
// Find count of items in tree
int IntBSTGetCount(HIntBST htree);


//////////////////////////////////////////////
// Will create a near complete tree
bool IntBSTLevelTree(HIntBST htree);


//////////////////////////////////////////////
//  Unit Test Code
bool IntBSTUnitTest(void);


// #endif // IntBST_h

