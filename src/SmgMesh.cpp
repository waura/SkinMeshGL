#include "stdafx.h"
#include "SkinMeshGL/SmgMesh.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#define _PI_ 3.1415926535

///////////////////////////////////
/*!
	$B%a%C%7%e!<%G!<%?$r%@%s%W$9$k(B
	@param[in] pMesh $B%@%s%W$5$l$k%a%C%7%e(B
*/
void DumpSmgMesh(const SmgMesh* pMesh)
{
	if(!pMesh) return;

	printf("--------- mesh ---------\n");
	
	int i;
	for(i=0; i<pMesh->nVertex; i++){
		DumpSmgVertex(&(pMesh->arrVertex[i]));
		if(pMesh->arrTextureCoords){
			DumpSmgCoords(&(pMesh->arrTextureCoords[i]));
		}
	}
	for(i=0; i<pMesh->nFaces; i++){
		DumpSmgFace(&(pMesh->arrFace[i]));
	}
	for(i=0; i<pMesh->nMaterials; i++){
		DumpSmgMaterial(&(pMesh->arrMaterial[i]));
	}

	if(pMesh->name){
		printf("mesh name: %s\n", pMesh->name);
	}
	printf("mesh nVertex: %d\n", pMesh->nVertex);
	printf("mesh nFaces: %d\n", pMesh->nFaces);
	printf("mesh nMaterials: %d\n", pMesh->nMaterials);
	
	printf("------------------------\n");
}

///////////////////////////////////
/*!
	$B%a%C%7%e$r@8@.$7$FJV$9(B
	@return $B@8@.$7$?%a%C%7%e$X$N%]%$%s%?(B
*/
SmgMesh* CreateSmgMesh()
{
	SmgMesh* pMesh = (SmgMesh*) malloc(sizeof(SmgMesh));
	memset(pMesh, 0, sizeof(SmgMesh));
	return pMesh;
}

///////////////////////////////////
/*!
	$B%a%C%7%e$r3+J|$9$k(B
	@param[in,out] pMesh $B3+J|$9$k%a%C%7%e$X$N%]%$%s%?(B
*/
void ReleaseSmgMesh(SmgMesh** pMesh)
{
	if(*pMesh){
		int i;

		//$B%a%C%7%eL>(B
		if((*pMesh)->name){
			free((*pMesh)->name);
			(*pMesh)->name = NULL;
		}

		//$BD:E@%G!<%?(B
		if((*pMesh)->arrVertex){
			free((*pMesh)->arrVertex);
			(*pMesh)->arrVertex = NULL;
			(*pMesh)->nVertex = 0;
		}
		if((*pMesh)->arrNormal){
			free((*pMesh)->arrNormal);
			(*pMesh)->arrNormal = NULL;
		}

		//$B%F%/%9%A%c(BUV
		if((*pMesh)->arrTextureCoords){
			free((*pMesh)->arrTextureCoords);
			(*pMesh)->arrTextureCoords = NULL;
		}

		//$BLL%G!<%?(B
		for(i=0; i<(*pMesh)->nFaces; i++){
			ReleaseSmgFaceVertexIndexs( &((*pMesh)->arrFace[i]) );
		}
		free((*pMesh)->arrFace);
		(*pMesh)->arrFace = NULL;
		(*pMesh)->nFaces = 0;

		//$B%^%F%j%"%k(B
		for(i=0; i<(*pMesh)->nFaces; i++){
			ReleaseSmgMaterialTexture(&((*pMesh)->arrMaterial[i]));
		}
		free((*pMesh)->arrMaterial);
		(*pMesh)->arrMaterial = NULL;
		(*pMesh)->nMaterials = 0;

		//$B%9%-%s%G!<%?(B
		if((*pMesh)->pSkinInfo){
			ReleaseSmgSkinInfo(&((*pMesh)->pSkinInfo));
		}

		free(*pMesh);
		*pMesh = NULL;
	}
}

///////////////////////////////////
/*!
	$B%a%C%7%e$NL>A0$r$D$1$k(B
	@param[in,out] pMesh $B%a%C%7%e$X$N%]%$%s%?(B
	@param[in] name $B$D$1$kL>A0(B
*/
void SetSmgMeshName(SmgMesh* pMesh, const char* name)
{
	if(pMesh->name){
		free(pMesh->name);
	}

	int len = strlen(name);
	pMesh->name = (char*) malloc(sizeof(char) * (len+1));
	strcpy(pMesh->name, name);
}

///////////////////////////////////
/*!
	$B%a%C%7%e$,J];}$9$kD:E@G[Ns$N%5%$%:$r%;%C%H$9$k!#(B
*/
void CreateSmgMeshVertexArr(SmgMesh* pMesh, int nVertex)
{
	if(pMesh->arrVertex){
		free(pMesh->arrVertex);
	}
	if(pMesh->arrNormal){
		free(pMesh->arrNormal);
	}
	
	pMesh->nVertex = nVertex;
	pMesh->arrVertex = (SmgVertex*) malloc(sizeof(SmgVertex) * nVertex);
	pMesh->arrNormal = (SmgVertex*) malloc(sizeof(SmgVertex) * nVertex);

	memset(pMesh->arrNormal, 0, sizeof(SmgVertex)*nVertex);
}

////////////////////////////////////
/*!
	$B%a%C%7%e$,J];}$9$kD:E@$r%;%C%H$9$k(B
*/
void SetSmgMeshVertex(SmgMesh* pMesh, int index, double x, double y, double z)
{
	assert( 0 <= index && index < pMesh->nVertex );

	SetSmgVertexVal(&(pMesh->arrVertex[index]), x, y, z);
}

void GetSmgMeshVertex(SmgMesh* pMesh, int index, double* dst)
{
	assert( 0 <= index && index < pMesh->nVertex );

	memcpy(dst, pMesh->arrVertex[index]._d, sizeof(double)*3);
}

void CreateSmgMeshTextureCoordsArr(SmgMesh* pMesh)
{
	if(pMesh->arrTextureCoords){
		free(pMesh->arrTextureCoords);
	}
	pMesh->arrTextureCoords = (SmgCoords*) malloc(sizeof(SmgCoords) * pMesh->nVertex);
}

void SetSmgMeshTextureCoords(SmgMesh* pMesh, int index, double u, double v)
{
	if(0 <= index && index < pMesh->nVertex){
		pMesh->arrTextureCoords[ index ].u = u;
		pMesh->arrTextureCoords[ index ].v = v;
	}
}

/////////////////////////////////////
/*!
	$B%a%C%7%e$,J];}$9$kLLG[Ns$N%5%$%:$r%;%C%H$9$k!#(B
*/
void CreateSmgMeshFaceArr(SmgMesh* pMesh, int nFaces)
{
	int i;
	if(pMesh->arrFace){
		for(i=0; pMesh->nFaces; i++){
				ReleaseSmgFaceVertexIndexs( &(pMesh->arrFace[i]) );
		}
		free(pMesh->arrFace);
	}

	pMesh->nFaces = nFaces;
	pMesh->arrFace = (SmgFace*) malloc(sizeof(SmgFace) * nFaces);
	
	//$BA4LL=i4|2=(B
	for(i=0; i<nFaces; i++){
		InitSmgFace( &(pMesh->arrFace[i]) );
	}
}

//////////////////////////////////////
/*!
	$B%a%C%7%e$,J];}$9$kLL$N%G!<%?$r%;%C%H$9$k(B
*/
void SetSmgMeshFace(SmgMesh *pMesh, int index, int n_ver, int *ver)
{
	assert(0 <= index && index < pMesh->nFaces);
	if(!pMesh) return;

	SetSmgFace(&(pMesh->arrFace[index]), n_ver, ver);
}

///////////////////////////////////////
/*!
	$BLL$N%^%F%j%"%k$r;XDj$9$k!#(B
*/
void SetSmgMeshFaceMaterialIndex(SmgMesh* pMesh, int face_index, int material_index)
{
	if(!pMesh) return;

	if(0 <= face_index && face_index < pMesh->nFaces){
		pMesh->arrFace[ face_index].material_index = material_index;
	}
}

//////////////////////////////////////
/*!
	$B%a%C%7%e$,J];}$9$k%^%F%j%"%kG[Ns$N%5%$%:$r%;%C%H$9$k(B
*/
void CreateSmgMeshMaterialArr(SmgMesh* pMesh, int nMaterials)
{
	if(!pMesh) return;

	int i;
	if(pMesh->arrMaterial){
		for(i=0; i<pMesh->nFaces; i++){
			ReleaseSmgMaterialTexture(&(pMesh->arrMaterial[i]));
		}
		free(pMesh->arrMaterial);
	}

	pMesh->arrMaterial = (SmgMaterial*) malloc(sizeof(SmgMaterial) * nMaterials);
	pMesh->nMaterials = nMaterials;
}

///////////////////////////////////////
/*!
	$B%a%C%7%e$,J];}$9$k%^%F%j%"%k$N%G!<%?$r%;%C%H(B
*/
void SetSmgMeshMaterial(SmgMesh* pMesh, int index, const SmgMaterial* pMaterial)
{
	if(!pMesh) return;

	if(0 <= index && index < pMesh->nMaterials){
		pMesh->arrMaterial[ index ] = *pMaterial;
	}
}

///////////////////////////////////////
/*!
	$B%9%-%s%&%'%$%H$NDI2C(B
*/
void AddSmgMeshSkinWeight(SmgMesh* pMesh, SmgSkinWeight* pSkinWeight)
{
	if(pMesh->pSkinInfo){
		int i;
		for(i=0; i < pMesh->pSkinInfo->nBones; i++){
			if(pMesh->pSkinInfo->arrSkinWeight[i] == NULL){
				pMesh->pSkinInfo->arrSkinWeight[i] = pSkinWeight;
				break;
			}
		}
	}
}

///////////////////////////////////////
/*!
	$BK!@~$,:n@.$5$l$F$$$J$$>l9g:n@.$9$k(B
	@param[in] pMesh;
*/
void MakeSmgMeshFaceNormal(SmgMesh* pMesh)
{
	if(!pMesh) return;

	int i,j;
	for(i=0; i<pMesh->nFaces; i++){
		CalcNormalVertex(&(pMesh->arrFace[i].normalVec),
			&(pMesh->arrVertex[ pMesh->arrFace[i].arrVertexIndexs[0] ]),
			&(pMesh->arrVertex[ pMesh->arrFace[i].arrVertexIndexs[1] ]),
			&(pMesh->arrVertex[ pMesh->arrFace[i].arrVertexIndexs[2] ]));
	}

	pMesh->isMakedNormalVertex = TRUE;
}

void MakeSmgMeshVertexNormal(SmgMesh* pMesh)
{
	if(!pMesh) return;

	MakeSmgMeshFaceNormal( pMesh );

	memset(pMesh->arrNormal, 0, sizeof(SmgVertex) * pMesh->nVertex);

	int i,j;
	for(i=0; i<pMesh->nFaces; i++){
		for(j=0; j<pMesh->arrFace[i].nVertexIndexs; j++){
			CalcAddVertex(
				&(pMesh->arrNormal[ pMesh->arrFace[i].arrVertexIndexs[j] ]),
				&(pMesh->arrNormal[ pMesh->arrFace[i].arrVertexIndexs[j] ]),
				&(pMesh->arrFace[i].normalVec));
		}
	}

	double length;
	for(i=0; i<pMesh->nVertex; i++){
		length = GetVertexLength( &(pMesh->arrNormal[i]) );
	
		if(length == 0.0){
			continue;
		}

		for(j=0; j<3; j++){
			pMesh->arrNormal[i]._d[j] /= length;
		}

	}
}

////////////////////////////////////////
/*!
	$B%\!<%s%3%s%S%M!<%7%g%s$N:n@.(B
*/
void MakeSmgMeshBoneCombination(SmgMesh* pMesh)
{
	if(!pMesh) return;
	if(!pMesh->pSkinInfo) return;

	int i,j,k;
	int nMaxSkinWeightsPerVertex = pMesh->pSkinInfo->nMaxSkinWeightsPerVertex;
	//$BD:E@$r%-!<$H$7$?%\!<%s$X$N%O%C%7%e%F!<%V%k$N:n@.(B
	int** vertex2bone_table = (int**) malloc(sizeof(int*) * pMesh->nVertex);
	for(i=0; i<pMesh->nVertex; i++){
		vertex2bone_table[i] = (int*) malloc(sizeof(int) * nMaxSkinWeightsPerVertex);
		for(j=0; j<nMaxSkinWeightsPerVertex; j++){
			vertex2bone_table[i][j] = -1;
		}
	}
	for(i=0; i<pMesh->pSkinInfo->nBones; i++){
		//$B3F%\!<%s$N;}$D%&%'%$%H(B
		for(j=0; j<pMesh->pSkinInfo->arrSkinWeight[i]->nWeights; j++){
			int ver_index = pMesh->pSkinInfo->arrSkinWeight[i]->vertexIndices[j];
			//add bone id
			for(k=0; k<nMaxSkinWeightsPerVertex; k++){
				if(vertex2bone_table[ver_index][k] == -1){
					vertex2bone_table[ver_index][k] = i;
					break;
				}
			}
		}
	}
	
	for(i=0; i<pMesh->nFaces; i++){
		for(j=0; j<pMesh->arrFace[i].nVertexIndexs; j++){

		}
	}

	for(i=0; i<pMesh->nVertex; i++){
		free(vertex2bone_table[i]);
	}
	free(vertex2bone_table);
}

////////////////////////////////////////
/*!
	$B%F%9%/%A%c$N:n@.(B
*/
void GenSmgMeshTexture(SmgMesh* pMesh)
{
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	int i;
	for(i=0; i<pMesh->nMaterials; i++){
		if(pMesh->arrMaterial[i].pTexture){
			glGenTextures(1, &(pMesh->arrMaterial[i].glTexName));
			glBindTexture(GL_TEXTURE_2D, pMesh->arrMaterial[i].glTexName);

			
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			//glTexImage2D(
			//	GL_TEXTURE_2D, 0, GL_RGBA,
			//	pMesh->arrMaterial[i].pTexture->width,
			//	pMesh->arrMaterial[i].pTexture->height,
			//	0, GL_RGBA, GL_UNSIGNED_BYTE,
			//	pMesh->arrMaterial[i].pTexture->_data);
			glTexImage2D(
				GL_TEXTURE_2D, 0, GL_RGB,
				pMesh->arrMaterial[i].pTexture->width,
				pMesh->arrMaterial[i].pTexture->height,
				0, GL_RGB, GL_UNSIGNED_BYTE,
				pMesh->arrMaterial[i].pTexture->_data);

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			//glBindTexture(GL_TEXTURE_2D, 0);
		}

	}

	glDisable(GL_TEXTURE_2D);
}

///////////////////////////////////////
/*!
	OpenGL$B$K$h$k%U%l!<%`$NIA2h(B
	@param[in] pMesh $BIA2h$9$k%a%C%7%e(B
*/
void DrawSmgMeshGL(SmgMesh* pMesh, int draw_mode)
{
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int i,j;
	double c1, c2;
	for(i=0; i<pMesh->nFaces; i++){
	
		if(draw_mode == DRAW_WILE){
			glBegin(GL_LINE_LOOP);
		}
		else if(draw_mode == DRAW_POLY){
			switch(pMesh->arrFace[i].nVertexIndexs){
				case 3:
					glBegin(GL_TRIANGLES);
					break;
				case 4:
					glBegin(GL_QUADS);
					break;
				default:
					glBegin(GL_TRIANGLE_STRIP);
					break;
			}
		}

		//$B%^%F%j%"%k@_Dj(B
		if((pMesh->arrFace[i].material_index != -1) && (pMesh->arrMaterial)){
			glMaterialfv( GL_FRONT,
				//GL_DIFFUSE,
				GL_AMBIENT_AND_DIFFUSE,
				pMesh->arrMaterial[ pMesh->arrFace[i].material_index ].color );
			glMaterialfv( GL_FRONT,
				GL_SHININESS,
				&(pMesh->arrMaterial[ pMesh->arrFace[i].material_index ].power) );
			glMaterialfv( GL_FRONT,
				GL_SPECULAR,
				pMesh->arrMaterial[ pMesh->arrFace[i].material_index ].specular );
			glMaterialfv( GL_FRONT,
				GL_EMISSION,
				pMesh->arrMaterial[ pMesh->arrFace[i].material_index ].emissiver );

			glBindTexture(GL_TEXTURE_2D,
				pMesh->arrMaterial[ pMesh->arrFace[i].material_index ].glTexName);
		}
		
		//$BIA2h(B
		for(j=0; j<pMesh->arrFace[i].nVertexIndexs; j++){
			//uv
			if(pMesh->arrFace[i].material_index != -1 && pMesh->arrMaterial &&
				pMesh->arrMaterial[ pMesh->arrFace[i].material_index ].pTexture)
			{
				glTexCoord2d(
					pMesh->arrTextureCoords[ pMesh->arrFace[i].arrVertexIndexs[j] ].u,
					pMesh->arrTextureCoords[ pMesh->arrFace[i].arrVertexIndexs[j] ].v);
			}

			//$BK!@~(B
			c1 = pMesh->arrFace[i].normalVec._d[0] * pMesh->arrNormal[ pMesh->arrFace[i].arrVertexIndexs[j] ]._d[0] +
				pMesh->arrFace[i].normalVec._d[1] * pMesh->arrNormal[ pMesh->arrFace[i].arrVertexIndexs[j] ]._d[1] +
				pMesh->arrFace[i].normalVec._d[2] * pMesh->arrNormal[ pMesh->arrFace[i].arrVertexIndexs[j] ]._d[2];
			c2 = cos(45.0 * _PI_ / 180.0);
			if(c1 < c2){
				glNormal3dv( pMesh->arrFace[i].normalVec._d );
			}
			else{
				glNormal3dv( pMesh->arrNormal[ pMesh->arrFace[i].arrVertexIndexs[j] ]._d );
			}

			//$BD:E@(B
			glVertex3dv(pMesh->arrVertex[ pMesh->arrFace[i].arrVertexIndexs[j] ]._d);
		}

		if(pMesh->arrFace[i].material_index != -1){
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);
}
