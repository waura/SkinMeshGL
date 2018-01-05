#include <SkinMeshGL/SmgMat.h>

void DumpSmgMat4(const SmgMat4* pMat)
{
	int i,j;
	double d;
	for(i=0; i<4; i++){
		printf("| ");
		for(j=0; j<4; j++){
			d = GetSmgMat4Val(pMat, i, j);
			printf("%f ",d); 
		}
		printf(" |\n");
	}
	printf("\n");
}

//src$B$r(Bdst$B$K%3%T!<$9$k(B
void CopySmgMat4(SmgMat4* dst, const SmgMat4* src)
{
	int i,j;
	double d;
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			d = GetSmgMat4Val(src, i, j);
			SetSmgMat4Val(dst, i, j, d);
		}
	}
}

//row$B9T(Bcol$BNs$NCM$rJV$9(B
//row,col$B$H$b$K(B(0$B!A(B3)
double GetSmgMat4Val(const SmgMat4* pMat, int row, int col)
{
	return pMat->_d[row + col*4];
}

//row$B9T(Bcol$BNs$K(Bval$B$rBeF~$9$k(B
void SetSmgMat4Val(SmgMat4* pMat, int row, int col, double val)
{
	pMat->_d[row + col*4] = val;
}

//src$B$rE>CV$7$?$b$N$r(Bdst$B$K$$$l$k(B
void TransposeSmgMat4(SmgMat4* dst, const SmgMat4* src)
{
	int i,j;
	double d;
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			d = GetSmgMat4Val(src, j, i);
			SetSmgMat4Val(dst, i, j, d);
		}
	}
}


//pMat$B$rC10L9TNs$K$9$k(B
void SetSmgMat4Identity(SmgMat4* pMat)
{
	//$BC10L9TNs$G=i4|2=(B
	SetSmgMat4Val(pMat, 0, 0, 1.0);
	SetSmgMat4Val(pMat, 0, 1, 0.0);
	SetSmgMat4Val(pMat, 0, 2, 0.0);
	SetSmgMat4Val(pMat, 0, 3, 0.0);
	SetSmgMat4Val(pMat, 1, 0, 0.0);
	SetSmgMat4Val(pMat, 1, 1, 1.0);
	SetSmgMat4Val(pMat, 1, 2, 0.0);
	SetSmgMat4Val(pMat, 1, 3, 0.0);
	SetSmgMat4Val(pMat, 2, 0, 0.0);
	SetSmgMat4Val(pMat, 2, 1, 0.0);
	SetSmgMat4Val(pMat, 2, 2, 1.0);
	SetSmgMat4Val(pMat, 2, 3, 0.0);
	SetSmgMat4Val(pMat, 3, 0, 0.0);
	SetSmgMat4Val(pMat, 3, 1, 0.0);
	SetSmgMat4Val(pMat, 3, 2, 0.0);
	SetSmgMat4Val(pMat, 3, 3, 1.0);
}

//pMat$B$r3HBg=L>.9TNs$K$9$k(B
void SetSmgMat4Scaling(SmgMat4* pMat, double x_scale, double y_scale, double z_scale)
{
	SetSmgMat4Val(pMat, 0, 0, x_scale);
	SetSmgMat4Val(pMat, 0, 1, 0.0);
	SetSmgMat4Val(pMat, 0, 2, 0.0);
	SetSmgMat4Val(pMat, 0, 3, 0.0);
	SetSmgMat4Val(pMat, 1, 0, 0.0);
	SetSmgMat4Val(pMat, 1, 1, y_scale);
	SetSmgMat4Val(pMat, 1, 2, 0.0);
	SetSmgMat4Val(pMat, 1, 3, 0.0);
	SetSmgMat4Val(pMat, 2, 0, 0.0);
	SetSmgMat4Val(pMat, 2, 1, 0.0);
	SetSmgMat4Val(pMat, 2, 2, z_scale);
	SetSmgMat4Val(pMat, 2, 3, 0.0);
	SetSmgMat4Val(pMat, 3, 0, 0.0);
	SetSmgMat4Val(pMat, 3, 1, 0.0);
	SetSmgMat4Val(pMat, 3, 2, 0.0);
	SetSmgMat4Val(pMat, 3, 3, 1.0);
}

//$B%/%)!<%?%K%*%s$+$i2sE>9TNs$KJQ49$9$k(B
void SetSmgMat4RotQuaternion(SmgMat4* pMat, const SmgQuaternion* pQ)
{
	double x, y, z, w;
	GetSmgQuaternionVal(pQ, &x, &y, &z, &w);

	SetSmgMat4Val(pMat, 0, 0, 1.0 - 2.0*(y*y + z*z));
	SetSmgMat4Val(pMat, 0, 1, 2.0*(x*y + w*z));
	SetSmgMat4Val(pMat, 0, 2, 2.0*(x*z - w*z));
	SetSmgMat4Val(pMat, 0, 3, 0.0);
	SetSmgMat4Val(pMat, 1, 0, 2.0*(x*y - w*z));
	SetSmgMat4Val(pMat, 1, 1, 1.0 - 2.0*(x*x + z*z));
	SetSmgMat4Val(pMat, 1, 2, 2.0*(y*z + w*x));
	SetSmgMat4Val(pMat, 1, 3, 0.0);
	SetSmgMat4Val(pMat, 2, 0, 2.0*(x*z + w*y));
	SetSmgMat4Val(pMat, 2, 1, 2.0*(y*z - w*x));
	SetSmgMat4Val(pMat, 2, 2, 1.0 - 2.0*(x*x + y*y));
	SetSmgMat4Val(pMat, 2, 3, 0.0);
	SetSmgMat4Val(pMat, 3, 0, 0.0);
	SetSmgMat4Val(pMat, 3, 1, 0.0);
	SetSmgMat4Val(pMat, 3, 2, 0.0);
	SetSmgMat4Val(pMat, 3, 3, 1.0);
}

//$BJ?9T0\F09TNs$r@8@.$9$k(B
void SetSmgMat4Trans(SmgMat4* pMat, double x, double y, double z)
{
	SetSmgMat4Val(pMat, 0, 0, 1.0);
	SetSmgMat4Val(pMat, 0, 1, 0.0);
	SetSmgMat4Val(pMat, 0, 2, 0.0);
	SetSmgMat4Val(pMat, 0, 3, x);
	SetSmgMat4Val(pMat, 1, 0, 0.0);
	SetSmgMat4Val(pMat, 1, 1, 1.0);
	SetSmgMat4Val(pMat, 1, 2, 0.0);
	SetSmgMat4Val(pMat, 1, 3, y);
	SetSmgMat4Val(pMat, 2, 0, 0.0);
	SetSmgMat4Val(pMat, 2, 1, 0.0);
	SetSmgMat4Val(pMat, 2, 2, 1.0);
	SetSmgMat4Val(pMat, 2, 3, z);
	SetSmgMat4Val(pMat, 3, 0, 0.0);
	SetSmgMat4Val(pMat, 3, 1, 0.0);
	SetSmgMat4Val(pMat, 3, 2, 0.0);
	SetSmgMat4Val(pMat, 3, 3, 1.0);
}


void CalcSmgMat4Multiply(SmgMat4* dst, const SmgMat4* src1, const SmgMat4* src2)
{
	SmgMat4 calc;
	int i,j,k;
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			double sum=0.0;
			for(k=0; k<4; k++){
				sum += GetSmgMat4Val(src1,i, k) * GetSmgMat4Val(src2, k, j);
			}
			SetSmgMat4Val(&calc, i, j, sum);
		}
	}

	CopySmgMat4(dst, &calc);
}