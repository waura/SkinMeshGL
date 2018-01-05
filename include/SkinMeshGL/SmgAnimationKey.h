#ifndef _SMGANIMATIONKEY_H_
#define _SMGANIMATIONKEY_H_

#include "stdafx.h"

enum SMG_ANIM_KEY_TYPE {
	SMG_ANIM_ROT   = 0,
	SMG_ANIM_SCALE = 1,
	SMG_ANIM_TRANS = 2,
	SMG_ANIM_MAT   = 4,
};

typedef struct _SmgAnimationKey SmgAnimationKey;
struct _SmgAnimationKey {
	int keyType; 
	int nKeys;
	int* arrKey;
	int nDatas;
	double** key_datas;
};


SmgAnimationKey* CreateSmgAnimationKey();
void ReleaseSmgAnimationKey(SmgAnimationKey** ppAnimKey);

void SetSmgAnimationKeyType(SmgAnimationKey* pAnimKey, int keyType);
void CreateSmgAnimationKeyKeyArr(SmgAnimationKey* pAnimKey, int nKeys);
void SetSmgAnimationKeyKey(SmgAnimationKey* pAnimKey, int index, int key);
void CreateSmgAnimationKeyDataArr(SmgAnimationKey* pAnimKey, int nKeys);
void SetSmgAnimationKeyData(SmgAnimationKey* pAnimKey, int index, int nDatas, double* data);

#endif //_SMGANIMATIONKEY_H_