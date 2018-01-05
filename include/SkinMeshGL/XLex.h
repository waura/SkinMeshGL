#ifndef _XLEX_H_
#define _XLEX_H_

#include "stdafx.h"

//////////////////////////////////////////////////////
/*
				Xファイル字句解析
*/

//トークン格納
typedef struct _XFILE_TOKENS {
	int nTokens; //トークン数
	int arr_token_size;
	char** arr_token; //トークン配列
} XFILE_TOKENS;

//区切り文字
static const char _DELIMITERS[] = { 
	'{',
	'}',
	',',
	';',
	-1,
};

///////////////////////////////////////////////////
/*!
	Xファイル(テキスト形式)を字句解析してトークンズを返す。
	@param[in] path Xファイルパス
	@return トークンズ、失敗した場合はNULL
*/
XFILE_TOKENS* XLexFmtTxt(const char* path);

///////////////////////////////////////////////////
/*!
	トークンの後始末
	@param[in,out] pTokens 開放するトークンズのポインタへのポインタ
*/
void ReleaseTokens(XFILE_TOKENS** pTokens);

////////////////////////////////////////////////////
/*!
	トークンのテストダンプ
	@param[in] pTokens ダンプするトークンズ
*/
void DumpTokens(const XFILE_TOKENS* pTokens);

#endif