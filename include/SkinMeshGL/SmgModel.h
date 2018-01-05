#ifndef _SMGMODEL_H_
#define _SMGMODEL_H_

#include "SmgFrame.h"

typedef struct _SmgModel {
	SmgFrame* pRootFrame;
	unsigned long startTime;
	unsigned long currentTime;
} SmgModel;

//
void DumpSmgModel(SmgModel* pModel);

SmgModel* CreateSmgModel();
void ReleaseSmgModel(SmgModel** ppModel);

//////////////////////////////////
/*!
	テクスチャの生成
	@param[in] pModel
*/
void GenSmgModelTexture(SmgModel* pModel);

/////////////////////////////////
/*!
	初期時間を設定する
	@param[in] time 
*/
void SetStartTime(SmgModel* pModel, unsigned long time);

/////////////////////////////////
/*!
	モーションを進める
	@param[in] time 現在の時間
*/
void FrameMoveByTime(SmgModel* pModel, unsigned long time);

/////////////////////////////////
/*!
	コマ送り
*/
void FrameMoveOneStep(SmgModel* pModel);

/////////////////////////////////
/*!
	OpenGLによるモデルのレンダリング
	@param[in] pModel レンダリングするモデル
*/
void RenderSmgModelGL(const SmgModel* pModel, int draw_mode);

#endif