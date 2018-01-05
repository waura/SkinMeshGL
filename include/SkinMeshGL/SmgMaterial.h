#ifndef _SMGMATERIAL_H_
#define _SMGMATERIAL_H_

#include "SmgImg.h"

typedef struct _SmgMaterial {
	float color[4];     //$B4pK\?'(B(RGBA)
	float power;        //$B%O%$%i%$%H6/EY(B
	float specular[3];  //$B%O%$%i%$%H?'(B(RGB)
	float emissiver[3]; //$BH/9T?'(B
	char* texture_path;  //$B%F%/%9%A%c%Q%9(B
	SmgImg* pTexture;    //$B%F%/%9%A%c(B
	unsigned int glTexName;
} SmgMaterial;

//
void DumpSmgMaterial(const SmgMaterial* pMaterial);

//$B=i4|2=(B
void InitSmgMaterial(SmgMaterial* pMaterial);

//$B4pK\?'(B
void SetSmgMaterialColor(SmgMaterial* pMaterial, double r, double g, double b, double a);
//$B%O%$%i%$%H6/EY(B
void SetSmgMaterialPower(SmgMaterial* pMaterial, double power);
//$B%O%$%i%$%H?'(B
void SetSmgMaterialSpecular(SmgMaterial* pMaterial, double r, double g, double b);
//$BH/9T?'(B
void SetSmgMaterialEmissive(SmgMaterial* pMaterial, double r, double g, double b);
//$B%F%/%9%A%c%Q%9(B
void CreateSmgMaterialTexture(SmgMaterial* pMaterial, const char* path);
void ReleaseSmgMaterialTexture(SmgMaterial* pMaterial);
#endif //_SMGMATERIAL_H_