#ifndef _SMGVERTEX_H_
#define _SMGVERTEX_H_

#include "SkinMeshGL/stdafx.h"

typedef struct _SmgVertex {
	double _d[3];
} SmgVertex;

//
void DumpSmgVertex(const SmgVertex* pVertex);

//
void SetSmgVertexVal(SmgVertex* pVertex, double x, double y, double z);
void SetSmgVertexFromArr(SmgVertex* pVertex, double* d_arr);

//
double GetVertexLength(const SmgVertex* v);

//dst = v1 + v2
void CalcAddVertex(SmgVertex* dst, const SmgVertex* v1, const SmgVertex* v2);
//dst = v1 - v2
void CalcSubVertex(SmgVertex* dst, const SmgVertex* v1, const SmgVertex* v2);

//$BE@(Bp1,p2,p3$B$NC10LK!@~%Y%/%H%k$r5a$a$k(B
BOOL CalcNormalVertex(SmgVertex* dst, const SmgVertex* p1, 
					  const SmgVertex* p2, const SmgVertex* p3);

////////////////////////////////////////////////
/*!
	dst$B$K(Bsrc1$B$H(Bsrc2$B$r(Bt:1-t$B$GJ,3d$7$?$H$-$N@~7AJd4V7k2L$r(Bdst$B$KJV$9(B
*/
void CalcLerpVertex(SmgVertex* dst, const SmgVertex* src1,
					const SmgVertex* src2, float fLeapValue);


#endif //_SMGVERTEX_H_