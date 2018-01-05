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

//点p1,p2,p3の単位法線ベクトルを求める
BOOL CalcNormalVertex(SmgVertex* dst, const SmgVertex* p1, 
					  const SmgVertex* p2, const SmgVertex* p3);

////////////////////////////////////////////////
/*!
	dstにsrc1とsrc2をt:1-tで分割したときの線形補間結果をdstに返す
*/
void CalcLerpVertex(SmgVertex* dst, const SmgVertex* src1,
					const SmgVertex* src2, float fLeapValue);


#endif //_SMGVERTEX_H_