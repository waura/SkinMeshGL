#include "SkinMeshGL/SmgQuaternion.h"

void SetSmgQuaternionVal(SmgQuaternion* pQuaternion, double x,
						 double y, double z, double w)
{
	if(pQuaternion){
		pQuaternion->_d[0] = x;
		pQuaternion->_d[1] = y;
		pQuaternion->_d[2] = z;
		pQuaternion->_d[3] = w;
	}
}
//
void SetSmgQuaternionFromArr(SmgQuaternion* pQuaternion, const double* d_arr)
{
	if(!pQuaternion) return;

	int i;
	for(i=0; i<4; i++){
		pQuaternion->_d[i] = d_arr[i];
	}
}

//
void GetSmgQuaternionVal(const SmgQuaternion* pQuaternion, double* x, 
						 double* y, double* z, double* w)
{
	if(!pQuaternion) return;
	
	*x = pQuaternion->_d[0];
	*y = pQuaternion->_d[1];
	*z = pQuaternion->_d[2];
	*w = pQuaternion->_d[3];
}

//球面線形補間
//src1からsrc2への移動をで補間したクォータニオンをdstに返す
void CalcSmgQuaternionSlerp(SmgQuaternion* dst, const SmgQuaternion* src1,
							const SmgQuaternion* src2, float t)
{
	double d = src1->_d[0] * src2->_d[0] + src1->_d[1] * src2->_d[1] +
		src1->_d[2] * src2->_d[2] + src1->_d[3] * src2->_d[3];
	double ss = 1.0 - d*d;

	if(ss == 0.0){
		SetSmgQuaternionFromArr(dst, src1->_d);
	}
	else{
		double sp = sqrt(ss);
		double ph = acos(d);
		double pt = ph * t;
		double t1 = sin(pt) / sp;
		double t0 = sin(ph - pt) / sp;

		dst->_d[0] = src1->_d[0] * t0 + src2->_d[0] * t1;
		dst->_d[1] = src1->_d[1] * t0 + src2->_d[1] * t1;
		dst->_d[2] = src1->_d[2] * t0 + src2->_d[2] * t1;
		dst->_d[3] = src1->_d[3] * t0 + src2->_d[3] * t1;
	}
}
