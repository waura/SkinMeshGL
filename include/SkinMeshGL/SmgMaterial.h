#ifndef _SMGMATERIAL_H_
#define _SMGMATERIAL_H_

#include "SmgImg.h"

typedef struct _SmgMaterial {
	float color[4];     //基本色(RGBA)
	float power;        //ハイライト強度
	float specular[3];  //ハイライト色(RGB)
	float emissiver[3]; //発行色
	char* texture_path;  //テクスチャパス
	SmgImg* pTexture;    //テクスチャ
	unsigned int glTexName;
} SmgMaterial;

//
void DumpSmgMaterial(const SmgMaterial* pMaterial);

//初期化
void InitSmgMaterial(SmgMaterial* pMaterial);

//基本色
void SetSmgMaterialColor(SmgMaterial* pMaterial, double r, double g, double b, double a);
//ハイライト強度
void SetSmgMaterialPower(SmgMaterial* pMaterial, double power);
//ハイライト色
void SetSmgMaterialSpecular(SmgMaterial* pMaterial, double r, double g, double b);
//発行色
void SetSmgMaterialEmissive(SmgMaterial* pMaterial, double r, double g, double b);
//テクスチャパス
void CreateSmgMaterialTexture(SmgMaterial* pMaterial, const char* path);
void ReleaseSmgMaterialTexture(SmgMaterial* pMaterial);
#endif //_SMGMATERIAL_H_