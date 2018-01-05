#ifndef _SMGSKININFO_H_
#define _SMGSKININFO_H_

#include "SmgSkinWeight.h"

typedef struct _SmgSkinInfo {
	int nBones; //$B%\!<%s$NAm?t(B
	SmgSkinWeight** arrSkinWeight; //$B%\!<%s%&%'%$%H(B
	int nMaxSkinWeightsPerVertex;  //$B0l$D$NE@$K$+$+$k%\!<%s$N:GBg?t(B
	int nMaxSkinWeightsPerFace;    //$B0l$D$NLL$K$+$+$k%\!<%s$N:GBg?t(B
} SmgSkinInfo;

SmgSkinInfo* CreateSmgSkinInfo();
void ReleaseSmgSkinInfo(SmgSkinInfo** ppSkinInfo);

void CreateSmgSkinInfoSkinWeightArr(SmgSkinInfo* pSkinInfo, int nBones);
#endif //_SMGSKININFO_H_