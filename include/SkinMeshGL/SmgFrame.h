#ifndef _SMGFRAME_H_
#define _SMGFRAME_H_

#include "stdafx.h"
#include "SmgMat.h"
#include "SmgQuaternion.h"
#include "SmgMesh.h"
#include "SmgAnimationKey.h"

typedef struct _SmgFrame SmgFrame;
struct _SmgFrame {
	char* name;
	SmgMat4 transFormMat;//フレームの元の変換行列
	SmgMat4 animMat;     //アニメーションの変化行列
	SmgMat4 combinedMat; //変換行列最終結果、レンダリングにこれを使用する
	SmgMesh* pMesh;
	SmgFrame *pSiblingFrame;
	SmgFrame* pFirstChildFrame;
	SmgAnimationKey* pMatAnimKey;
	SmgAnimationKey* pScaleAnimKey;
	SmgAnimationKey* pRotAnimKey;
	SmgAnimationKey* pTransAnimKey;
};

void DumpSmgFrame(const SmgFrame* pFrame);
void DumpSmgFrameHierarchy(const SmgFrame* pFrame, int i);

SmgFrame* CreateSmgFrame();
void ReleaseSmgFrame(SmgFrame** ppFrame);

///////////////////////////////////
/*!
	メッシュの名前をつける
	@param[in,out] pMesh メッシュへのポインタ
	@param[in] name つける名前
*/
void SetSmgFrameName(SmgFrame* pFrame, const char* name);

///////////////////////////////////
/*!
	名前がnameのフレームを探して返す
	@param[in] pFrame 検索対象ルートフレーム
	@param[in] name 検索フレーム名
	@return 対象のフレームへのポインタ、見つからなければNULL
*/
SmgFrame* FindSmgFrame(SmgFrame* pFrame, const char* name);

///////////////////////////////////
/*!
	子フレームを追加する。
	@param[in,out] pFrame 追加される側
	@param[in] pFrame 追加する子フレーム
*/
void AddSmgFrame(SmgFrame* pFrame, SmgFrame* pChildFrame);

///////////////////////////////////
/*!
	アニメーションキーを追加する
	@param[in,out] pFrame 追加される側
	@param[in] pAnimKey アニメーションキー
*/
void AddSmgAnimationKey(SmgFrame* pFrame, SmgAnimationKey* pAnimKey);

///////////////////////////////////
/*!
	フレームに現在の時間を与え、変換行列を生成
	@param[in] pFrame
	@param[in] time 設定する時間
*/
void SetSmgFrameTime(SmgFrame* pFrame, unsigned long time);

///////////////////////////////////
/*!
	変換行列の生成
	@param[in] pFrame
	@param[in] pMatCur 現在の変換行列
*/
void UpdateSmgFrames(SmgFrame* pFrame, const SmgMat4* pMatCur);

///////////////////////////////////
/*!
	テスクチャの生成
	@param[in] pFrame 
*/
void GenSmgFrameTexture(SmgFrame* pFrame);

/////////////////////////
/*!
	OpenGLによるフレームの描画
	@param[in] pFrame 描画するフレーム
*/
void DrawSmgFrameGL(const SmgFrame* pFrame, int draw_mode);
#endif