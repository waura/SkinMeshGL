#include "SkinMeshGL/SmgFace.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//
void DumpSmgFace(const SmgFace* pFace)
{
	if(!pFace) return;

	int i;
	printf("%d: ", pFace->nVertexIndexs);
	for(i=0; i<pFace->nVertexIndexs; i++){
		printf("%d ", pFace->arrVertexIndexs[i]);
	}
	printf("material: %d\n", pFace->material_index); 
}

void InitSmgFace(SmgFace* pFace)
{
	assert(pFace);
	
	memset(pFace, 0, sizeof(SmgFace));
	pFace->material_index = -1;
}

void SetSmgFace(SmgFace* pFace, int nVertexIndexs, const int *arrVertexIndexs)
{
	assert(pFace);

	int i;
	pFace->nVertexIndexs = nVertexIndexs;

	if(pFace->arrVertexIndexs){
		free(pFace->arrVertexIndexs);
	}

	for(i=0; i<3; i++){
		pFace->normalVec._d[i] = 0.0;
	}

	pFace->arrVertexIndexs = (int*) malloc(sizeof(int) * nVertexIndexs);

	for(i=0; i<nVertexIndexs; i++){
		pFace->arrVertexIndexs[i] = arrVertexIndexs[i];
	}
}

void ReleaseSmgFaceVertexIndexs(SmgFace* pFace)
{
	assert(pFace);

	if(pFace->arrVertexIndexs){
		free(pFace->arrVertexIndexs);
		pFace->arrVertexIndexs = NULL;
	}

	pFace->nVertexIndexs = -1;
}
