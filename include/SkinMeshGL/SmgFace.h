#ifndef _SMGFACE_H_
#define _SMGFACE_H_

#include "SmgVertex.h"

typedef struct _SmgFace{
	int nVertexIndexs;		//$BLL$,;}$DD:E@%$%s%G%C%/%9$N?t(B
	int* arrVertexIndexs;	//$BD:E@HV9fG[Ns(B
	int material_index;     //$BLL$N%^%F%j%"%k$N%$%s%G%C%/%9(B $B%^%F%j%"%k$,L5$$>l9g$O(B-1
	SmgVertex normalVec;	//$BC10LK!@~%Y%/%H%k(B
} SmgFace;

//
void DumpSmgFace(const SmgFace* pFace);

//$B=i4|2=(B
void InitSmgFace(SmgFace* pFace);

/////////////////////
/*!
	$BLL$,;}$DD:E@%G!<%?$r%;%C%H$9$k!#(B
	@param[in,out] pFace $BLL(B
	@parma[in] nVertexIndexs $BD:E@?t(B
	@parma[in] arrVertexIndexs $B%;%C%H$9$kD:E@%$%s%G%C%/%9%G!<%?(B
*/
void SetSmgFace(SmgFace* pFace, int nVertexIndexs, const int* arrVertexIndexs);

//
void ReleaseSmgFaceVertexIndexs(SmgFace* pFace);

#endif