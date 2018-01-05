#ifndef _SMGQUATERNION_H_
#define _SMGQUATERNION_H_

#include "stdafx.h"

typedef struct _SmgQuaternion {
	double _d[4]; //x y z w
} SmgQuaternion;

void SetSmgQuaternionVal(SmgQuaternion* pQuaternion, double x,
						 double y, double z, double w);
//
void SetSmgQuaternionFromArr(SmgQuaternion* pQuaternion, const double* d_arr);
//
void GetSmgQuaternionVal(const SmgQuaternion* pQuaternion, double* x, 
						 double* y, double* z, double* w);

//球面線形補間
//src1からsrc2への移動をで補間したクォータニオンをdstに返す
void CalcSmgQuaternionSlerp(SmgQuaternion* dst, const SmgQuaternion* src1,
							const SmgQuaternion* src2, float t);
#endif //_SMGQUATERNION_H_

