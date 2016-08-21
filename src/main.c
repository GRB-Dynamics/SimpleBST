#include <stdio.h>
#include "IntBST.h"

////////////////////////////////////
int main(void)
	{
	// Create an HIntBST variable from the IntBST.h file.
	HIntBST htree;
	// Initialize htree to an empty tree.
	htree=IntBSTCreate();
	
	// Add nodes to the tree.
	IntBSTAdd(htree,10);
	IntBSTAdd(htree,20);
	IntBSTAdd(htree,5);

	// Print the values of the tree.
	IntBSTPrint(htree);

	// Destroy the tree.
	IntBSTDestroy(htree);

	return 0;	
	}
