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




// #endif // IntBST_h

