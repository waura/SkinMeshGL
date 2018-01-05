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
	char* name;           //$B%a%C%7%e$NL>A0(B
	int nVertex;          //$BD:E@$N?t(B
	SmgVertex* arrVertex; //$BD:E@G[Ns(B
	SmgVertex* arrNormal;
	SmgCoords* arrTextureCoords; //$BD:E@$N%F%9%/%A%c(BUV$B:BI8(B
	int nFaces;                  //$BLL$N?t(B
	SmgFace* arrFace;            //$BLLG[Ns(B
	int nMaterials;              //$B%^%F%j%"%k$N8D?t(B
	SmgMaterial* arrMaterial;    //$B%^%F%j%"%kG[Ns(B
	BOOL isMakedNormalVertex;    //$BK!@~$r:n@.:Q$_$+!)(B
	SmgSkinInfo* pSkinInfo;      //$B%9%-%s%a%C%7%e>pJs(B
	SmgBoneCombination* arrBoneCombination; //
}SmgMesh;

///////////////////////////////////
/*!
	$B%a%C%7%e!<%G!<%?$r%@%s%W$9$k(B
	@param[in] pMesh $B%@%s%W$5$l$k%a%C%7%e(B
*/
void DumpSmgMesh(const SmgMesh* pMesh);

///////////////////////////////////
/*!
	$B%a%C%7%e$r@8@.$7$FJV$9(B
	@return $B@8@.$7$?%a%C%7%e$X$N%]%$%s%?(B
*/
SmgMesh* CreateSmgMesh();

///////////////////////////////////
/*!
	$B%a%C%7%e$r3+J|$9$k(B
	@param[in,out] pMesh $B3+J|$9$k%a%C%7%e$X$N%]%$%s%?(B
*/
void ReleaseSmgMesh(SmgMesh** pMesh);

///////////////////////////////////
/*!
	$B%a%C%7%e$NL>A0$r$D$1$k(B
	@param[in,out] pMesh $B%a%C%7%e$X$N%]%$%s%?(B
	@param[in] name $B$D$1$kL>A0(B
*/
void SetSmgMeshName(SmgMesh* pMesh, const char* name);

///////////////////////////////////
/*!
	$B%a%C%7%e$,J];}$9$kD:E@G[Ns$N%5%$%:$r%;%C%H$9$k!#(B
*/
void CreateSmgMeshVertexArr(SmgMesh* pMesh, int nVertex);

////////////////////////////////////
/*!
	$B%a%C%7%e$,J];}$9$kD:E@$r%;%C%H$9$k(B
*/
void SetSmgMeshVertex(SmgMesh* pMesh, int index, double x, double y, double z);

void GetSmgMeshVertex(SmgMesh* pMesh, int index, double* dst);

/////////////////////////////////////
/*!
	$B%F%9%/%A%c(BUV$B:BI8G[Ns:n@.(B
	@param[in,out] pMesh
*/
void CreateSmgMeshTextureCoordsArr(SmgMesh* pMesh);

/////////////////////////////////////
/*!
	$B%F%9%/%A%c(BUV$B:BI8$r%;%C%H(B
	@param[in] pMesh
	@param[in] index
	@param[in] u
	@param[in] v
*/
void SetSmgMeshTextureCoords(SmgMesh* pMesh, int index, double u, double v);

/////////////////////////////////////
/*!
	$B%a%C%7%e$,J];}$9$kLLG[Ns$N%5%$%:$r%;%C%H$9$k!#(B
*/
void CreateSmgMeshFaceArr(SmgMesh* pMesh, int nFaces);

//////////////////////////////////////
/*!
	$B%a%C%7%e$,J];}$9$kLL$N%G!<%?$r%;%C%H$9$k(B
*/
void SetSmgMeshFace(SmgMesh* pMesh, int index, int n_ver, int* ver);

///////////////////////////////////////
/*!
	$BLL$N%^%F%j%"%k$r;XDj$9$k!#(B
*/
void SetSmgMeshFaceMaterialIndex(SmgMesh* pMesh, int face_index, int material_index);

//////////////////////////////////////
/*!
	$B%a%C%7%e$,J];}$9$k%^%F%j%"%kG[Ns$N%5%$%:$r%;%C%H$9$k(B
*/
void CreateSmgMeshMaterialArr(SmgMesh* pMesh, int nMaterials);

///////////////////////////////////////
/*!
	$B%a%C%7%e$,J];}$9$k%^%F%j%"%k$N%G!<%?$r%;%C%H(B
*/
void SetSmgMeshMaterial(SmgMesh* pMesh, int index, const SmgMaterial* pMaterial);

///////////////////////////////////////
/*!
	$B%9%-%s%&%'%$%H$NDI2C(B
*/
void AddSmgMeshSkinWeight(SmgMesh* pMesh, SmgSkinWeight* pSkinWeight);

///////////////////////////////////////
/*!
	$BK!@~$,:n@.$5$l$F$$$J$$>l9g:n@.$9$k(B
	@param[in] pMesh;
*/
void MakeSmgMeshFaceNormal(SmgMesh* pMesh);

void MakeSmgMeshVertexNormal(SmgMesh* pMesh);

////////////////////////////////////////
/*!
	$B%\!<%s%3%s%S%M!<%7%g%s$N:n@.(B
*/
void MakeSmgMeshBoneCombination(SmgMesh* pMesh);

////////////////////////////////////////
/*!
	$B%F%9%/%A%c$N:n@.(B
*/
void GenSmgMeshTexture(SmgMesh* pMesh);

///////////////////////////////////////
/*!
	OpenGL$B$K$h$k%U%l!<%`$NIA2h(B
	@param[in] pMesh $BIA2h$9$k%a%C%7%e(B
*/
void DrawSmgMeshGL(SmgMesh* pMesh, int draw_mode);

#endif