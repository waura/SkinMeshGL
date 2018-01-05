#include <SkinMeshGL/SmgFrame.h>

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

void DumpSmgFrame(const SmgFrame* pFrame)
{
	if(!pFrame) return;

	int i,j;
	printf("---------- frame ----------\n");
	if(pFrame->name){
		printf("name: %s\n", pFrame->name);
	}
	printf("transform mat:\n");
	for(i=0; i<4; i++){
		printf("| ");
		for(j=0; j<4; j++){
			printf("%f, ", GetSmgMat4Val(&(pFrame->transFormMat), j, i));
		}
		printf(" |\n");
	}
	printf("\n");
	if(pFrame->pFirstChildFrame){
		DumpSmgFrame(pFrame->pFirstChildFrame);
	}
	if(pFrame->pMesh){
		DumpSmgMesh(pFrame->pMesh);
	}
	printf("---------------------------\n");

	if(pFrame->pSiblingFrame){
		DumpSmgFrame(pFrame->pSiblingFrame);
	}
}

void DumpSmgFrameHierarchy(const SmgFrame* pFrame, int i)
{
	printf("---------- frame ----------\n");
	if(pFrame->name){
		int j;
		for(j=0; j<i; j++){
			printf("  ");
		}
		printf("name: %s\n", pFrame->name);
	}
	if(pFrame->pFirstChildFrame){
		DumpSmgFrameHierarchy(pFrame->pFirstChildFrame, i+1);
	}
	printf("---------------------------\n");

	if(pFrame->pSiblingFrame){
		DumpSmgFrameHierarchy(pFrame->pSiblingFrame, i);
	}
}

SmgFrame* CreateSmgFrame()
{
	SmgFrame* pFrame = (SmgFrame*) malloc(sizeof(SmgFrame));
	pFrame->name = NULL;
	pFrame->pSiblingFrame = NULL;
	pFrame->pFirstChildFrame = NULL;
	pFrame->pMesh = NULL;
	pFrame->pMatAnimKey = NULL;
	pFrame->pRotAnimKey = NULL;
	pFrame->pScaleAnimKey = NULL;
	pFrame->pTransAnimKey = NULL;
	
	//$BC10L9TNs$G=i4|2=(B
	SetSmgMat4Identity(&(pFrame->transFormMat));
	SetSmgMat4Identity(&(pFrame->animMat));
	SetSmgMat4Identity(&(pFrame->combinedMat));
	return pFrame;
}

void ReleaseSmgFrame(SmgFrame** ppFrame)
{
	if(*ppFrame){
		if((*ppFrame)->name){
			free((*ppFrame)->name);
		}
		if((*ppFrame)->pMesh){
			ReleaseSmgMesh(&((*ppFrame)->pMesh));
		}
		if((*ppFrame)->pSiblingFrame){
			ReleaseSmgFrame(&((*ppFrame)->pSiblingFrame));
		}
		if((*ppFrame)->pFirstChildFrame){
			ReleaseSmgFrame(&((*ppFrame)->pFirstChildFrame));
		}
		if((*ppFrame)->pMatAnimKey){
			ReleaseSmgAnimationKey(&((*ppFrame)->pMatAnimKey));
		}
		if((*ppFrame)->pRotAnimKey){
			ReleaseSmgAnimationKey(&((*ppFrame)->pRotAnimKey));
		}
		if((*ppFrame)->pScaleAnimKey){
			ReleaseSmgAnimationKey(&((*ppFrame)->pScaleAnimKey));
		}
		if((*ppFrame)->pTransAnimKey){
			ReleaseSmgAnimationKey(&((*ppFrame)->pTransAnimKey));
		}

		*ppFrame = NULL;
	}
}

///////////////////////////////////
/*!
	$B%a%C%7%e$NL>A0$r$D$1$k(B
	@param[in,out] pMesh $B%a%C%7%e$X$N%]%$%s%?(B
	@param[in] name $B$D$1$kL>A0(B
*/
void SetSmgFrameName(SmgFrame* pFrame, const char* name)
{
	if(pFrame->name){
		free(pFrame->name);
	}

	int len = strlen(name);
	pFrame->name = (char*) malloc(sizeof(char) * (len+1));
	strcpy(pFrame->name, name);
}

///////////////////////////////////
/*!
	$BL>A0$,(Bname$B$N%U%l!<%`$rC5$7$FJV$9(B
	@param[in] pFrame $B8!:wBP>]%k!<%H%U%l!<%`(B
	@param[in] name $B8!:w%U%l!<%`L>(B
	@return $BBP>]$N%U%l!<%`$X$N%]%$%s%?!"8+$D$+$i$J$1$l$P(BNULL
*/
SmgFrame* FindSmgFrame(SmgFrame* pFrame, const char* name)
{
	if(strcmp(pFrame->name, name) == 0){
		return pFrame;
	}

	if(pFrame->pFirstChildFrame){//$B;R$r6u8!:w(B
		SmgFrame* pf = FindSmgFrame(pFrame->pFirstChildFrame, name);
		if(pf) return pf;
	}

	if(pFrame->pSiblingFrame){
		SmgFrame* pf = FindSmgFrame(pFrame->pSiblingFrame, name);
		if(pf) return pf;
	}

	return NULL;
}

///////////////////////////////////
/*!
	$B;R%U%l!<%`$rDI2C$9$k!#(B
	@param[in,out] pFrame $BDI2C$5$l$k%U%l!<%`(B
	@param[in] pFrame $BDI2C$9$k;R%U%l!<%`(B
*/
void AddSmgFrame(SmgFrame* pFrame, SmgFrame* pChildFrame)
{
	if(pFrame){
		if(pFrame->pFirstChildFrame == NULL){
			pFrame->pFirstChildFrame = pChildFrame;
		}
		else{
			pChildFrame->pSiblingFrame = pFrame->pFirstChildFrame->pSiblingFrame;
			pFrame->pFirstChildFrame->pSiblingFrame = pChildFrame;
		}
	}
}

///////////////////////////////////
/*!
	$B%"%K%a!<%7%g%s%-!<$rDI2C$9$k(B
	@param[in,out] pFrame $BDI2C$5$l$kB&(B
	@param[in] pAnimKey $B%"%K%a!<%7%g%s%-!<(B
*/
void AddSmgAnimationKey(SmgFrame* pFrame, SmgAnimationKey* pAnimKey)
{
	if(pFrame){
		switch(pAnimKey->keyType){
			case SMG_ANIM_ROT:
				pFrame->pRotAnimKey = pAnimKey;
				break;
			case SMG_ANIM_SCALE:
				pFrame->pScaleAnimKey = pAnimKey;
				break;
			case SMG_ANIM_TRANS:
				pFrame->pTransAnimKey = pAnimKey;
				break;
			case SMG_ANIM_MAT:
				pFrame->pMatAnimKey = pAnimKey;
				break;
		}
	}
}

///////////////////////////////////
/*!
	$B%U%l!<%`$K8=:_$N;~4V$rM?$(!"JQ499TNs$r@8@.(B
	@param[in] pFrame
	@param[in] time $B@_Dj$9$k;~4V(B
*/
void SetSmgFrameTime(SmgFrame* pFrame, unsigned long time)
{
	int iKey;
	int dwp1;
	int dwp2;
	float fTime;
	float fTime1;
	float fTime2;
	float fLerpValue;
	SmgMat4 matTemp;
	SmgMat4 matResult;
	BOOL bAnim = FALSE;

	SmgAnimationKey* pMatAnimKey = pFrame->pMatAnimKey;
	SmgAnimationKey* pScaleAnimKey = pFrame->pScaleAnimKey;
	SmgAnimationKey* pRotAnimKey = pFrame->pRotAnimKey;
	SmgAnimationKey* pTransAnimKey = pFrame->pTransAnimKey;

	if(pMatAnimKey){
		//$B9TNs$H$7$F%"%K%a$,EPO?$5$l$F$$$?>l9g(B

		//$B;~4V$K$"$C$?%-!<%U%l!<%`$r8!:w(B
		fTime = (float)fmod((float)time, pMatAnimKey->arrKey[ pMatAnimKey->nKeys-1 ]);
		for(iKey=0; iKey<pMatAnimKey->nKeys; iKey++){
			if((float)pMatAnimKey->arrKey[iKey] > fTime){
				dwp2 = iKey;
				dwp1 = (0<iKey)?(iKey - 1) : iKey;
				break;
			}
		}
		fTime1 = (float)pMatAnimKey->arrKey[dwp1];
		fTime2 = (float)pMatAnimKey->arrKey[dwp2];

		//$B8=:_$N;~4V$K6a$$%-!<%U%l!<%`$rA*Br$9$k(B
		fLerpValue = ((fTime2 - fTime1) !=0) ? ((fTime - fTime1) / (fTime2 - fTime1)) : 0;
		iKey = (0.5 < fLerpValue) ? dwp2 : dwp1;
	
		int i,j;
		for(i=0; i<4; i++){
			for(j=0; j<4; j++){
				double d = pMatAnimKey->key_datas[iKey][j+i*4];
				SetSmgMat4Val(&matResult, i, j, d);
			}
		}
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				double d = pMatAnimKey->key_datas[iKey][i+j*4];
				SetSmgMat4Val(&matResult, i, j, d);
			}
		}

		CopySmgMat4(&(pFrame->animMat), &matResult);
		//
		//DumpSmgMat4(&(pFrame->animMat));
	}
	else{
		SetSmgMat4Identity(&matResult);
		if(pScaleAnimKey){
			//$B%9%1!<%k$N%"%K%a(B
			dwp1 = dwp2 = 0;

			//$B;~4V$K$"$C$?%-!<%U%l!<%`$r8!:w(B
			//$B0lHVBg$-$$%-!<%?%$%`$G8=:_$N;~4V$G3d$C$F>jM>$r5a$a$k(B
			fTime = (float)fmod((float)time, pScaleAnimKey->arrKey[ pScaleAnimKey->nKeys-1 ]);
			for(iKey=0; iKey<pScaleAnimKey->nKeys; iKey++){
				if((float)pScaleAnimKey->arrKey[iKey] > fTime){
					dwp2 = iKey;
					dwp1 = (0 < iKey) ? (iKey-1) : iKey;
					break;
				}
			}
			fTime1 = (float)pScaleAnimKey->arrKey[dwp1];
			fTime2 = (float)pScaleAnimKey->arrKey[dwp2];

			//$B@~7AJd40$7$F9g@.(B
			SmgVertex vScale;
			SmgVertex vScaleTime1;
			SmgVertex vScaleTime2;
			SetSmgVertexFromArr(&vScaleTime1, pScaleAnimKey->key_datas[dwp1]);
			SetSmgVertexFromArr(&vScaleTime2, pScaleAnimKey->key_datas[dwp2]);
			fLerpValue = ((fTime2 - fTime1) != 0) ? ((fTime-fTime1)/(fTime2 - fTime1)) : 0;
			CalcLerpVertex(&vScale, &vScaleTime1, &vScaleTime2, fLerpValue);

			//$B3HBg=L>.9TNs$r@8@.$73]$1$k(B
			SetSmgMat4Scaling(&matTemp, vScale._d[0], vScale._d[1], vScale._d[2]);
			CalcSmgMat4Multiply(&matResult, &matTemp, &matResult);

			bAnim = TRUE;
		}
		if(pRotAnimKey){
			//$B2sE>$N%"%K%a(B
			dwp1 = dwp2 = 0;

			//$B;~4V$K$"$C$?%-!<%U%l!<%`$r8!:w(B
			fTime = (float)fmod((float)time, pRotAnimKey->arrKey[ pRotAnimKey->nKeys-1 ]);
			for(iKey=0; iKey<pRotAnimKey->nKeys; iKey++){
				if((float)pRotAnimKey->arrKey[iKey] > fTime){
					dwp2 = iKey;
					dwp1 = (0 < iKey) ? (iKey-1) : iKey;
					break;
				}
			}
			fTime1 = (float)pRotAnimKey->arrKey[dwp1];
			fTime2 = (float)pRotAnimKey->arrKey[dwp2];
			fLerpValue = ((fTime2- fTime1) != 0) ? ((fTime - fTime1) / (fTime2 - fTime1)) : 0;

			//$B5e>u@~7AJd4V$7$F9g@.(B
			SmgQuaternion q, q1, q2;

			SetSmgQuaternionVal(&q1, pRotAnimKey->key_datas[dwp1][0],
				pRotAnimKey->key_datas[dwp1][1],
				pRotAnimKey->key_datas[dwp1][2],
				pRotAnimKey->key_datas[dwp1][3]);
			SetSmgQuaternionVal(&q2, -pRotAnimKey->key_datas[dwp2][0],
				pRotAnimKey->key_datas[dwp2][1],
				pRotAnimKey->key_datas[dwp2][2],
				pRotAnimKey->key_datas[dwp2][3]);
			CalcSmgQuaternionSlerp(&q, &q1, &q2, fLerpValue);

			//$B2sE>9TNs$r@8@.$7$+$1$k(B
			SetSmgMat4RotQuaternion(&matTemp, &q);
			CalcSmgMat4Multiply(&matResult, &matTemp, &matResult);

			bAnim = TRUE;
		}
		if(pTransAnimKey){
			//$BJ?9T0\F0$N%"%K%a(B
			dwp1 = dwp2 = 0;

			//$B;~4V$K$"$C$?%-!<%U%l!<%`$r8!:w(B
			fTime = (float)fmod((float)time, pTransAnimKey->arrKey[ pTransAnimKey->nKeys-1 ]);
			for(iKey=0; iKey<pTransAnimKey->nKeys; iKey++){
				if((float)pTransAnimKey->arrKey[iKey] > fTime){
					dwp2 = iKey;
					dwp1 = (0 < iKey) ? (iKey-1) : iKey;
					break;
				}
			}
			fTime1 = (float)pTransAnimKey->arrKey[dwp1];
			fTime2 = (float)pTransAnimKey->arrKey[dwp2];
			fLerpValue = ((fTime2 - fTime1) != 0) ? ((fTime - fTime1) / (fTime2 - fTime1)) : 0;

			//$B@~7AJd40$7$F9g@.(B
			SmgVertex vTrans;
			SmgVertex vTransTime1;
			SmgVertex vTransTime2;
			SetSmgVertexVal(&vTransTime1, pTransAnimKey->key_datas[dwp1][0],
				pTransAnimKey->key_datas[dwp1][1],
				pTransAnimKey->key_datas[dwp1][2]);
			SetSmgVertexVal(&vTransTime2, pTransAnimKey->key_datas[dwp2][0],
				pTransAnimKey->key_datas[dwp2][1],
				pTransAnimKey->key_datas[dwp2][2]);
			CalcLerpVertex(&vTrans, &vTransTime1, &vTransTime2, fLerpValue);

			//$BJ?9T0\F09TNs$r@8@.$7$+$1$k(B
			SetSmgMat4Trans(&matTemp, vTrans._d[0], vTrans._d[1], vTrans._d[2]);
			CalcSmgMat4Multiply(&matResult, &matTemp, &matResult);

			bAnim = TRUE;
		}
		else{
			//$BJ?9T0\F0$N%"%K%a$,L5$1$l$P%G%U%)%k%H$N0LCV$r;XDj(B
			SetSmgMat4Trans(&matTemp,
				GetSmgMat4Val(&(pFrame->transFormMat), 0, 3), 
				GetSmgMat4Val(&(pFrame->transFormMat), 0, 3),
				GetSmgMat4Val(&(pFrame->transFormMat), 0, 3));
			CalcSmgMat4Multiply(&matResult, &matTemp, &matResult);
		}
	}

	if(bAnim){
		CopySmgMat4(&(pFrame->animMat), &matResult);
	}

	//$B;R%U%l!<%`$N8F$S=P$7(B
	SmgFrame* pChild;
	for(pChild = pFrame->pFirstChildFrame; pChild; pChild=pChild->pSiblingFrame){
		SetSmgFrameTime(pChild, time);
	}
}

///////////////////////////////////
/*!
	$BJQ499TNs$N@8@.(B
	@param[in] pFrame
	@param[in] pMatCur $B8=:_$NJQ499TNs(B
*/
void UpdateSmgFrames(SmgFrame* pFrame, const SmgMat4* pMatCur)
{
	CalcSmgMat4Multiply(&(pFrame->combinedMat), &(pFrame->animMat), &(pFrame->transFormMat));
	CalcSmgMat4Multiply(&(pFrame->combinedMat), &(pFrame->combinedMat), pMatCur);

	//$B;R6!$N9TNsJQ49(B
	SmgFrame* pChild;
	for(pChild = pFrame->pFirstChildFrame; pChild; pChild = pChild->pSiblingFrame){
		UpdateSmgFrames(pChild, &(pFrame->combinedMat));
	}
}


///////////////////////////////////
/*!
	$B%F%9%/%A%c$N@8@.(B
*/
void GenSmgFrameTexture(SmgFrame* pFrame)
{
	if(!pFrame) return;

	if(pFrame->pMesh){
		GenSmgMeshTexture(pFrame->pMesh);
	}

	SmgFrame* pChild;
	for(pChild = pFrame->pFirstChildFrame; pChild; pChild=pChild->pSiblingFrame){
		GenSmgFrameTexture(pChild);
	}
}

/////////////////////////
/*!
	OpenGL$B$K$h$k%U%l!<%`$NIA2h(B
	@param[in] pFrame $BIA2h$9$k%U%l!<%`(B
*/
void DrawSmgFrameGL(const SmgFrame* pFrame, int draw_mode)
{
	if(!pFrame) return;

	//$B%b%G%j%s%0JQ49(B
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glLoadIdentity();
	//glMultMatrixd(pFrame->combinedMat._d);
	glMultMatrixd(pFrame->animMat._d);
	glMultMatrixd(pFrame->transFormMat._d);

	

	//$B%a%C%7%e$NI=<((B
	if(pFrame->pMesh){
		DrawSmgMeshGL(pFrame->pMesh, draw_mode);
	}

	

	//$B;R%U%l!<%`$NI=<((B
	SmgFrame* pChild;
	for(pChild = pFrame->pFirstChildFrame; pChild; pChild=pChild->pSiblingFrame){
		DrawSmgFrameGL(pChild, draw_mode);
	}

	glPopMatrix();
}
