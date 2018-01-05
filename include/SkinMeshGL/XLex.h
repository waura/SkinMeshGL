#ifndef _XLEX_H_
#define _XLEX_H_

#include "stdafx.h"

//////////////////////////////////////////////////////
/*
				X$B%U%!%$%k;z6g2r@O(B
*/

//$B%H!<%/%s3JG<(B
typedef struct _XFILE_TOKENS {
	int nTokens; //$B%H!<%/%s?t(B
	int arr_token_size;
	char** arr_token; //$B%H!<%/%sG[Ns(B
} XFILE_TOKENS;

//$B6h@Z$jJ8;z(B
static const char _DELIMITERS[] = { 
	'{',
	'}',
	',',
	';',
	-1,
};

///////////////////////////////////////////////////
/*!
	X$B%U%!%$%k(B($B%F%-%9%H7A<0(B)$B$r;z6g2r@O$7$F%H!<%/%s%:$rJV$9!#(B
	@param[in] path X$B%U%!%$%k%Q%9(B
	@return $B%H!<%/%s%:!"<:GT$7$?>l9g$O(BNULL
*/
XFILE_TOKENS* XLexFmtTxt(const char* path);

///////////////////////////////////////////////////
/*!
	$B%H!<%/%s$N8e;OKv(B
	@param[in,out] pTokens $B3+J|$9$k%H!<%/%s%:$N%]%$%s%?$X$N%]%$%s%?(B
*/
void ReleaseTokens(XFILE_TOKENS** pTokens);

////////////////////////////////////////////////////
/*!
	$B%H!<%/%s$N%F%9%H%@%s%W(B
	@param[in] pTokens $B%@%s%W$9$k%H!<%/%s%:(B
*/
void DumpTokens(const XFILE_TOKENS* pTokens);

#endif