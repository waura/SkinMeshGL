#include "SkinMeshGL/SmgAnimationKey.h"

SmgAnimationKey* CreateSmgAnimationKey()
{
	SmgAnimationKey* pAnimKey = (SmgAnimationKey*) malloc(sizeof(SmgAnimationKey));
	memset(pAnimKey, 0, sizeof(SmgAnimationKey));

	return pAnimKey;
}

void ReleaseSmgAnimationKey(SmgAnimationKey** ppAnimKey)
{
	if(*ppAnimKey){
		int i;
		
		//
		for(i=0; i<(*ppAnimKey)->nDatas; i++){
			free(&((*ppAnimKey)->key_datas[i]));
		}
		free((*ppAnimKey)->key_datas);

		//
		if((*ppAnimKey)->arrKey){
			free((*ppAnimKey)->arrKey);
		}

		free(*ppAnimKey);
		(*ppAnimKey) = NULL;
	}
}

void SetSmgAnimationKeyType(SmgAnimationKey* pAnimKey, int keyType)
{
	if(pAnimKey){
		pAnimKey->keyType = keyType;
	}
}

void CreateSmgAnimationKeyKeyArr(SmgAnimationKey* pAnimKey, int nKeys)
{
	if(pAnimKey){
		pAnimKey->nKeys = nKeys;
		pAnimKey->arrKey = (int*) malloc(sizeof(int) * nKeys);
	}
}

void SetSmgAnimationKeyKey(SmgAnimationKey* pAnimKey, int index, int key)
{
	if(pAnimKey){
		pAnimKey->arrKey[index] = key;
	}
}


void CreateSmgAnimationKeyDataArr(SmgAnimationKey* pAnimKey, int nKeys)
{
	if(pAnimKey){
		pAnimKey->nKeys = nKeys;
		pAnimKey->key_datas = (double**) malloc(sizeof(double*) * nKeys);
	}
}

void SetSmgAnimationKeyData(SmgAnimationKey* pAnimKey, int index, int nDatas, double* data)
{
	if(pAnimKey){
		int i;
		pAnimKey->key_datas[index] = (double*) malloc(sizeof(double) * nDatas);

		for(i=0; i<nDatas; i++){
			pAnimKey->key_datas[index][i] = data[i];
		}
	}
}