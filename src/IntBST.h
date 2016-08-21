//v0.2 copyright GRB-Dynamics 20160821U1338
//#ifndef IntBST_h
//#define IntBST_h

/////////////////////////////////////////////////
#include <stdbool.h>

/////////////////////////////////////////////////
// A structure for our binary tree. 
// It's a...pointer called HIntBST which is made up of GIntBST root node
/*
	This is subtle example of encapsulation in C.  By creating a pointer
	to some structure, we are creating an opaque handle to the internal
	structure of GIntBST.  Call the IntBST.h and IntBST.c a module(a unit of code)
	that you will use in a larger project.  When we use a module, all we 
	have to do is include the header file associated with the module(ie IntBST.h)
	
	Your comment that 
		"It's a...pointer called HIntBST which is made up of GIntBST root node"
	should not be here.  We are purposely hiding the implementation details from
	the user of the module.  The user can only use the functions below.

	This idea is sometimes called loose coupling of code.
	
	A better comment would be:  Create abstact handle to a binary search tree instance.

	In the next commit: erase this comment
*/
typedef struct GIntBST *HIntBST;

////////////////////////////////////////////////
/*  Creates a Binary Search Tree object with an initial value */
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

