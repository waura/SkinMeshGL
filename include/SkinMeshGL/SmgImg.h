#ifndef _SMGIMG_H_
#define _SMGIMG_H_

#include "stdafx.h"

typedef struct _BMPFILEHEADER{
  unsigned short bfType;
  unsigned long  bfSize;
  unsigned short bfReserved1;
  unsigned short bfReserved2;
  unsigned long  bfOffBits;
}BMPFILEHEADER;

typedef struct _BMPINFOHEADER{
    unsigned long  biSize;
    long           biWidth;
    long           biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned long  biCompression;
    unsigned long  biSizeImage;
    long           biXPixPerMeter;
    long           biYPixPerMeter;
    unsigned long  biClrUsed;
    unsigned long  biClrImporant;
}BMPINFOHEADER;

typedef struct _SmgImg {
	int width;
	int height;
	short depth;
	unsigned char* _data;
	//unsigned char _data[128][128][3];
} SmgImg;

SmgImg* LoadBmpSmgImg(const char* path);
void ReleaseSmgImg(SmgImg** pSmgImg);
#endif //_SMGIMG_H_