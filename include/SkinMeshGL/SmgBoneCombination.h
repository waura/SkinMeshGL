#ifndef _SMGBONECOMBINATION_H_
#define _SMGBONECOMBINATION_H_

#include "stdafx.h"

typedef struct _SmgBoneCombination {
	unsigned long AttribId; //マテリアルID
	unsigned long VertexStart; //頂点開始インデックス
	unsigned long VertexCount; //頂点数
	unsigned long *BoneId; //頂点配列インデックス
} SmgBoneCombination;

#endif //_SMGBONECOMBINATION_H_