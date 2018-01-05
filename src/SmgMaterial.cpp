#include "SkinMeshGL/SmgMaterial.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//
void DumpSmgMaterial(const SmgMaterial* pMaterial)
{
	if(!pMaterial) return;

	int i;
	printf("----material-----\n");
	
	printf("color: ");
	for(i=0; i<4; i++){
		printf("%f ", pMaterial->color[i]);
	}
	printf("\n");


	printf("power: %f\n", pMaterial->power);

	printf("specular: ");
	for(i=0; i<3; i++){
		printf("%f ", pMaterial->specular[i]);
	}
	printf("\n");

	printf("emissiver: ");
	for(i=0; i<3; i++){
		printf("%f ", pMaterial->emissiver[i]);
	}
	printf("\n");

	if(pMaterial->texture_path){
		printf("texture_path: %s\n", pMaterial->texture_path);
	}

	printf("-----------------\n");
}

//$B=i4|2=(B
void InitSmgMaterial(SmgMaterial* pMaterial)
{
	memset(pMaterial, 0, sizeof(SmgMaterial));
}

//$B4pK\?'(B
void SetSmgMaterialColor(SmgMaterial* pMaterial, double r, double g, double b, double a)
{
	if(pMaterial){
		pMaterial->color[0] = r;
		pMaterial->color[1] = g;
		pMaterial->color[2] = b;
		pMaterial->color[3] = a;
	}
}

//$B%O%$%i%$%H6/EY(B
void SetSmgMaterialPower(SmgMaterial *pMaterial, double power)
{
	if(pMaterial){
		pMaterial->power = power;
	}
}

//$B%O%$%i%$%H?'(B
void SetSmgMaterialSpecular(SmgMaterial* pMaterial, double r, double g, double b)
{
	if(pMaterial){
		pMaterial->specular[0] = r;
		pMaterial->specular[1] = g;
		pMaterial->specular[2] = b;
	}
}

//$BH/9T?'(B
void SetSmgMaterialEmissive(SmgMaterial* pMaterial, double r, double g, double b)
{
	if(pMaterial){
		pMaterial->emissiver[0] = r;
		pMaterial->emissiver[1] = g;
		pMaterial->emissiver[2] = b;
	}
}

//$B%F%/%9%A%c%Q%9(B
void CreateSmgMaterialTexture(SmgMaterial* pMaterial, const char* path)
{
	if(pMaterial){
		if(pMaterial->texture_path){
			free(pMaterial->texture_path);
		}

		int len = strlen(path);
		pMaterial->texture_path = (char*) malloc(sizeof(char) * (len+1));
		strcpy(pMaterial->texture_path, path);

		//
		pMaterial->pTexture = LoadBmpSmgImg(path);
	}
}

void ReleaseSmgMaterialTexture(SmgMaterial* pMaterial)
{
	if(!pMaterial) return;

	if(pMaterial->texture_path){
		free(pMaterial->texture_path);
		pMaterial->texture_path = NULL;

		ReleaseSmgImg(&(pMaterial->pTexture));
	}
}