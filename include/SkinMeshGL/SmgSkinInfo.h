#ifndef _SMGSKININFO_H_
#define _SMGSKININFO_H_

#include "SmgSkinWeight.h"

typedef struct _SmgSkinInfo {
	int nBones; //ボーンの総数
	SmgSkinWeight** arrSkinWeight; //ボーンウェイト
	int nMaxSkinWeightsPerVertex;  //一つの点にかかるボーンの最大数
	int nMaxSkinWeightsPerFace;    //一つの面にかかるボーンの最大数
} SmgSkinInfo;

SmgSkinInfo* CreateSmgSkinInfo();
void ReleaseSmgSkinInfo(SmgSkinInfo** ppSkinInfo);

void CreateSmgSkinInfoSkinWeightArr(SmgSkinInfo* pSkinInfo, int nBones);
#endif //_SMGSKININFO_H_