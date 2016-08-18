#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "IntBST.h"

/////////////////////////////////////////////
struct GIntBST
	{
	struct IntBST *Left;
	struct IntBST *Right;
	int Value;
	};


/////////////////////////////////////////////
HIntBST IntBSTCreate(int initialval)
	{
	struct GIntBST *newnode=(struct GIntBST *)malloc(sizeof(struct GIntBST));
	if(newnode==0)
		{
		fprintf(stderr,"Error: Unable to alloc memory\n");
		return 0;
		}

	newnode->Left=0;
	newnode->Right=0;
	newnode->Value=initialval;

	return (HIntBST)newnode;
	}


//////////////////////////////////////////////
bool IntBSTDestroy(HIntBST)
	{
	/* Fill In */
	return false;
	}


//////////////////////////////////////////////
bool IntBSTAdd(HIntBST htree,int val)
	{
	/* Fill In */
	
	return false;
	}


//////////////////////////////////////////////
bool IntBSTIsMember(HIntBST htree,int val)
	{
	/* Fill In */
	return false;
	}


//////////////////////////////////////////////
bool IntBSTPrint(HIntBST htree)
	{
	/* Fill In */
	return false;
	}

