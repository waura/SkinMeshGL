#ifndef _SMGMAT_H_
#define _SMGMAT_H_

#include "stdafx.h"
#include "SmgQuaternion.h"

//4x4行列
typedef struct _SmgMat4 {
	double _d[16];
} SmgMat4; 

//
void DumpSmgMat4(const SmgMat4* pMat);

//srcをdstにコピーする
void CopySmgMat4(SmgMat4* dst, const SmgMat4* src);

//row行col列の値を返す
//row,colともに(0〜3)
double GetSmgMat4Val(const SmgMat4* pMat, int row, int col);

//row行col列にvalを代入する
void SetSmgMat4Val(SmgMat4* pMat, int row, int col, double val);

//srcを転置したものをdstにいれる
void TransposeSmgMat4(SmgMat4* dst, const SmgMat4* src);

//pMatを単位行列にする
void SetSmgMat4Identity(SmgMat4* pMat);

//pMatを拡大縮小行列にする
void SetSmgMat4Scaling(SmgMat4* pMat, double x_scale, double y_scale, double z_scale);

//クォータニオンから回転行列に変換する
void SetSmgMat4RotQuaternion(SmgMat4* pMat, const SmgQuaternion* pQ);

//平行移動行列を生成する
void SetSmgMat4Trans(SmgMat4* pMat, double x, double y, double z);

//dst = src1 * src2
void CalcSmgMat4Multiply(SmgMat4* dst, const SmgMat4* src1, const SmgMat4* src2);
#endif