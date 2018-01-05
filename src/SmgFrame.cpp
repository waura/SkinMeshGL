#include <SkinMeshGL/SmgFrame.h>

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

void DumpSmgFrame(const SmgFrame* pFrame)
{
	if(!pFrame) return;

	int i,j;
	printf("---------- frame ----------\n");
	if(pFrame->name){
		printf("name: %s\n", pFrame->name);
	}
	printf("transform mat:\n");
	for(i=0; i<4; i++){
		printf("| ");
		for(j=0; j<4; j++){
			printf("%f, ", GetSmgMat4Val(&(pFrame->transFormMat), j, i));
		}
		printf(" |\n");
	}
	printf("\n");
	if(pFrame->pFirstChildFrame){
		DumpSmgFrame(pFrame->pFirstChildFrame);
	}
	if(pFrame->pMesh){
		DumpSmgMesh(pFrame->pMesh);
	}
	printf("---------------------------\n");

	if(pFrame->pSiblingFrame){
		DumpSmgFrame(pFrame->pSiblingFrame);
	}
}

void DumpSmgFrameHierarchy(const SmgFrame* pFrame, int i)
{
	printf("---------- frame ----------\n");
	if(pFrame->name){
		int j;
		for(j=0; j<i; j++){
			printf("  ");
		}
		printf("name: %s\n", pFrame->name);
	}
	if(pFrame->pFirstChildFrame){
		DumpSmgFrameHierarchy(pFrame->pFirstChildFrame, i+1);
	}
	printf("---------------------------\n");

	if(pFrame->pSiblingFrame){
		DumpSmgFrameHierarchy(pFrame->pSiblingFrame, i);
	}
}

SmgFrame* CreateSmgFrame()
{
	SmgFrame* pFrame = (SmgFrame*) malloc(sizeof(SmgFrame));
	pFrame->name = NULL;
	pFrame->pSiblingFrame = NULL;
	pFrame->pFirstChildFrame = NULL;
	pFrame->pMesh = NULL;
	pFrame->pMatAnimKey = NULL;
	pFrame->pRotAnimKey = NULL;
	pFrame->pScaleAnimKey = NULL;
	pFrame->pTransAnimKey = NULL;
	
	//単位行列で初期化
	SetSmgMat4Identity(&(pFrame->transFormMat));
	SetSmgMat4Identity(&(pFrame->animMat));
	SetSmgMat4Identity(&(pFrame->combinedMat));
	return pFrame;
}

void ReleaseSmgFrame(SmgFrame** ppFrame)
{
	if(*ppFrame){
		if((*ppFrame)->name){
			free((*ppFrame)->name);
		}
		if((*ppFrame)->pMesh){
			ReleaseSmgMesh(&((*ppFrame)->pMesh));
		}
		if((*ppFrame)->pSiblingFrame){
			ReleaseSmgFrame(&((*ppFrame)->pSiblingFrame));
		}
		if((*ppFrame)->pFirstChildFrame){
			ReleaseSmgFrame(&((*ppFrame)->pFirstChildFrame));
		}
		if((*ppFrame)->pMatAnimKey){
			ReleaseSmgAnimationKey(&((*ppFrame)->pMatAnimKey));
		}
		if((*ppFrame)->pRotAnimKey){
			ReleaseSmgAnimationKey(&((*ppFrame)->pRotAnimKey));
		}
		if((*ppFrame)->pScaleAnimKey){
			ReleaseSmgAnimationKey(&((*ppFrame)->pScaleAnimKey));
		}
		if((*ppFrame)->pTransAnimKey){
			ReleaseSmgAnimationKey(&((*ppFrame)->pTransAnimKey));
		}

		*ppFrame = NULL;
	}
}

///////////////////////////////////
/*!
	メッシュの名前をつける
	@param[in,out] pMesh メッシュへのポインタ
	@param[in] name つける名前
*/
void SetSmgFrameName(SmgFrame* pFrame, const char* name)
{
	if(pFrame->name){
		free(pFrame->name);
	}

	int len = strlen(name);
	pFrame->name = (char*) malloc(sizeof(char) * (len+1));
	strcpy(pFrame->name, name);
}

///////////////////////////////////
/*!
	名前がnameのフレームを探して返す
	@param[in] pFrame 検索対象ルートフレーム
	@param[in] name 検索フレーム名
	@return 対象のフレームへのポインタ、見つからなければNULL
*/
SmgFrame* FindSmgFrame(SmgFrame* pFrame, const char* name)
{
	if(strcmp(pFrame->name, name) == 0){
		return pFrame;
	}

	if(pFrame->pFirstChildFrame){//子を空検索
		SmgFrame* pf = FindSmgFrame(pFrame->pFirstChildFrame, name);
		if(pf) return pf;
	}

	if(pFrame->pSiblingFrame){
		SmgFrame* pf = FindSmgFrame(pFrame->pSiblingFrame, name);
		if(pf) return pf;
	}

	return NULL;
}

///////////////////////////////////
/*!
	子フレームを追加する。
	@param[in,out] pFrame 追加されるフレーム
	@param[in] pFrame 追加する子フレーム
*/
void AddSmgFrame(SmgFrame* pFrame, SmgFrame* pChildFrame)
{
	if(pFrame){
		if(pFrame->pFirstChildFrame == NULL){
			pFrame->pFirstChildFrame = pChildFrame;
		}
		else{
			pChildFrame->pSiblingFrame = pFrame->pFirstChildFrame->pSiblingFrame;
			pFrame->pFirstChildFrame->pSiblingFrame = pChildFrame;
		}
	}
}

///////////////////////////////////
/*!
	アニメーションキーを追加する
	@param[in,out] pFrame 追加される側
	@param[in] pAnimKey アニメーションキー
*/
void AddSmgAnimationKey(SmgFrame* pFrame, SmgAnimationKey* pAnimKey)
{
	if(pFrame){
		switch(pAnimKey->keyType){
			case SMG_ANIM_ROT:
				pFrame->pRotAnimKey = pAnimKey;
				break;
			case SMG_ANIM_SCALE:
				pFrame->pScaleAnimKey = pAnimKey;
				break;
			case SMG_ANIM_TRANS:
				pFrame->pTransAnimKey = pAnimKey;
				break;
			case SMG_ANIM_MAT:
				pFrame->pMatAnimKey = pAnimKey;
				break;
		}
	}
}

///////////////////////////////////
/*!
	フレームに現在の時間を与え、変換行列を生成
	@param[in] pFrame
	@param[in] time 設定する時間
*/
void SetSmgFrameTime(SmgFrame* pFrame, unsigned long time)
{
	int iKey;
	int dwp1;
	int dwp2;
	float fTime;
	float fTime1;
	float fTime2;
	float fLerpValue;
	SmgMat4 matTemp;
	SmgMat4 matResult;
	BOOL bAnim = FALSE;

	SmgAnimationKey* pMatAnimKey = pFrame->pMatAnimKey;
	SmgAnimationKey* pScaleAnimKey = pFrame->pScaleAnimKey;
	SmgAnimationKey* pRotAnimKey = pFrame->pRotAnimKey;
	SmgAnimationKey* pTransAnimKey = pFrame->pTransAnimKey;

	if(pMatAnimKey){
		//行列としてアニメが登録されていた場合

		//時間にあったキーフレームを検索
		fTime = (float)fmod((float)time, pMatAnimKey->arrKey[ pMatAnimKey->nKeys-1 ]);
		for(iKey=0; iKey<pMatAnimKey->nKeys; iKey++){
			if((float)pMatAnimKey->arrKey[iKey] > fTime){
				dwp2 = iKey;
				dwp1 = (0<iKey)?(iKey - 1) : iKey;
				break;
			}
		}
		fTime1 = (float)pMatAnimKey->arrKey[dwp1];
		fTime2 = (float)pMatAnimKey->arrKey[dwp2];

		//現在の時間に近いキーフレームを選択する
		fLerpValue = ((fTime2 - fTime1) !=0) ? ((fTime - fTime1) / (fTime2 - fTime1)) : 0;
		iKey = (0.5 < fLerpValue) ? dwp2 : dwp1;
	
		int i,j;
		for(i=0; i<4; i++){
			for(j=0; j<4; j++){
				double d = pMatAnimKey->key_datas[iKey][j+i*4];
				SetSmgMat4Val(&matResult, i, j, d);
			}
		}
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				double d = pMatAnimKey->key_datas[iKey][i+j*4];
				SetSmgMat4Val(&matResult, i, j, d);
			}
		}

		CopySmgMat4(&(pFrame->animMat), &matResult);
		//
		//DumpSmgMat4(&(pFrame->animMat));
	}
	else{
		SetSmgMat4Identity(&matResult);
		if(pScaleAnimKey){
			//スケールのアニメ
			dwp1 = dwp2 = 0;

			//時間にあったキーフレームを検索
			//一番大きいキータイムで現在の時間で割って剰余を求める
			fTime = (float)fmod((float)time, pScaleAnimKey->arrKey[ pScaleAnimKey->nKeys-1 ]);
			for(iKey=0; iKey<pScaleAnimKey->nKeys; iKey++){
				if((float)pScaleAnimKey->arrKey[iKey] > fTime){
					dwp2 = iKey;
					dwp1 = (0 < iKey) ? (iKey-1) : iKey;
					break;
				}
			}
			fTime1 = (float)pScaleAnimKey->arrKey[dwp1];
			fTime2 = (float)pScaleAnimKey->arrKey[dwp2];

			//線形補完して合成
			SmgVertex vScale;
			SmgVertex vScaleTime1;
			SmgVertex vScaleTime2;
			SetSmgVertexFromArr(&vScaleTime1, pScaleAnimKey->key_datas[dwp1]);
			SetSmgVertexFromArr(&vScaleTime2, pScaleAnimKey->key_datas[dwp2]);
			fLerpValue = ((fTime2 - fTime1) != 0) ? ((fTime-fTime1)/(fTime2 - fTime1)) : 0;
			CalcLerpVertex(&vScale, &vScaleTime1, &vScaleTime2, fLerpValue);

			//拡大縮小行列を生成し掛ける
			SetSmgMat4Scaling(&matTemp, vScale._d[0], vScale._d[1], vScale._d[2]);
			CalcSmgMat4Multiply(&matResult, &matTemp, &matResult);

			bAnim = TRUE;
		}
		if(pRotAnimKey){
			//回転のアニメ
			dwp1 = dwp2 = 0;

			//時間にあったキーフレームを検索
			fTime = (float)fmod((float)time, pRotAnimKey->arrKey[ pRotAnimKey->nKeys-1 ]);
			for(iKey=0; iKey<pRotAnimKey->nKeys; iKey++){
				if((float)pRotAnimKey->arrKey[iKey] > fTime){
					dwp2 = iKey;
					dwp1 = (0 < iKey) ? (iKey-1) : iKey;
					break;
				}
			}
			fTime1 = (float)pRotAnimKey->arrKey[dwp1];
			fTime2 = (float)pRotAnimKey->arrKey[dwp2];
			fLerpValue = ((fTime2- fTime1) != 0) ? ((fTime - fTime1) / (fTime2 - fTime1)) : 0;

			//球状線形補間して合成
			SmgQuaternion q, q1, q2;

			SetSmgQuaternionVal(&q1, pRotAnimKey->key_datas[dwp1][0],
				pRotAnimKey->key_datas[dwp1][1],
				pRotAnimKey->key_datas[dwp1][2],
				pRotAnimKey->key_datas[dwp1][3]);
			SetSmgQuaternionVal(&q2, -pRotAnimKey->key_datas[dwp2][0],
				pRotAnimKey->key_datas[dwp2][1],
				pRotAnimKey->key_datas[dwp2][2],
				pRotAnimKey->key_datas[dwp2][3]);
			CalcSmgQuaternionSlerp(&q, &q1, &q2, fLerpValue);

			//回転行列を生成しかける
			SetSmgMat4RotQuaternion(&matTemp, &q);
			CalcSmgMat4Multiply(&matResult, &matTemp, &matResult);

			bAnim = TRUE;
		}
		if(pTransAnimKey){
			//平行移動のアニメ
			dwp1 = dwp2 = 0;

			//時間にあったキーフレームを検索
			fTime = (float)fmod((float)time, pTransAnimKey->arrKey[ pTransAnimKey->nKeys-1 ]);
			for(iKey=0; iKey<pTransAnimKey->nKeys; iKey++){
				if((float)pTransAnimKey->arrKey[iKey] > fTime){
					dwp2 = iKey;
					dwp1 = (0 < iKey) ? (iKey-1) : iKey;
					break;
				}
			}
			fTime1 = (float)pTransAnimKey->arrKey[dwp1];
			fTime2 = (float)pTransAnimKey->arrKey[dwp2];
			fLerpValue = ((fTime2 - fTime1) != 0) ? ((fTime - fTime1) / (fTime2 - fTime1)) : 0;

			//線形補完して合成
			SmgVertex vTrans;
			SmgVertex vTransTime1;
			SmgVertex vTransTime2;
			SetSmgVertexVal(&vTransTime1, pTransAnimKey->key_datas[dwp1][0],
				pTransAnimKey->key_datas[dwp1][1],
				pTransAnimKey->key_datas[dwp1][2]);
			SetSmgVertexVal(&vTransTime2, pTransAnimKey->key_datas[dwp2][0],
				pTransAnimKey->key_datas[dwp2][1],
				pTransAnimKey->key_datas[dwp2][2]);
			CalcLerpVertex(&vTrans, &vTransTime1, &vTransTime2, fLerpValue);

			//平行移動行列を生成しかける
			SetSmgMat4Trans(&matTemp, vTrans._d[0], vTrans._d[1], vTrans._d[2]);
			CalcSmgMat4Multiply(&matResult, &matTemp, &matResult);

			bAnim = TRUE;
		}
		else{
			//平行移動のアニメが無ければデフォルトの位置を指定
			SetSmgMat4Trans(&matTemp,
				GetSmgMat4Val(&(pFrame->transFormMat), 0, 3), 
				GetSmgMat4Val(&(pFrame->transFormMat), 0, 3),
				GetSmgMat4Val(&(pFrame->transFormMat), 0, 3));
			CalcSmgMat4Multiply(&matResult, &matTemp, &matResult);
		}
	}

	if(bAnim){
		CopySmgMat4(&(pFrame->animMat), &matResult);
	}

	//子フレームの呼び出し
	SmgFrame* pChild;
	for(pChild = pFrame->pFirstChildFrame; pChild; pChild=pChild->pSiblingFrame){
		SetSmgFrameTime(pChild, time);
	}
}

///////////////////////////////////
/*!
	変換行列の生成
	@param[in] pFrame
	@param[in] pMatCur 現在の変換行列
*/
void UpdateSmgFrames(SmgFrame* pFrame, const SmgMat4* pMatCur)
{
	CalcSmgMat4Multiply(&(pFrame->combinedMat), &(pFrame->animMat), &(pFrame->transFormMat));
	CalcSmgMat4Multiply(&(pFrame->combinedMat), &(pFrame->combinedMat), pMatCur);

	//子供の行列変換
	SmgFrame* pChild;
	for(pChild = pFrame->pFirstChildFrame; pChild; pChild = pChild->pSiblingFrame){
		UpdateSmgFrames(pChild, &(pFrame->combinedMat));
	}
}


///////////////////////////////////
/*!
	テスクチャの生成
*/
void GenSmgFrameTexture(SmgFrame* pFrame)
{
	if(!pFrame) return;

	if(pFrame->pMesh){
		GenSmgMeshTexture(pFrame->pMesh);
	}

	SmgFrame* pChild;
	for(pChild = pFrame->pFirstChildFrame; pChild; pChild=pChild->pSiblingFrame){
		GenSmgFrameTexture(pChild);
	}
}

/////////////////////////
/*!
	OpenGLによるフレームの描画
	@param[in] pFrame 描画するフレーム
*/
void DrawSmgFrameGL(const SmgFrame* pFrame, int draw_mode)
{
	if(!pFrame) return;

	//モデリング変換
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glLoadIdentity();
	//glMultMatrixd(pFrame->combinedMat._d);
	glMultMatrixd(pFrame->animMat._d);
	glMultMatrixd(pFrame->transFormMat._d);

	

	//メッシュの表示
	if(pFrame->pMesh){
		DrawSmgMeshGL(pFrame->pMesh, draw_mode);
	}

	

	//子フレームの表示
	SmgFrame* pChild;
	for(pChild = pFrame->pFirstChildFrame; pChild; pChild=pChild->pSiblingFrame){
		DrawSmgFrameGL(pChild, draw_mode);
	}

	glPopMatrix();
}
