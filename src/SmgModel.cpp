#include "SkinMeshGL/SmgModel.h"

#include <stdlib.h>
#include <stdio.h>

void DumpSmgModel(SmgModel* pModel)
{
	if(!pModel) return;

	printf("------------ model -------------\n");
	DumpSmgFrame(pModel->pRootFrame);
	printf("--------------------------------\n");
}

SmgModel* CreateSmgModel()
{
	SmgModel* pModel = (SmgModel*) malloc(sizeof(SmgModel));
	pModel->pRootFrame = NULL;
	pModel->currentTime = 0;
	pModel->startTime = 0;
	return pModel;
}

void ReleaseSmgModel(SmgModel** ppModel)
{
	if(*ppModel){
		ReleaseSmgFrame(&((*ppModel)->pRootFrame));
		*ppModel = NULL;
	}
}

//////////////////////////////////
/*!
	$B%F%/%9%A%c$N@8@.(B
	@param[in] pModel
*/
void GenSmgModelTexture(SmgModel* pModel)
{
	GenSmgFrameTexture(pModel->pRootFrame);
}

/////////////////////////////////
/*!
	$B=i4|;~4V$r@_Dj$9$k(B
	@param[in] time 
*/
void SetStartTime(SmgModel* pModel, unsigned long time)
{
	if(pModel){
		pModel->startTime = time;
	}
}

/////////////////////////////////
/*!
	$B%b!<%7%g%s$r?J$a$k(B
	@param[in] time $B8=:_$N;~4V(B
*/
void FrameMoveByTime(SmgModel* pModel, unsigned long time)
{
	if(pModel){
		pModel->currentTime = time - pModel->startTime;
		SetSmgFrameTime(pModel->pRootFrame, pModel->currentTime);
	}
}

/////////////////////////////////
/*!
	$B%3%^Aw$j(B
*/
void FrameMoveOneStep(SmgModel* pModel)
{
	if(pModel){
		pModel->currentTime++;
		SetSmgFrameTime(pModel->pRootFrame, pModel->currentTime);
	}
}


/////////////////////////////////
/*!
	OpenGL$B$K$h$k%b%G%k$N%l%s%@%j%s%0(B
	@param[in] pModel $B%l%s%@%j%s%0$9$k%b%G%k(B
*/
void RenderSmgModelGL(const SmgModel *pModel, int draw_mode)
{
	SmgMat4 matCur;
	SetSmgMat4Identity(&matCur);

	////$BJQ499TNs$N99?7(B
	//UpdateSmgFrames(pModel->pRootFrame, &matCur);
	//$BIA2h(B
	DrawSmgFrameGL(pModel->pRootFrame, draw_mode);
}
