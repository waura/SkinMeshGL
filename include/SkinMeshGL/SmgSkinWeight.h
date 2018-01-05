#ifndef _SMGSKINWEIGHT_H_
#define _SMGSKINWEIGHT_H_

#include "stdafx.h"
#include "SmgMat.h"

typedef struct _SmgSkinWeight {
	int nWeights;        //ウェイト数
	int* vertexIndices;  //ボーンの影響を受ける頂点の配列
	float* weights;      //それぞれの頂点が受けるウェイト
	SmgMat4 matrixOffset; //頂点をボーンの空間にトランスフォームする行列
} SmgSkinWeight;


/////////////////////////////////////
/*!
	SmgSkinWeightを初期化して生成する
	@return 
*/
SmgSkinWeight* CreateSmgSkinWeight();

//////////////////////////////////////
/*!
	SmgSkinWeightを開放する
	@param[in,out] ppSkinWeight 開放するskinweight
*/
void ReleaseSmgSkinWeight(SmgSkinWeight** ppSkinWeight);

//////////////////////////////////////
/*!
	頂点インデックス配列を作成
*/
void CreateSmgSkinWeightVertexIndexArr(SmgSkinWeight* pSkinWeight, int nWeights);

//////////////////////////////////////
/*!
	頂点インデックスを格納
*/
void SetSmgSkinWeightVertexIndex(SmgSkinWeight* pSkinWeight, int index, int vertexindex);

void CreateSmgSkinWeightWeightArr(SmgSkinWeight* pSkinWeight, int nWeights);
void SetSmgSkinWeightWeight(SmgSkinWeight* pSkinWeight, int index, float weight);
#endif //_SMGSKINWEIGHT_H_