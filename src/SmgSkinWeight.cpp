#include "SkinMeshGL/SmgSkinWeight.h"

/////////////////////////////////////
/*!
	SmgSkinWeightを初期化して生成する
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
	SmgSkinWeightを開放する
	@param[in,out] ppSkinWeight 開放するskinweight
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
	頂点インデックス配列を作成
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
	頂点インデックスを格納
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
