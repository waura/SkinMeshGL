#ifndef _SMGFACE_H_
#define _SMGFACE_H_

#include "SmgVertex.h"

typedef struct _SmgFace{
	int nVertexIndexs;		//面が持つ頂点インデックスの数
	int* arrVertexIndexs;	//頂点番号配列
	int material_index;     //面のマテリアルのインデックス マテリアルが無い場合は-1
	SmgVertex normalVec;	//単位法線ベクトル
} SmgFace;

//
void DumpSmgFace(const SmgFace* pFace);

//初期化
void InitSmgFace(SmgFace* pFace);

/////////////////////
/*!
	面が持つ頂点データをセットする。
	@param[in,out] pFace 面
	@parma[in] nVertexIndexs 頂点数
	@parma[in] arrVertexIndexs セットする頂点インデックスデータ
*/
void SetSmgFace(SmgFace* pFace, int nVertexIndexs, const int* arrVertexIndexs);

//
void ReleaseSmgFaceVertexIndexs(SmgFace* pFace);

#endif