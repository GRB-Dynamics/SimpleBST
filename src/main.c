#include <stdio.h>
#include "IntBST.h"

////////////////////////////////////
int main(void)
	{
	if(IntBSTUnitTest()==false)
		{
		printf("**Test Failed\n");
		return 1;
		}

	return 0;	
	}
