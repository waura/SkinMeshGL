#ifndef _SMGMAT_H_
#define _SMGMAT_H_

#include "stdafx.h"
#include "SmgQuaternion.h"

//4x4$B9TNs(B
typedef struct _SmgMat4 {
	double _d[16];
} SmgMat4; 

//
void DumpSmgMat4(const SmgMat4* pMat);

//src$B$r(Bdst$B$K%3%T!<$9$k(B
void CopySmgMat4(SmgMat4* dst, const SmgMat4* src);

//row$B9T(Bcol$BNs$NCM$rJV$9(B
//row,col$B$H$b$K(B(0$B!A(B3)
double GetSmgMat4Val(const SmgMat4* pMat, int row, int col);

//row$B9T(Bcol$BNs$K(Bval$B$rBeF~$9$k(B
void SetSmgMat4Val(SmgMat4* pMat, int row, int col, double val);

//src$B$rE>CV$7$?$b$N$r(Bdst$B$K$$$l$k(B
void TransposeSmgMat4(SmgMat4* dst, const SmgMat4* src);

//pMat$B$rC10L9TNs$K$9$k(B
void SetSmgMat4Identity(SmgMat4* pMat);

//pMat$B$r3HBg=L>.9TNs$K$9$k(B
void SetSmgMat4Scaling(SmgMat4* pMat, double x_scale, double y_scale, double z_scale);

//$B%/%)!<%?%K%*%s$+$i2sE>9TNs$KJQ49$9$k(B
void SetSmgMat4RotQuaternion(SmgMat4* pMat, const SmgQuaternion* pQ);

//$BJ?9T0\F09TNs$r@8@.$9$k(B
void SetSmgMat4Trans(SmgMat4* pMat, double x, double y, double z);

//dst = src1 * src2
void CalcSmgMat4Multiply(SmgMat4* dst, const SmgMat4* src1, const SmgMat4* src2);
#endif