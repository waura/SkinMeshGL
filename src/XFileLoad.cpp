#include "SkinMeshGL/XFileLoad.h"
#include "SkinMeshGL/XLex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _DEBUG_PRINT_

//d1 d2$B$NCM$rF~$lBX$((B
void swapd(double* d1, double* d2)
{
	double tmp = *d1;
	*d1 = *d2;
	*d2 = tmp;
}

/////////////////////////////////////////////
/*!
	$B%+%l%s%H%a%C%7%e$r99?7(B
*/
void update_current_mesh(LOADING_DATA* l_data, SmgMesh* pMesh)
{
	if(l_data->pCurrentMesh){
		//$BK!@~%G!<%?$,:n@.$5$l$F$J$1$l$P:n@.(B
		if(!l_data->pCurrentMesh->isMakedNormalVertex){
			MakeSmgMeshVertexNormal(l_data->pCurrentMesh);
		}
		//$B%\!<%s$+$iIA2h%G!<%?$r:GE,2=$9$k(B
		MakeSmgMeshBoneCombination(l_data->pCurrentMesh);
	}
	l_data->pCurrentMesh = pMesh; 
}

////////////////////////////////////////////////
/*!
	$B%+%l%s%H%U%l!<%`$r99?7(B
*/
void update_current_frame(LOADING_DATA* l_data, SmgFrame* pFrame)
{
	l_data->pCurrentFrame = pFrame;
}

/////////////////////////////////////////////
/*!
	$B%$%s%G%C%/%9$N<!$N%H!<%/%s$r;2>H$9$k!#(B
*/
char* next_token(XFILE_TOKENS* pTokens, int t_index)
{
	if(t_index + 1 >= pTokens->nTokens) return NULL;
	return pTokens->arr_token[t_index];
}

/////////////////////////////////////////////
/*!
	$B%$%s%G%C%/%9$N%H!<%/%s$rJV$7!"%$%s%G%C%/%9$r?J$a$k(B
*/
char* get_token(XFILE_TOKENS* pTokens, int* pt_index)
{
	if((*pt_index) >= pTokens->nTokens) return NULL;
	return pTokens->arr_token[(*pt_index)++];
}

/////////////////////////////////////////////
/*!
	$B%$%s%G%C%/%9$N%H!<%/%s$r@0?t$K$7$FJV$7!"%$%s%G%C%/%9$r?J$a$k(B
*/
int get_int(XFILE_TOKENS* pTokens, int* pt_index)
{
	return atoi( get_token(pTokens, pt_index) );
}

/////////////////////////////////////////////
/*!
	$B%$%s%G%C%/%9$N%H!<%/%s$rIbF0>.?t$K$7$FJV$7!"%$%s%G%C%/%9$r?J$a$k(B
*/
double get_double(XFILE_TOKENS* pTokens, int* pt_index)
{
	return atof( get_token(pTokens, pt_index) );
}

/////////////////////////////////////////////
/*!
	$B<!$N%H!<%/%s$,L>A0$N$H$-$=$NL>A0$rJV$7!"%$%s%G%C%/%9$r?J$a$k(B
	$B$=$&$G$J$$;~$O(BNULL$B$rJV$9!#(B
*/
char* get_name(XFILE_TOKENS* pTokens, int* pt_index)
{
	if(!(strcmp(next_token(pTokens, *pt_index), "{") == 0)){
		return get_token(pTokens, pt_index);
	}
	return NULL;
}

/////////////////////////////////////////////
/*!
	"{"$B$,=P$k$^$GHt$P$9(B
*/
void skip_name(XFILE_TOKENS* pTokens, int* pt_index)
{
	int i;
	for(i= *pt_index + 1; i < pTokens->nTokens; i++){
		if(strcmp(pTokens->arr_token[i], "{") == 0)
			break;
	}
	*pt_index = i;
}

//////////////////////////////////////////////
/*!
	$B<!$K$"$k(B"{"$B$N$H$-BP1~$9$k(B"}"$B$N<!$^$GHt$P$9(B
*/
void skip_node(XFILE_TOKENS* pTokens, int* pt_index)
{
	while((*pt_index) < pTokens->nTokens){
		char* token = get_token(pTokens, pt_index);
		if(strcmp(token, "{") == 0) break;
	}

	int cnt=1;
	while((*pt_index) < pTokens->nTokens){
		char* token = get_token(pTokens, pt_index);
		
		if(strcmp(token, "{") == 0) cnt++;
		else if(strcmp(token, "}") == 0) cnt--;

		if(cnt <= 0) break;
	}

	if(cnt > 0){
		printf("error: short of '}'");
		exit(1);
	}
}

void read_unknown(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int *pt_index)
{
	skip_node(pTokens, pt_index);
}

void read_template(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int* pt_index)
{
	skip_name(pTokens, pt_index);
	skip_node(pTokens, pt_index);
}

void read_header(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int* pt_index)
{
	skip_node(pTokens, pt_index);
}

void read_mesh_normals(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int* pt_index)
{
	int i,j;
	get_token(pTokens, pt_index); //skip '{'

	//$BK!@~$N?t(B
	int nNormals = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'

	//$BD:E@K!@~$NFI$_9~$_(B
	for(i=0; i<nNormals; i++){
		double x = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double y = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double z = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'

		//$B=q$-9~$_(B

		get_token(pTokens, pt_index); //skip ';' or ','
	}

	//$BLLK!@~$N?t(B
	int nFaceNormals = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'

	//$BLLK!@~$NFI$_9~$_(B
	for(i=0; i<nFaceNormals; i++){
		int num_vers = get_int(pTokens, pt_index); //$BD:E@?t(B
		get_token(pTokens, pt_index); //skip ';'

		int* is = (int*) malloc(sizeof(int)*num_vers);
		for(j=0; j<num_vers; j++){
			is[j] = get_int(pTokens, pt_index);
			get_token(pTokens, pt_index); //skip ';'

			//$B=q$-9~$_(B
		}
		get_token(pTokens, pt_index); //skip ';' or ','
	}

	get_token(pTokens, pt_index); //skip '}'
}

BOOL read_mesh_texture_coords(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int* pt_index)
{
	int i;
	get_token(pTokens, pt_index); //skip '{'

	//$B%F%9%/%A%cD:E@$N?t(B
	int nTextureCoords = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	if(nTextureCoords != l_data->pCurrentMesh->nVertex){
		return FALSE;
	}

	//uv$B:BI8G[Ns:n@.(B
	CreateSmgMeshTextureCoordsArr(l_data->pCurrentMesh);

	//UV$B:BI8(B
	for(i = 0; i < nTextureCoords; i++){
		double u = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double v = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'

		//$B=q$-9~$_(B
		SetSmgMeshTextureCoords(l_data->pCurrentMesh, i, u, v);

		get_token(pTokens, pt_index); //skip ',' or ';'
	}

	get_token(pTokens, pt_index); //skip '}'
	return TRUE;
}

void read_mesh_vertex_colors(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int* pt_index)
{
	skip_node(pTokens, pt_index);
}

BOOL read_mesh_material_list(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int* pt_index)
{
	if(!l_data->pCurrentMesh){
		//$B8=:_$N%a%C%7%e$,L5$$>l9g$O%(%i!<(B
		return FALSE;
	}

	int i;
	get_token(pTokens, pt_index); //skip '{'

	//$B%^%F%j%"%k$N?t(B
	int nMaterial = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	CreateSmgMeshMaterialArr(l_data->pCurrentMesh, nMaterial);

	//$BLL$N?t(B
	int nFace = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	if(l_data->pCurrentMesh->nFaces != nFace){
		//$BLL$N?t$,IT0lCW(B
		return FALSE;
	}

	//$BLL$NE,MQ%^%F%j%"%kHV9f(B
	for(i=0; i<nFace; i++){
		int material_index = get_int(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ',' or ';'

		SetSmgMeshFaceMaterialIndex(l_data->pCurrentMesh, i, material_index);
	}

	if(strcmp(next_token(pTokens, *pt_index), ";") == 0){
		//lightwave$B$,EG$/(BX$B%U%!%$%k$K$O(B';'$B$,L5$$$N$GJ,4t(B
		get_token(pTokens, pt_index); //skip ';'
	}

	//$B%^%F%j%"%kFI$_9~$_(B
	for(i=0; i<nMaterial; i++){
		if(!(strcmp(get_token(pTokens, pt_index), "Material") == 0)) return false;

		SmgMaterial  material;
		InitSmgMaterial(&material);
		
		get_token(pTokens, pt_index); //skip '{'

		//$B4pK\?'(B
		double r = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double g = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double b = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double a = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		get_token(pTokens, pt_index); //skip ';'
		SetSmgMaterialColor(&material, r, g, b, a);

		//$B%O%$%i%$%H6/EY(B
		double power = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		SetSmgMaterialPower(&material, power);

		//$B%O%$%i%$%H?'(B
		double hr = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double hg = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double hb = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		get_token(pTokens, pt_index); //skip ';'
		SetSmgMaterialSpecular(&material, hr, hg, hb);

		//$BH/9T?'(B
		double gr = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double gg = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double gb = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		get_token(pTokens, pt_index); //skip ';'
		SetSmgMaterialEmissive(&material, gr, gg, gb);

		//$B%F%9%/%A%c%U%!%$%kL>(B
		if(strcmp(next_token(pTokens, *pt_index), "TextureFilename") == 0){
			get_token(pTokens, pt_index); //skip TextureFilename
			get_token(pTokens, pt_index); //skip '{'
			char* name = get_token(pTokens, pt_index);
			get_token(pTokens, pt_index); //skip ';'
			get_token(pTokens, pt_index); //skip }

			//"xxx"$B$N(B"$B$r<h$j=|$/(B
			int j;
			int n_index=0;
			int len = strlen(name);
			char* n_name = (char*)malloc(sizeof(char)*(len+1));
			for(j=0; name[j] != '\0'; j++){
				if(name[j] != '"'){
					n_name[n_index++] = name[j];
				}
			}
			n_name[n_index++] = '\0';
			CreateSmgMaterialTexture(&material, n_name);
			free(n_name);
		}

		get_token(pTokens, pt_index); //skip '}'

		SetSmgMeshMaterial(l_data->pCurrentMesh, i, &material);
	}

	get_token(pTokens, pt_index); //skip '}'

	return TRUE;
}

void read_skin_mesh_header(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int* pt_index)
{
	SmgSkinInfo* pSkinInfo = CreateSmgSkinInfo();

	get_token(pTokens, pt_index); //skip '{'

	//$B0l$D$NE@$K$+$+$k%\!<%s$N:GBg?t(B
	int nMaxSkinWeightsPerVertex = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	pSkinInfo->nMaxSkinWeightsPerVertex = nMaxSkinWeightsPerVertex;

	//$B0l$D$NLL$K$+$+$k%\!<%s$N:GBg?t(B
	int nMaxSkinWeightsPerFace = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	pSkinInfo->nMaxSkinWeightsPerFace = nMaxSkinWeightsPerFace;

	//$B%\!<%s?t<hF@(B
	int nBones = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'

	get_token(pTokens, pt_index); //skip '}'

	//$B%\!<%sG[Ns:n@.(B
	CreateSmgSkinInfoSkinWeightArr(pSkinInfo, nBones);
	
	//$B%9%-%s>pJsDI2C(B
	l_data->pCurrentMesh->pSkinInfo = pSkinInfo;
}

void read_skin_weights(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int* pt_index)
{
	int i,j;
	SmgSkinWeight* pSkinWeight = CreateSmgSkinWeight();

	get_token(pTokens, pt_index); //skip '{'

	char* to_frame = get_token(pTokens, pt_index); //$BBP>]$N%U%l!<%`L>(B
	get_token(pTokens, pt_index); //skip ';'

	int nWeights = get_int(pTokens, pt_index); //$BD:E@?t(B
	get_token(pTokens, pt_index); //skip ';'
	//
	CreateSmgSkinWeightVertexIndexArr(pSkinWeight, nWeights);
	CreateSmgSkinWeightWeightArr(pSkinWeight, nWeights);

	//$BD:E@%$%s%G%C%/%9FI$_9~$_(B
	for(i=0; i<nWeights; i++){
		int	ver_index = get_int(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ',' or ';'
		//
		SetSmgSkinWeightVertexIndex(pSkinWeight, i, ver_index);
	}

	//$B%&%'%$%HFI$_9~$_(B
	for(i=0; i<nWeights; i++){
		double weight = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ',' or ';'
		//
		SetSmgSkinWeightWeight(pSkinWeight, i, weight);
	}

	//$B%\!<%s6u4V$X$N%H%i%s%9%U%)!<%`9TNs(B
	for(j=0; j<4; j++){
		for(i=0; i<4; i++){
			double val = get_double(pTokens, pt_index);
			get_token(pTokens, pt_index);
			//
			SetSmgMat4Val(&(pSkinWeight->matrixOffset), i, j, val);
		}
	}

	get_token(pTokens, pt_index); //skip ';'
	get_token(pTokens, pt_index); //skip '}'

	//$B%9%-%s%&%'%$%HDI2C(B
	AddSmgMeshSkinWeight(l_data->pCurrentMesh, pSkinWeight);
}

void read_mesh(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int* pt_index)
{
	SmgFrame* pCurrentFrame = l_data->pCurrentFrame;
	if(!pCurrentFrame && !l_data->pLoadingModel->pRootFrame){
		//$B8=:_$N(BFrame$B$,L5$/%k!<%H%U%l!<%`$,L5$$>l9g$O:n@.$9$k(B
		SmgFrame* pFrame = CreateSmgFrame();
		pCurrentFrame = pFrame;
		l_data->pLoadingModel->pRootFrame = pFrame;
	}

	int i,j;
	SmgMesh* pMesh = CreateSmgMesh();
	SmgMesh* pBeforeMesh = l_data->pCurrentMesh;
	update_current_mesh(l_data, pMesh); //$B8=:_$N%a%C%7%e$r99?7(B
	pCurrentFrame->pMesh = pMesh; //$B8=:_$N%U%l!<%`$K$3$N%a%C%7%e$r;}$?$;$k(B

	char* m_name = get_name(pTokens, pt_index);
	if(m_name){ //$BL>A0M-$j$N>l9g(B
		SetSmgMeshName(pMesh, m_name);
	}
	get_token(pTokens, pt_index); //skip '{'
	
	//$BD:E@?t(B
	int n_ver = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	CreateSmgMeshVertexArr(pMesh, n_ver);

	//$BD:E@FI$_9~$_(B
	for(i=0; i<n_ver; i++){
		double x = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double y = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double z = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'

		//$B=q$-9~$_(B $B1&<j:BI87O$XJQ49(B
		SetSmgMeshVertex(pMesh, i, x, y, -z);

		get_token(pTokens, pt_index); //skip ';' or ','
	}

	//$BLL?t(B
	int n_fac = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	CreateSmgMeshFaceArr(pMesh, n_fac);

	//$BLLFI$_9~$_(B
	for(i=0; i<n_fac; i++){
		int num_vers = get_int(pTokens, pt_index); //$BD:E@?t(B
		get_token(pTokens, pt_index); //skip ';'

		int* is = (int*) malloc(sizeof(int)*num_vers);
		for(j=0; j<num_vers; j++){
			//$B1&<j:BI8$XJQ49$9$k$?$a5U=g$GFI$_9~$_(B
			is[num_vers-j-1] = get_int(pTokens, pt_index);
			get_token(pTokens, pt_index); //skip ';'

		}
		
		//$B=q$-9~$_(B
		SetSmgMeshFace(pMesh, i, num_vers, is);
		free(is);

		get_token(pTokens, pt_index); //skip ';' or ','
	}

	//$B%*%W%7%g%sFI$_9~$_(B
	while((*pt_index) < pTokens->nTokens){
		char* token = get_token(pTokens, pt_index);
		if(strcmp(token, "MeshMaterialList") == 0){
			read_mesh_material_list(l_data, pTokens, pt_index);
		}
		else if(strcmp(token, "MeshNormals") == 0){
			read_mesh_normals(l_data, pTokens, pt_index);
		}
		else if(strcmp(token, "MeshTextureCoords") == 0){
			read_mesh_texture_coords(l_data, pTokens, pt_index);
		}
		else if(strcmp(token, "MeshVertexColors") == 0){
			read_mesh_vertex_colors(l_data, pTokens, pt_index);
		}
		else if(strcmp(token, "XSkinMeshHeader") == 0){
			read_skin_mesh_header(l_data, pTokens, pt_index);
		}
		else if(strcmp(token, "SkinWeights") == 0){
			read_skin_weights(l_data, pTokens, pt_index);
		}
		else if(strcmp(token, "}") == 0){
			break;
		}
		else{
			read_unknown(l_data, pTokens, pt_index);
		}
	}

	update_current_mesh(l_data, pBeforeMesh);
}

BOOL read_frame(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int *pt_index)
{
	SmgFrame* pFrame = CreateSmgFrame();
	SmgFrame* pBeforeFrame = l_data->pCurrentFrame;
	if(l_data->pCurrentFrame){
		//$BA0$N%U%l!<%`$K;R6!$H$7$FDI2C(B
		AddSmgFrame(l_data->pCurrentFrame, pFrame);
	}
	else{
		l_data->pLoadingModel->pRootFrame = pFrame;
	}

	//$B$3$N%U%l!<%`$r8=:_$N%U%l!<%`$X(B
	update_current_frame(l_data, pFrame);

	char* f_name = get_name(pTokens, pt_index);
	if(f_name){ //$BL>A0M-$j$N>l9g(B
		SetSmgFrameName(pFrame, f_name);
	}
	get_token(pTokens, pt_index); //skip '{'

	if(strcmp(get_token(pTokens, pt_index), "FrameTransformMatrix") != 0){
		return FALSE;
	}

	get_token(pTokens, pt_index); //skip '{'

	int i,j;
	for(j=0; j<4; j++){
		for(i=0; i<4; i++){
			double val = get_double(pTokens, pt_index);
			get_token(pTokens, pt_index);
			//$BE>CV$7$F3JG<(B
			SetSmgMat4Val(&(pFrame->transFormMat), j, i, val);
		}
	}
	SetSmgMat4Val(&(pFrame->transFormMat), 2, 3, 
		(-1) * GetSmgMat4Val(&(pFrame->transFormMat), 2, 3));
	get_token(pTokens, pt_index); //skip ';'
	get_token(pTokens, pt_index); //skip '}'

	//$B%*%W%7%g%sFI$_9~$_(B
	while((*pt_index) < pTokens->nTokens){
		char* token = get_token(pTokens, pt_index);
		if(strcmp(token, "Frame") == 0){
			read_frame(l_data, pTokens, pt_index);
		}
		else if(strcmp(token, "Mesh") == 0){
			read_mesh(l_data, pTokens, pt_index);
		}
		else if(strcmp(token, "}") == 0){
			break;
		}
		else{
			read_unknown(l_data, pTokens, pt_index);
		}
	}

	//$BA0$N%+%l%s%H%U%l!<%`$XLa$9(B
	update_current_frame(l_data, pBeforeFrame);
	return TRUE;
}

void read_animation_key(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int *pt_index)
{
	int i,j;
	SmgAnimationKey* pAnimKey = CreateSmgAnimationKey();

	get_token(pTokens, pt_index); //skip '{'

	//$B%-!<%?%$%W(B
	int keyType = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	SetSmgAnimationKeyType(pAnimKey, keyType);
	
	//$B%-!<?t(B
	int nKeys = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	CreateSmgAnimationKeyKeyArr(pAnimKey, nKeys);
	CreateSmgAnimationKeyDataArr(pAnimKey, nKeys);

	//$B%-!<%G!<%?$r<h$j=P$7%3%T!<(B
	for(i=0; i<nKeys; i++){
		int num = get_int(pTokens, pt_index);
		get_token(pTokens, pt_index);
		//$B%-!<CM=q$-9~$_(B
		SetSmgAnimationKeyKey(pAnimKey, i, num);

		int d_size = get_int(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		//
		double* d = (double*) malloc(sizeof(double) * d_size);
		for(j=0; j<d_size; j++){
			d[j] = get_double(pTokens, pt_index);
			get_token(pTokens, pt_index); //skip ',' or ';'
		}
		//$B:8<j:BI87O$+$i1&<j:BI87O$XJQ49(B
		switch(keyType){
			case SMG_ANIM_MAT:
				{
					//$B9TNs$rE>CV(B
					int s,t;
					for(t=0; t<4; t++){
						for(s=0; s<t; s++){
							swapd(&(d[s+t*4]), &(d[t+s*4]));
						}
					}
					d[3+2*4] = -1.0 * d[3+2*4];
				}
			  break;
			case SMG_ANIM_ROT:
				{
					//from (w, x, y, z) to (x, y, z, w) 
				    double tmp = d[0];
				    d[0] = d[1]; //x
				    d[1] = d[2]; //y
				    d[2] = d[3]; //z
				    d[3] = -1.0 * tmp; //w
				}
				break;
			case SMG_ANIM_TRANS:
			    d[2] = -1.0 * d[2];
				break;
		}
		//$B%3%T!<(B
		for(j=0; j<d_size; j++){
			SetSmgAnimationKeyData(pAnimKey, i, d_size, d);
		}

		free(d);
		get_token(pTokens, pt_index); //skip ';'
		get_token(pTokens, pt_index); //skip ',' or ';'
	}

	get_token(pTokens, pt_index); //skip '}'

	//$B%U%l!<%`$KDI2C(B
	AddSmgAnimationKey(l_data->pCurrentFrame, pAnimKey);
}

void read_animation(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int *pt_index)
{
	SmgFrame* pBeforeFrame = l_data->pCurrentFrame;

	char* a_name = get_name(pTokens, pt_index);
	if(a_name){ //$BL>A0$"$j$N>l9g(B
	}
	get_token(pTokens, pt_index); //skip '{'

	//
	while((*pt_index) < pTokens->nTokens){
		char* token = get_token(pTokens, pt_index);
		if(strcmp(token, "AnimationKey") == 0){
			read_animation_key(l_data, pTokens, pt_index);
		}
		else if(strcmp(token, "{") == 0){//$B%U%l!<%`%M!<%`(B
			char* f_name = get_token(pTokens, pt_index);
			get_token(pTokens, pt_index); //skip '}'

			//"xxx"$B$N(B"$B$r<h$j=|$/(B
			int j;
			int n_index=0;
			int len = strlen(f_name);
			char* nf_name = (char*)malloc(sizeof(char)*(len+1));
			for(j=0; f_name[j] != '\0'; j++){
				if(f_name[j] != '"'){
					nf_name[n_index++] = f_name[j];
				}
			}
			nf_name[n_index++] = '\0';

			//$B%U%l!<%`8!:w(B
			SmgFrame* pFrame = FindSmgFrame(l_data->pLoadingModel->pRootFrame, nf_name);
			update_current_frame(l_data, pFrame);
			free(nf_name);

		}
		else if(strcmp(token, "}") == 0){
			break;
		}
	}

	update_current_frame(l_data, pBeforeFrame);
}

void read_animation_set(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int *pt_index)
{
	char* a_name = get_name(pTokens, pt_index);
	if(a_name){ //$BL>A0M-$j$N>l9g(B
	}
	get_token(pTokens, pt_index); //skip '{'

	//
	while((*pt_index) < pTokens->nTokens){
		char* token = get_token(pTokens, pt_index);
		if(strcmp(token, "Animation") == 0){
			read_animation(l_data, pTokens, pt_index);
		}
		else if(strcmp(token, "}") == 0){
			break;
		}
	}
}

SmgModel* XFileLoad(const char* path)
{
	int t_index=0;
	//$B%U%!%$%kFI$_9~$_!"%H!<%/%s$KJ,3d(B
	XFILE_TOKENS* pTokens = XLexFmtTxt(path);
	if(pTokens == NULL){
	  printf("file open error %s \n", path);
	  return NULL;
	}
	//DumpTokens(pTokens);

	//
	LOADING_DATA l_data;
	l_data.pCurrentMesh = NULL;
	l_data.pCurrentFrame = NULL;
	l_data.pLoadingModel = CreateSmgModel();

	for(t_index=0; t_index < pTokens->nTokens; ){
		char* token = get_token(pTokens, &t_index);
		if(t_index >= pTokens->nTokens) break;

		if(strcmp(token, "xof") == 0){
	#ifdef _DEBUG_PRINT_
			printf("xof-");
			printf("version:%s", get_token(pTokens, &t_index)); //$B%P!<%8%g%s(B
			printf(" bit:%s\n", get_token(pTokens, &t_index)); //$B%S%C%H?t(B
	#endif //_DEBUG_PRINT
		}
		else if(strcmp(token, "template") == 0){
			read_template(&l_data, pTokens, &t_index);
		}
		else if(strcmp(token, "Header") == 0){
			read_header(&l_data, pTokens, &t_index);
		}
		else if(strcmp(token, "Frame") == 0){
			read_frame(&l_data, pTokens, &t_index);
		}
		else if(strcmp(token, "Mesh") == 0){
			read_mesh(&l_data, pTokens, &t_index);
		}
		else if(strcmp(token, "AnimationSet") == 0){
			read_animation_set(&l_data, pTokens, &t_index);
		}
	}

	ReleaseTokens(&pTokens);

	return l_data.pLoadingModel;
}
