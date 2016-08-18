//v0.1 copyright GRB-Dynamics 20160818R1332
#ifndef IntBST_h
#define IntBST_h

/////////////////////////////////////////////////
#include <stdbool.h>

/////////////////////////////////////////////////
typedef struct GIntBST *HIntBST;

////////////////////////////////////////////////
/*  Creates a Binary Search Tree object with an initial value */
HIntBST IntBSTCreate(int initialval);


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




#endif // IntBST_h

