#include <stdio.h>
#include "IntBST.h"

////////////////////////////////////
int main(void)
	{
	HIntBST htree;
	htree=IntBSTCreate();

	IntBSTAdd(htree,10);
	IntBSTAdd(htree,20);
	IntBSTAdd(htree,5);

	
	IntBSTPrint(htree);

	IntBSTDestroy(htree);

	return 0;	
	}
