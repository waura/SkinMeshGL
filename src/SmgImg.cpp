#include <SkinMeshGL/SmgImg.h>

SmgImg* LoadBmpSmgImg(const char* path)
{
	SmgImg* pSmgImg = NULL;
	FILE *fp;
	int start_y, stop_y;
	int imgsize;   //$B%$%a!<%8$N%5%$%:(B
	int imgHeight; //$B2hA|9b$5(B
	int imgWidth;  //$B2hA|I}(B
	int colbit;    //1$B2hAG$"$?$j$N%S%C%H?t(B
	unsigned char* buf, *buf_top; //$B2hA|%G!<%?$H$;$N@hF,%]%$%s%?(B
	BMPFILEHEADER bf;
	BMPINFOHEADER bi;

	if((fp = fopen(path, "rb")) == NULL){
		return NULL;
	}

	//$B%X%C%@<hF@(B 
	if(fread((void*)&(bf.bfType), sizeof(unsigned short), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bf.bfSize), sizeof(unsigned long), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bf.bfReserved1), sizeof(unsigned short), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bf.bfReserved2), sizeof(unsigned short), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bf.bfOffBits), sizeof(unsigned long), 1, fp) != 1){
		return NULL;
	}
	//
	if(fread((void*)&(bi.biSize), sizeof(unsigned long), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bi.biWidth), sizeof(long), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bi.biHeight), sizeof(long), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bi.biPlanes), sizeof(unsigned short), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bi.biBitCount), sizeof(unsigned short), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bi.biCompression), sizeof(unsigned long), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bi.biSizeImage), sizeof(unsigned long), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bi.biXPixPerMeter), sizeof(long), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bi.biYPixPerMeter), sizeof(long), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bi.biClrUsed),sizeof(unsigned long), 1, fp) != 1){
		return NULL;
	}
	if(fread((void*)&(bi.biClrImporant), sizeof(unsigned long), 1, fp) != 1){
		return NULL;
	}

	//$B%U%!%$%k%U%)!<%^%C%H%A%'%C%/(B
	if(bf.bfType != *(unsigned short*)"BM")
		return NULL;
	int size = sizeof(BMPINFOHEADER);
	if(bi.biSize != sizeof(BMPINFOHEADER))
		return NULL;
	if(bi.biCompression != 0)
		return NULL;

	imgsize = bi.biSizeImage;
	colbit = bi.biBitCount; //1$B?'$"$?$j$N%S%C%H?t(B
	imgWidth = bi.biWidth;
	imgHeight = bi.biHeight;


	//24bit bmp $B0J30$OFI$^$J$$(B
	if(colbit != 24)
		return NULL;

	//$B%$%a!<%8%G!<%?<hF@(B
	buf_top = buf = (unsigned char*) malloc(imgsize);
	if(buf == NULL){
		return NULL;
	}
	if(fread((void*)buf, 1, imgsize, fp) != imgsize){
		free(buf_top);
		return NULL;
	}

	//
	pSmgImg = (SmgImg*) malloc(sizeof(SmgImg));
	if(pSmgImg == NULL){
		free(buf_top);
		return NULL;
	}
	pSmgImg->width = imgWidth;
	pSmgImg->height = imgHeight;
	//pSmgImg->_data = (unsigned char*) malloc(sizeof(unsigned char) * imgWidth * imgHeight *4);
	pSmgImg->_data = (unsigned char*) malloc(sizeof(unsigned char) * imgWidth * imgHeight *3);
	if(pSmgImg->_data == NULL){
		free(buf_top);
		return NULL;
	}

	//$B%G!<%?$rE83+(B
	int x,y;
	start_y=0;
	stop_y = imgHeight;
	for(y=start_y; y<stop_y; y++){
		for(x=0; x<imgWidth; x++){
			//pSmgImg->_data[x + y * imgHeight + 3] = 255;      //a
			pSmgImg->_data[x + (imgHeight-y) * imgHeight + 2] = *(buf++); //b
			pSmgImg->_data[x + (imgHeight-y) * imgHeight + 1] = *(buf++); //g
			pSmgImg->_data[x + (imgHeight-y) * imgHeight + 0] = *(buf++); //r
		}
	}

	free(buf_top);
	fclose(fp);
	return pSmgImg;
}

void ReleaseSmgImg(SmgImg** pSmgImg)
{
	if(*pSmgImg){
		if((*pSmgImg)->_data){
			free((*pSmgImg)->_data);
			(*pSmgImg)->_data = NULL;
		}
		free(*pSmgImg);
		*pSmgImg = NULL;
	}
}