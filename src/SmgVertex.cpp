#include "SkinMeshGL/SmgVertex.h"


//
void DumpSmgVertex(const SmgVertex *pVertex)
{
	if(!pVertex) return;
	printf("x=%f y=%f z=%f\n", pVertex->_d[0], pVertex->_d[1], pVertex->_d[2]);
}

void SetSmgVertexVal(SmgVertex* pVertex, double x, double y, double z)
{
	if(pVertex){
		pVertex->_d[0] = x;
		pVertex->_d[1] = y;
		pVertex->_d[2] = z;
	}
}

void SetSmgVertexFromArr(SmgVertex* pVertex, double* d_arr)
{
	if(pVertex){
		int i;
		for(i=0; i<3; i++){
			pVertex->_d[i] = d_arr[i];
		}
	}
}

double GetVertexLength(const SmgVertex* v)
{
	return sqrt(v->_d[0] * v->_d[0] +
		v->_d[1] * v->_d[1] +
		v->_d[2] * v->_d[2] );
}

//dst = v1 + v2
void CalcAddVertex(SmgVertex* dst, const SmgVertex *v1, const SmgVertex *v2)
{
	int i;
	for(i=0; i<3; i++){
		dst->_d[i] = v1->_d[i] + v2->_d[i];
	}
}

//dst = v1 - v2
void CalcSubVertex(SmgVertex* dst, const SmgVertex *v1, const SmgVertex *v2)
{
	int i;
	for(i=0; i<3; i++){
		dst->_d[i] = v1->_d[i] - v2->_d[i];
	}
}

//点v1,v2,v3の単位法線ベクトルを求める
BOOL CalcNormalVertex(SmgVertex* dst, const SmgVertex* p1,
					  const SmgVertex* p2, const SmgVertex* p3)
{
	int i;
	SmgVertex v1, v2;
	SmgVertex cross;
	double length;
	CalcSubVertex(&v1, p1, p2);
	CalcSubVertex(&v2, p3, p2);

	cross._d[0] = v2._d[1] * v1._d[2] - v2._d[2] * v1._d[1];
	cross._d[1] = v2._d[2] * v1._d[0] - v2._d[0] * v1._d[2];
	cross._d[2] = v2._d[0] * v1._d[1] - v2._d[1] * v1._d[0];

	length = GetVertexLength( &cross );

	if(length == 0.0){
		return FALSE;
	}

	for(i=0; i<3; i++){
		dst->_d[i] = cross._d[i] / length;
	}

	return TRUE;
}

////////////////////////////////////////////////
/*!
	dstにsrc1とsrc2をt:1-tで分割したときの線形補間結果をdstに返す
*/
void CalcLerpVertex(SmgVertex* dst, const SmgVertex* src1,
					const SmgVertex* src2, float fLeapValue)
{
	dst->_d[0] = (src2->_d[0] - src1->_d[0])*fLeapValue + src1->_d[0];
	dst->_d[1] = (src2->_d[1] - src1->_d[1])*fLeapValue + src1->_d[1];
	dst->_d[2] = (src2->_d[2] - src1->_d[2])*fLeapValue + src1->_d[2];
}