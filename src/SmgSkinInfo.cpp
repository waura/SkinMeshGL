#include "SkinMeshGL/SmgSkinInfo.h"

SmgSkinInfo* CreateSmgSkinInfo()
{
	SmgSkinInfo* pSkinInfo = (SmgSkinInfo*) malloc(sizeof(SmgSkinInfo));
	memset(pSkinInfo, 0, sizeof(SmgSkinInfo));
	return pSkinInfo;
}

void ReleaseSmgSkinInfo(SmgSkinInfo** ppSkinInfo)
{
	if(*ppSkinInfo){
		int i;
		for(i=0; i<(*ppSkinInfo)->nBones; i++){
			free((*ppSkinInfo)->arrSkinWeight[i]);
			(*ppSkinInfo)->arrSkinWeight[i] = NULL;
		}
		
		free((*ppSkinInfo)->arrSkinWeight);
		(*ppSkinInfo)->arrSkinWeight = NULL;
		(*ppSkinInfo)->nBones = 0;

		free(*ppSkinInfo);
		(*ppSkinInfo) = NULL;
	}
}

void CreateSmgSkinInfoSkinWeightArr(SmgSkinInfo* pSkinInfo, int nBones)
{
	int i;
	pSkinInfo->nBones = nBones;
	pSkinInfo->arrSkinWeight = (SmgSkinWeight**) malloc(sizeof(SmgSkinWeight*)*nBones);

	//初期化
	for(i=0; i<nBones; i++){
		pSkinInfo->arrSkinWeight[i] = NULL;
	}
}