#ifndef _SMGBONECOMBINATION_H_
#define _SMGBONECOMBINATION_H_

#include "stdafx.h"

typedef struct _SmgBoneCombination {
	unsigned long AttribId; //$B%^%F%j%"%k(BID
	unsigned long VertexStart; //$BD:E@3+;O%$%s%G%C%/%9(B
	unsigned long VertexCount; //$BD:E@?t(B
	unsigned long *BoneId; //$BD:E@G[Ns%$%s%G%C%/%9(B
} SmgBoneCombination;

#endif //_SMGBONECOMBINATION_H_