#include "SkinMeshGL/SmgModel.h"

#include <stdlib.h>
#include <stdio.h>

void DumpSmgModel(SmgModel* pModel)
{
	if(!pModel) return;

	printf("------------ model -------------\n");
	DumpSmgFrame(pModel->pRootFrame);
	printf("--------------------------------\n");
}

SmgModel* CreateSmgModel()
{
	SmgModel* pModel = (SmgModel*) malloc(sizeof(SmgModel));
	pModel->pRootFrame = NULL;
	pModel->currentTime = 0;
	pModel->startTime = 0;
	return pModel;
}

void ReleaseSmgModel(SmgModel** ppModel)
{
	if(*ppModel){
		ReleaseSmgFrame(&((*ppModel)->pRootFrame));
		*ppModel = NULL;
	}
}

//////////////////////////////////
/*!
	テクスチャの生成
	@param[in] pModel
*/
void GenSmgModelTexture(SmgModel* pModel)
{
	GenSmgFrameTexture(pModel->pRootFrame);
}

/////////////////////////////////
/*!
	初期時間を設定する
	@param[in] time 
*/
void SetStartTime(SmgModel* pModel, unsigned long time)
{
	if(pModel){
		pModel->startTime = time;
	}
}

/////////////////////////////////
/*!
	モーションを進める
	@param[in] time 現在の時間
*/
void FrameMoveByTime(SmgModel* pModel, unsigned long time)
{
	if(pModel){
		pModel->currentTime = time - pModel->startTime;
		SetSmgFrameTime(pModel->pRootFrame, pModel->currentTime);
	}
}

/////////////////////////////////
/*!
	コマ送り
*/
void FrameMoveOneStep(SmgModel* pModel)
{
	if(pModel){
		pModel->currentTime++;
		SetSmgFrameTime(pModel->pRootFrame, pModel->currentTime);
	}
}


/////////////////////////////////
/*!
	OpenGLによるモデルのレンダリング
	@param[in] pModel レンダリングするモデル
*/
void RenderSmgModelGL(const SmgModel *pModel, int draw_mode)
{
	SmgMat4 matCur;
	SetSmgMat4Identity(&matCur);

	////変換行列の更新
	//UpdateSmgFrames(pModel->pRootFrame, &matCur);
	//描画
	DrawSmgFrameGL(pModel->pRootFrame, draw_mode);
}
