#ifndef _SMGMESH_H_
#define _SMGMESH_H_

#include "stdafx.h"
#include "SmgVertex.h"
#include "SmgCoords.h"
#include "SmgFace.h"
#include "SmgMaterial.h"
#include "SmgImg.h"
#include "SmgSkinInfo.h"
#include "SmgBoneCombination.h"

#define DRAW_POLY 0
#define DRAW_WILE 1

typedef struct _SmgMesh {
	char* name;           //メッシュの名前
	int nVertex;          //頂点の数
	SmgVertex* arrVertex; //頂点配列
	SmgVertex* arrNormal;
	SmgCoords* arrTextureCoords; //頂点のテスクチャUV座標
	int nFaces;                  //面の数
	SmgFace* arrFace;            //面配列
	int nMaterials;              //マテリアルの個数
	SmgMaterial* arrMaterial;    //マテリアル配列
	BOOL isMakedNormalVertex;    //法線を作成済みか？
	SmgSkinInfo* pSkinInfo;      //スキンメッシュ情報
	SmgBoneCombination* arrBoneCombination; //
}SmgMesh;

///////////////////////////////////
/*!
	メッシューデータをダンプする
	@param[in] pMesh ダンプされるメッシュ
*/
void DumpSmgMesh(const SmgMesh* pMesh);

///////////////////////////////////
/*!
	メッシュを生成して返す
	@return 生成したメッシュへのポインタ
*/
SmgMesh* CreateSmgMesh();

///////////////////////////////////
/*!
	メッシュを開放する
	@param[in,out] pMesh 開放するメッシュへのポインタ
*/
void ReleaseSmgMesh(SmgMesh** pMesh);

///////////////////////////////////
/*!
	メッシュの名前をつける
	@param[in,out] pMesh メッシュへのポインタ
	@param[in] name つける名前
*/
void SetSmgMeshName(SmgMesh* pMesh, const char* name);

///////////////////////////////////
/*!
	メッシュが保持する頂点配列のサイズをセットする。
*/
void CreateSmgMeshVertexArr(SmgMesh* pMesh, int nVertex);

////////////////////////////////////
/*!
	メッシュが保持する頂点をセットする
*/
void SetSmgMeshVertex(SmgMesh* pMesh, int index, double x, double y, double z);

void GetSmgMeshVertex(SmgMesh* pMesh, int index, double* dst);

/////////////////////////////////////
/*!
	テスクチャUV座標配列作成
	@param[in,out] pMesh
*/
void CreateSmgMeshTextureCoordsArr(SmgMesh* pMesh);

/////////////////////////////////////
/*!
	テスクチャUV座標をセット
	@param[in] pMesh
	@param[in] index
	@param[in] u
	@param[in] v
*/
void SetSmgMeshTextureCoords(SmgMesh* pMesh, int index, double u, double v);

/////////////////////////////////////
/*!
	メッシュが保持する面配列のサイズをセットする。
*/
void CreateSmgMeshFaceArr(SmgMesh* pMesh, int nFaces);

//////////////////////////////////////
/*!
	メッシュが保持する面のデータをセットする
*/
void SetSmgMeshFace(SmgMesh* pMesh, int index, int n_ver, int* ver);

///////////////////////////////////////
/*!
	面のマテリアルを指定する。
*/
void SetSmgMeshFaceMaterialIndex(SmgMesh* pMesh, int face_index, int material_index);

//////////////////////////////////////
/*!
	メッシュが保持するマテリアル配列のサイズをセットする
*/
void CreateSmgMeshMaterialArr(SmgMesh* pMesh, int nMaterials);

///////////////////////////////////////
/*!
	メッシュが保持するマテリアルのデータをセット
*/
void SetSmgMeshMaterial(SmgMesh* pMesh, int index, const SmgMaterial* pMaterial);

///////////////////////////////////////
/*!
	スキンウェイトの追加
*/
void AddSmgMeshSkinWeight(SmgMesh* pMesh, SmgSkinWeight* pSkinWeight);

///////////////////////////////////////
/*!
	法線が作成されていない場合作成する
	@param[in] pMesh;
*/
void MakeSmgMeshFaceNormal(SmgMesh* pMesh);

void MakeSmgMeshVertexNormal(SmgMesh* pMesh);

////////////////////////////////////////
/*!
	ボーンコンビネーションの作成
*/
void MakeSmgMeshBoneCombination(SmgMesh* pMesh);

////////////////////////////////////////
/*!
	テスクチャの作成
*/
void GenSmgMeshTexture(SmgMesh* pMesh);

///////////////////////////////////////
/*!
	OpenGLによるフレームの描画
	@param[in] pMesh 描画するメッシュ
*/
void DrawSmgMeshGL(SmgMesh* pMesh, int draw_mode);

#endif