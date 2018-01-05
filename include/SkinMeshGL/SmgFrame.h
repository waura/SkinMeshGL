#ifndef _SMGFRAME_H_
#define _SMGFRAME_H_

#include "stdafx.h"
#include "SmgMat.h"
#include "SmgQuaternion.h"
#include "SmgMesh.h"
#include "SmgAnimationKey.h"

typedef struct _SmgFrame SmgFrame;
struct _SmgFrame {
	char* name;
	SmgMat4 transFormMat;//$B%U%l!<%`$N85$NJQ499TNs(B
	SmgMat4 animMat;     //$B%"%K%a!<%7%g%s$NJQ2=9TNs(B
	SmgMat4 combinedMat; //$BJQ499TNs:G=*7k2L!"%l%s%@%j%s%0$K$3$l$r;HMQ$9$k(B
	SmgMesh* pMesh;
	SmgFrame *pSiblingFrame;
	SmgFrame* pFirstChildFrame;
	SmgAnimationKey* pMatAnimKey;
	SmgAnimationKey* pScaleAnimKey;
	SmgAnimationKey* pRotAnimKey;
	SmgAnimationKey* pTransAnimKey;
};

void DumpSmgFrame(const SmgFrame* pFrame);
void DumpSmgFrameHierarchy(const SmgFrame* pFrame, int i);

SmgFrame* CreateSmgFrame();
void ReleaseSmgFrame(SmgFrame** ppFrame);

///////////////////////////////////
/*!
	$B%a%C%7%e$NL>A0$r$D$1$k(B
	@param[in,out] pMesh $B%a%C%7%e$X$N%]%$%s%?(B
	@param[in] name $B$D$1$kL>A0(B
*/
void SetSmgFrameName(SmgFrame* pFrame, const char* name);

///////////////////////////////////
/*!
	$BL>A0$,(Bname$B$N%U%l!<%`$rC5$7$FJV$9(B
	@param[in] pFrame $B8!:wBP>]%k!<%H%U%l!<%`(B
	@param[in] name $B8!:w%U%l!<%`L>(B
	@return $BBP>]$N%U%l!<%`$X$N%]%$%s%?!"8+$D$+$i$J$1$l$P(BNULL
*/
SmgFrame* FindSmgFrame(SmgFrame* pFrame, const char* name);

///////////////////////////////////
/*!
	$B;R%U%l!<%`$rDI2C$9$k!#(B
	@param[in,out] pFrame $BDI2C$5$l$kB&(B
	@param[in] pFrame $BDI2C$9$k;R%U%l!<%`(B
*/
void AddSmgFrame(SmgFrame* pFrame, SmgFrame* pChildFrame);

///////////////////////////////////
/*!
	$B%"%K%a!<%7%g%s%-!<$rDI2C$9$k(B
	@param[in,out] pFrame $BDI2C$5$l$kB&(B
	@param[in] pAnimKey $B%"%K%a!<%7%g%s%-!<(B
*/
void AddSmgAnimationKey(SmgFrame* pFrame, SmgAnimationKey* pAnimKey);

///////////////////////////////////
/*!
	$B%U%l!<%`$K8=:_$N;~4V$rM?$(!"JQ499TNs$r@8@.(B
	@param[in] pFrame
	@param[in] time $B@_Dj$9$k;~4V(B
*/
void SetSmgFrameTime(SmgFrame* pFrame, unsigned long time);

///////////////////////////////////
/*!
	$BJQ499TNs$N@8@.(B
	@param[in] pFrame
	@param[in] pMatCur $B8=:_$NJQ499TNs(B
*/
void UpdateSmgFrames(SmgFrame* pFrame, const SmgMat4* pMatCur);

///////////////////////////////////
/*!
	$B%F%9%/%A%c$N@8@.(B
	@param[in] pFrame 
*/
void GenSmgFrameTexture(SmgFrame* pFrame);

/////////////////////////
/*!
	OpenGL$B$K$h$k%U%l!<%`$NIA2h(B
	@param[in] pFrame $BIA2h$9$k%U%l!<%`(B
*/
void DrawSmgFrameGL(const SmgFrame* pFrame, int draw_mode);
#endif