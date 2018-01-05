#ifndef _SMGMODEL_H_
#define _SMGMODEL_H_

#include "SmgFrame.h"

typedef struct _SmgModel {
	SmgFrame* pRootFrame;
	unsigned long startTime;
	unsigned long currentTime;
} SmgModel;

//
void DumpSmgModel(SmgModel* pModel);

SmgModel* CreateSmgModel();
void ReleaseSmgModel(SmgModel** ppModel);

//////////////////////////////////
/*!
	$B%F%/%9%A%c$N@8@.(B
	@param[in] pModel
*/
void GenSmgModelTexture(SmgModel* pModel);

/////////////////////////////////
/*!
	$B=i4|;~4V$r@_Dj$9$k(B
	@param[in] time 
*/
void SetStartTime(SmgModel* pModel, unsigned long time);

/////////////////////////////////
/*!
	$B%b!<%7%g%s$r?J$a$k(B
	@param[in] time $B8=:_$N;~4V(B
*/
void FrameMoveByTime(SmgModel* pModel, unsigned long time);

/////////////////////////////////
/*!
	$B%3%^Aw$j(B
*/
void FrameMoveOneStep(SmgModel* pModel);

/////////////////////////////////
/*!
	OpenGL$B$K$h$k%b%G%k$N%l%s%@%j%s%0(B
	@param[in] pModel $B%l%s%@%j%s%0$9$k%b%G%k(B
*/
void RenderSmgModelGL(const SmgModel* pModel, int draw_mode);

#endif