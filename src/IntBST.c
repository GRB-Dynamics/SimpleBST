//v0.2 copyright GRB-Dynamics 20160821U1338
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "IntBST.h"

/////////////////////////////////////////////
struct GIntNode
	{
	struct IntNode *Left;
	struct IntNode *Right;
	int Value;
	};


/////////////////////////////////////////////
struct GIntBST
	{
	struct GIntNode *Root;
	};


/////////////////////////////////////////////
HIntBST IntBSTCreate(void)
	{
	struct GIntBST *newnode=(struct GIntBST *)malloc(sizeof(struct GIntBST));
	if(newnode==0)
		{
		fprintf(stderr,"Error: Unable to alloc memory\n");
		return 0;
		}
	
	// Empty Node List
	newnode->Root=0;

	return (HIntBST)newnode;
	}


//////////////////////////////////////////////
bool IntBSTDestroy(HIntBST htree)
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

