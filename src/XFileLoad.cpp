#include "SkinMeshGL/XFileLoad.h"
#include "SkinMeshGL/XLex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _DEBUG_PRINT_

//d1 d2の値を入れ替え
void swapd(double* d1, double* d2)
{
	double tmp = *d1;
	*d1 = *d2;
	*d2 = tmp;
}

/////////////////////////////////////////////
/*!
	カレントメッシュを更新
*/
void update_current_mesh(LOADING_DATA* l_data, SmgMesh* pMesh)
{
	if(l_data->pCurrentMesh){
		//法線データが作成されてなければ作成
		if(!l_data->pCurrentMesh->isMakedNormalVertex){
			MakeSmgMeshVertexNormal(l_data->pCurrentMesh);
		}
		//ボーンから描画データを最適化する
		MakeSmgMeshBoneCombination(l_data->pCurrentMesh);
	}
	l_data->pCurrentMesh = pMesh; 
}

////////////////////////////////////////////////
/*!
	カレントフレームを更新
*/
void update_current_frame(LOADING_DATA* l_data, SmgFrame* pFrame)
{
	l_data->pCurrentFrame = pFrame;
}

/////////////////////////////////////////////
/*!
	インデックスの次のトークンを参照する。
*/
char* next_token(XFILE_TOKENS* pTokens, int t_index)
{
	if(t_index + 1 >= pTokens->nTokens) return NULL;
	return pTokens->arr_token[t_index];
}

/////////////////////////////////////////////
/*!
	インデックスのトークンを返し、インデックスを進める
*/
char* get_token(XFILE_TOKENS* pTokens, int* pt_index)
{
	if((*pt_index) >= pTokens->nTokens) return NULL;
	return pTokens->arr_token[(*pt_index)++];
}

/////////////////////////////////////////////
/*!
	インデックスのトークンを整数にして返し、インデックスを進める
*/
int get_int(XFILE_TOKENS* pTokens, int* pt_index)
{
	return atoi( get_token(pTokens, pt_index) );
}

/////////////////////////////////////////////
/*!
	インデックスのトークンを浮動小数にして返し、インデックスを進める
*/
double get_double(XFILE_TOKENS* pTokens, int* pt_index)
{
	return atof( get_token(pTokens, pt_index) );
}

/////////////////////////////////////////////
/*!
	次のトークンが名前のときその名前を返し、インデックスを進める
	そうでない時はNULLを返す。
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
	"{"が出るまで飛ばす
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
	次にある"{"のとき対応する"}"の次まで飛ばす
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

	//法線の数
	int nNormals = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'

	//頂点法線の読み込み
	for(i=0; i<nNormals; i++){
		double x = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double y = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double z = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'

		//書き込み

		get_token(pTokens, pt_index); //skip ';' or ','
	}

	//面法線の数
	int nFaceNormals = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'

	//面法線の読み込み
	for(i=0; i<nFaceNormals; i++){
		int num_vers = get_int(pTokens, pt_index); //頂点数
		get_token(pTokens, pt_index); //skip ';'

		int* is = (int*) malloc(sizeof(int)*num_vers);
		for(j=0; j<num_vers; j++){
			is[j] = get_int(pTokens, pt_index);
			get_token(pTokens, pt_index); //skip ';'

			//書き込み
		}
		get_token(pTokens, pt_index); //skip ';' or ','
	}

	get_token(pTokens, pt_index); //skip '}'
}

BOOL read_mesh_texture_coords(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int* pt_index)
{
	int i;
	get_token(pTokens, pt_index); //skip '{'

	//テスクチャ頂点の数
	int nTextureCoords = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	if(nTextureCoords != l_data->pCurrentMesh->nVertex){
		return FALSE;
	}

	//uv座標配列作成
	CreateSmgMeshTextureCoordsArr(l_data->pCurrentMesh);

	//UV座標
	for(i = 0; i < nTextureCoords; i++){
		double u = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double v = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'

		//書き込み
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
		//現在のメッシュが無い場合はエラー
		return FALSE;
	}

	int i;
	get_token(pTokens, pt_index); //skip '{'

	//マテリアルの数
	int nMaterial = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	CreateSmgMeshMaterialArr(l_data->pCurrentMesh, nMaterial);

	//面の数
	int nFace = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	if(l_data->pCurrentMesh->nFaces != nFace){
		//面の数が不一致
		return FALSE;
	}

	//面の適用マテリアル番号
	for(i=0; i<nFace; i++){
		int material_index = get_int(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ',' or ';'

		SetSmgMeshFaceMaterialIndex(l_data->pCurrentMesh, i, material_index);
	}

	if(strcmp(next_token(pTokens, *pt_index), ";") == 0){
		//lightwaveが吐くXファイルには';'が無いので分岐
		get_token(pTokens, pt_index); //skip ';'
	}

	//マテリアル読み込み
	for(i=0; i<nMaterial; i++){
		if(!(strcmp(get_token(pTokens, pt_index), "Material") == 0)) return false;

		SmgMaterial  material;
		InitSmgMaterial(&material);
		
		get_token(pTokens, pt_index); //skip '{'

		//基本色
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

		//ハイライト強度
		double power = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		SetSmgMaterialPower(&material, power);

		//ハイライト色
		double hr = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double hg = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double hb = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		get_token(pTokens, pt_index); //skip ';'
		SetSmgMaterialSpecular(&material, hr, hg, hb);

		//発行色
		double gr = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double gg = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double gb = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		get_token(pTokens, pt_index); //skip ';'
		SetSmgMaterialEmissive(&material, gr, gg, gb);

		//テスクチャファイル名
		if(strcmp(next_token(pTokens, *pt_index), "TextureFilename") == 0){
			get_token(pTokens, pt_index); //skip TextureFilename
			get_token(pTokens, pt_index); //skip '{'
			char* name = get_token(pTokens, pt_index);
			get_token(pTokens, pt_index); //skip ';'
			get_token(pTokens, pt_index); //skip }

			//"xxx"の"を取り除く
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

	//一つの点にかかるボーンの最大数
	int nMaxSkinWeightsPerVertex = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	pSkinInfo->nMaxSkinWeightsPerVertex = nMaxSkinWeightsPerVertex;

	//一つの面にかかるボーンの最大数
	int nMaxSkinWeightsPerFace = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	pSkinInfo->nMaxSkinWeightsPerFace = nMaxSkinWeightsPerFace;

	//ボーン数取得
	int nBones = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'

	get_token(pTokens, pt_index); //skip '}'

	//ボーン配列作成
	CreateSmgSkinInfoSkinWeightArr(pSkinInfo, nBones);
	
	//スキン情報追加
	l_data->pCurrentMesh->pSkinInfo = pSkinInfo;
}

void read_skin_weights(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int* pt_index)
{
	int i,j;
	SmgSkinWeight* pSkinWeight = CreateSmgSkinWeight();

	get_token(pTokens, pt_index); //skip '{'

	char* to_frame = get_token(pTokens, pt_index); //対象のフレーム名
	get_token(pTokens, pt_index); //skip ';'

	int nWeights = get_int(pTokens, pt_index); //頂点数
	get_token(pTokens, pt_index); //skip ';'
	//
	CreateSmgSkinWeightVertexIndexArr(pSkinWeight, nWeights);
	CreateSmgSkinWeightWeightArr(pSkinWeight, nWeights);

	//頂点インデックス読み込み
	for(i=0; i<nWeights; i++){
		int	ver_index = get_int(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ',' or ';'
		//
		SetSmgSkinWeightVertexIndex(pSkinWeight, i, ver_index);
	}

	//ウェイト読み込み
	for(i=0; i<nWeights; i++){
		double weight = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ',' or ';'
		//
		SetSmgSkinWeightWeight(pSkinWeight, i, weight);
	}

	//ボーン空間へのトランスフォーム行列
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

	//スキンウェイト追加
	AddSmgMeshSkinWeight(l_data->pCurrentMesh, pSkinWeight);
}

void read_mesh(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int* pt_index)
{
	SmgFrame* pCurrentFrame = l_data->pCurrentFrame;
	if(!pCurrentFrame && !l_data->pLoadingModel->pRootFrame){
		//現在のFrameが無くルートフレームが無い場合は作成する
		SmgFrame* pFrame = CreateSmgFrame();
		pCurrentFrame = pFrame;
		l_data->pLoadingModel->pRootFrame = pFrame;
	}

	int i,j;
	SmgMesh* pMesh = CreateSmgMesh();
	SmgMesh* pBeforeMesh = l_data->pCurrentMesh;
	update_current_mesh(l_data, pMesh); //現在のメッシュを更新
	pCurrentFrame->pMesh = pMesh; //現在のフレームにこのメッシュを持たせる

	char* m_name = get_name(pTokens, pt_index);
	if(m_name){ //名前有りの場合
		SetSmgMeshName(pMesh, m_name);
	}
	get_token(pTokens, pt_index); //skip '{'
	
	//頂点数
	int n_ver = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	CreateSmgMeshVertexArr(pMesh, n_ver);

	//頂点読み込み
	for(i=0; i<n_ver; i++){
		double x = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double y = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		double z = get_double(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'

		//書き込み 右手座標系へ変換
		SetSmgMeshVertex(pMesh, i, x, y, -z);

		get_token(pTokens, pt_index); //skip ';' or ','
	}

	//面数
	int n_fac = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	CreateSmgMeshFaceArr(pMesh, n_fac);

	//面読み込み
	for(i=0; i<n_fac; i++){
		int num_vers = get_int(pTokens, pt_index); //頂点数
		get_token(pTokens, pt_index); //skip ';'

		int* is = (int*) malloc(sizeof(int)*num_vers);
		for(j=0; j<num_vers; j++){
			//右手座標へ変換するため逆順で読み込み
			is[num_vers-j-1] = get_int(pTokens, pt_index);
			get_token(pTokens, pt_index); //skip ';'

		}
		
		//書き込み
		SetSmgMeshFace(pMesh, i, num_vers, is);
		free(is);

		get_token(pTokens, pt_index); //skip ';' or ','
	}

	//オプション読み込み
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
		//前のフレームに子供として追加
		AddSmgFrame(l_data->pCurrentFrame, pFrame);
	}
	else{
		l_data->pLoadingModel->pRootFrame = pFrame;
	}

	//このフレームを現在のフレームへ
	update_current_frame(l_data, pFrame);

	char* f_name = get_name(pTokens, pt_index);
	if(f_name){ //名前有りの場合
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
			//転置して格納
			SetSmgMat4Val(&(pFrame->transFormMat), j, i, val);
		}
	}
	SetSmgMat4Val(&(pFrame->transFormMat), 2, 3, 
		(-1) * GetSmgMat4Val(&(pFrame->transFormMat), 2, 3));
	get_token(pTokens, pt_index); //skip ';'
	get_token(pTokens, pt_index); //skip '}'

	//オプション読み込み
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

	//前のカレントフレームへ戻す
	update_current_frame(l_data, pBeforeFrame);
	return TRUE;
}

void read_animation_key(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int *pt_index)
{
	int i,j;
	SmgAnimationKey* pAnimKey = CreateSmgAnimationKey();

	get_token(pTokens, pt_index); //skip '{'

	//キータイプ
	int keyType = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	SetSmgAnimationKeyType(pAnimKey, keyType);
	
	//キー数
	int nKeys = get_int(pTokens, pt_index);
	get_token(pTokens, pt_index); //skip ';'
	CreateSmgAnimationKeyKeyArr(pAnimKey, nKeys);
	CreateSmgAnimationKeyDataArr(pAnimKey, nKeys);

	//キーデータを取り出しコピー
	for(i=0; i<nKeys; i++){
		int num = get_int(pTokens, pt_index);
		get_token(pTokens, pt_index);
		//キー値書き込み
		SetSmgAnimationKeyKey(pAnimKey, i, num);

		int d_size = get_int(pTokens, pt_index);
		get_token(pTokens, pt_index); //skip ';'
		//
		double* d = (double*) malloc(sizeof(double) * d_size);
		for(j=0; j<d_size; j++){
			d[j] = get_double(pTokens, pt_index);
			get_token(pTokens, pt_index); //skip ',' or ';'
		}
		//左手座標系から右手座標系へ変換
		switch(keyType){
			case SMG_ANIM_MAT:
				{
					//行列を転置
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
		//コピー
		for(j=0; j<d_size; j++){
			SetSmgAnimationKeyData(pAnimKey, i, d_size, d);
		}

		free(d);
		get_token(pTokens, pt_index); //skip ';'
		get_token(pTokens, pt_index); //skip ',' or ';'
	}

	get_token(pTokens, pt_index); //skip '}'

	//フレームに追加
	AddSmgAnimationKey(l_data->pCurrentFrame, pAnimKey);
}

void read_animation(LOADING_DATA* l_data, XFILE_TOKENS* pTokens, int *pt_index)
{
	SmgFrame* pBeforeFrame = l_data->pCurrentFrame;

	char* a_name = get_name(pTokens, pt_index);
	if(a_name){ //名前ありの場合
	}
	get_token(pTokens, pt_index); //skip '{'

	//
	while((*pt_index) < pTokens->nTokens){
		char* token = get_token(pTokens, pt_index);
		if(strcmp(token, "AnimationKey") == 0){
			read_animation_key(l_data, pTokens, pt_index);
		}
		else if(strcmp(token, "{") == 0){//フレームネーム
			char* f_name = get_token(pTokens, pt_index);
			get_token(pTokens, pt_index); //skip '}'

			//"xxx"の"を取り除く
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

			//フレーム検索
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
	if(a_name){ //名前有りの場合
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
	//ファイル読み込み、トークンに分割
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
			printf("version:%s", get_token(pTokens, &t_index)); //バージョン
			printf(" bit:%s\n", get_token(pTokens, &t_index)); //ビット数
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
