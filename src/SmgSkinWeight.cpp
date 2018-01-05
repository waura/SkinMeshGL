#include "SkinMeshGL/SmgSkinWeight.h"

/////////////////////////////////////
/*!
	SmgSkinWeight$B$r=i4|2=$7$F@8@.$9$k(B
	@return 
*/
SmgSkinWeight* CreateSmgSkinWeight()
{
	SmgSkinWeight* psw = (SmgSkinWeight*) malloc(sizeof(SmgSkinWeight));
	memset(psw, 0, sizeof(SmgSkinWeight));
	return psw;
}

//////////////////////////////////////
/*!
	SmgSkinWeight$B$r3+J|$9$k(B
	@param[in,out] ppSkinWeight $B3+J|$9$k(Bskinweight
*/
void ReleaseSmgSkinWeight(SmgSkinWeight** ppSkinWeight)
{
	if(*ppSkinWeight){
		if((*ppSkinWeight)->vertexIndices){
			free((*ppSkinWeight)->vertexIndices);
		}
		if((*ppSkinWeight)->weights){
			free((*ppSkinWeight)->weights);
		}

		free(*ppSkinWeight);
		(*ppSkinWeight) = NULL;
	}
}

//////////////////////////////////////
/*!
	$BD:E@%$%s%G%C%/%9G[Ns$r:n@.(B
*/
void CreateSmgSkinWeightVertexIndexArr(SmgSkinWeight* pSkinWeight, int nWeights)
{
	if(pSkinWeight){
		pSkinWeight->nWeights = nWeights;
		pSkinWeight->vertexIndices = (int*) malloc(sizeof(int) * nWeights);
	}
}

//////////////////////////////////////
/*!
	$BD:E@%$%s%G%C%/%9$r3JG<(B
*/
void SetSmgSkinWeightVertexIndex(SmgSkinWeight* pSkinWeight, int index, int vertexindex)
{
	if(pSkinWeight){
		pSkinWeight->vertexIndices[index] = vertexindex;
	}
}

void CreateSmgSkinWeightWeightArr(SmgSkinWeight* pSkinWeight, int nWeights)
{
	if(pSkinWeight){
		pSkinWeight->nWeights = nWeights;
		pSkinWeight->weights = (float*) malloc(sizeof(float) * nWeights);
	}
}

void SetSmgSkinWeightWeight(SmgSkinWeight* pSkinWeight, int index, float weight)
{
	if(pSkinWeight){
		pSkinWeight->weights[index] = weight;
	}
}
