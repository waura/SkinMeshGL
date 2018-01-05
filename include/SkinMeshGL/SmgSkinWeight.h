#ifndef _SMGSKINWEIGHT_H_
#define _SMGSKINWEIGHT_H_

#include "stdafx.h"
#include "SmgMat.h"

typedef struct _SmgSkinWeight {
	int nWeights;        //$B%&%'%$%H?t(B
	int* vertexIndices;  //$B%\!<%s$N1F6A$r<u$1$kD:E@$NG[Ns(B
	float* weights;      //$B$=$l$>$l$ND:E@$,<u$1$k%&%'%$%H(B
	SmgMat4 matrixOffset; //$BD:E@$r%\!<%s$N6u4V$K%H%i%s%9%U%)!<%`$9$k9TNs(B
} SmgSkinWeight;


/////////////////////////////////////
/*!
	SmgSkinWeight$B$r=i4|2=$7$F@8@.$9$k(B
	@return 
*/
SmgSkinWeight* CreateSmgSkinWeight();

//////////////////////////////////////
/*!
	SmgSkinWeight$B$r3+J|$9$k(B
	@param[in,out] ppSkinWeight $B3+J|$9$k(Bskinweight
*/
void ReleaseSmgSkinWeight(SmgSkinWeight** ppSkinWeight);

//////////////////////////////////////
/*!
	$BD:E@%$%s%G%C%/%9G[Ns$r:n@.(B
*/
void CreateSmgSkinWeightVertexIndexArr(SmgSkinWeight* pSkinWeight, int nWeights);

//////////////////////////////////////
/*!
	$BD:E@%$%s%G%C%/%9$r3JG<(B
*/
void SetSmgSkinWeightVertexIndex(SmgSkinWeight* pSkinWeight, int index, int vertexindex);

void CreateSmgSkinWeightWeightArr(SmgSkinWeight* pSkinWeight, int nWeights);
void SetSmgSkinWeightWeight(SmgSkinWeight* pSkinWeight, int index, float weight);
#endif //_SMGSKINWEIGHT_H_