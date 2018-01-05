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

//$B5eLL@~7AJd4V(B
//src1$B$+$i(Bsrc2$B$X$N0\F0$r$GJd4V$7$?%/%)!<%?%K%*%s$r(Bdst$B$KJV$9(B
void CalcSmgQuaternionSlerp(SmgQuaternion* dst, const SmgQuaternion* src1,
							const SmgQuaternion* src2, float t);
#endif //_SMGQUATERNION_H_

