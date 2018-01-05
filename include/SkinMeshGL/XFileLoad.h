#ifndef _XFILELOAD_H_
#define _XFILELOAD_H_

#include "SmgModel.h"

typedef struct _LOADING_DATA{
	SmgMesh* pCurrentMesh;
	SmgFrame* pCurrentFrame;
	SmgModel* pLoadingModel;
} LOADING_DATA;

SmgModel* XFileLoad(const char* path);

#endif