#ifndef _SMGCOORDS_H_
#define _SMGCOORDS_H_

#include "stdafx.h"

typedef struct _SmgCoords {
	double u, v;
} SmgCoords;

void DumpSmgCoords(const SmgCoords* pCoords);

#endif //_SMGCOORDS_H_