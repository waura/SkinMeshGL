#include "SkinMeshGL/XLex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define READ_BUF_SIZE 512	//ファイル読み込みバッファサイズ
#define TOKEN_ARR_SIZE 400000 //トークン配列のサイズ
							//足りなくなった場合は新たにこのサイズ分確保

////////////////////////////////////////////////////
/*!
	最後尾が改行の場合それを\0に置き換える
*/
void chomp(char* str)
{
	int len = strlen(str);
	if(str[len-1] == '\n'){
		str[len-1] = '\0';
	}
}

////////////////////////////////////////////////////
/*!
	区切り文字かどうかを返す
	@param[in] c 調べる文字
	@return 区切り文字ならTRUE,そうでないならFALSEを返す
*/
BOOL isDelimiter(char c)
{
	int i;
	for(i=0; _DELIMITERS[i] != -1; i++){
		if(c == _DELIMITERS[i]){
			return TRUE;
		}
	}
	return FALSE;
}

////////////////////////////////////////////////////
/*!
	srcからcnt文字までの範囲の文字をdstにヌル文字を足してコピー
*/
void str_range_copy(char* dst, const char* src, int cnt)
{
	int i;
	for(i=0; i<cnt; i++){
		dst[i] = src[i];
	}
	dst[i] = '\0';
}

/////////////////////////////////////////////////////
/*!
	tokenをpTokensに追加する
*/
void add_token(XFILE_TOKENS* pTokens, char* token)
{
	if(pTokens->nTokens + 1 > pTokens->arr_token_size){
		//領域が足りなった場合は拡張する。
		//新領域確保
		char** new_arr = (char**) malloc(
			sizeof(char*) * (TOKEN_ARR_SIZE + pTokens->arr_token_size));
		//新領域にコピー
		int i;
		for(i=0; i<pTokens->arr_token_size; i++){
			new_arr[i] = pTokens->arr_token[i];
		}
		for(i=pTokens->arr_token_size; i<TOKEN_ARR_SIZE; i++){
			new_arr[i] = NULL;
		}

		//古い領域を開放
		free(pTokens->arr_token);
		//差し替え
		pTokens->arr_token = new_arr;
		pTokens->arr_token_size += TOKEN_ARR_SIZE;
	}

	pTokens->arr_token[ pTokens->nTokens++ ] = token;
}

////////////////////////////////////////////////////
/*!
	bufを解析してトークンに分割
*/
void split_token(XFILE_TOKENS* pTokens, const char* buf)
{
	int cnt_str=0; //コピー文字数カウント
	char* index_pC = (char*)&(buf[0]); //コピー開始位置を記憶

	int i;
	for(i=0; buf[i] != '\0'; i++){
		if(isDelimiter(buf[i])){ //区切り文字なら
			if(cnt_str){
				//コピーする文字があるならコピー
				char* token = (char*) malloc(sizeof(char)*(cnt_str+1));
				str_range_copy(token, index_pC, cnt_str);
				//tokensにtokenを追加
				add_token(pTokens, token);
			}
			//区切り文字をトークンとして出力
			char* token = (char*) malloc(sizeof(char)*2);
			str_range_copy(token, &(buf[i]), 1);
			add_token(pTokens, token);

			//
			cnt_str=0;
			index_pC = (char*)&(buf[i+1]);
		}
		else if(isspace(buf[i])){//空白文字
			if(cnt_str){
				//コピーする文字があるならコピー
				char* token = (char*) malloc(sizeof(char)*(cnt_str+1));
				str_range_copy(token, index_pC, cnt_str);
				//tokensにtokenを追加
				add_token(pTokens, token);
			}
			cnt_str=0;
			index_pC = (char*)&(buf[i+1]);
		}
		else{ //通常文字
			cnt_str++;
		}
	}

	if(cnt_str != 0){ //残りがあるならコピー
		char* token = (char*) malloc(sizeof(char)*(cnt_str+1));
		str_range_copy(token, index_pC, cnt_str);
		//tokensにtokenを追加
		add_token(pTokens, token);
	}
}

///////////////////////////////////////////////////
/*!
	Xファイル(テキスト形式)を字句解析してトークンズを返す。
	@param[in] path Xファイルパス
	@return トークン、失敗した場合はNULL
*/
XFILE_TOKENS* XLexFmtTxt(const char* path)
{
	int i;
	FILE *fp;
	if((fp = fopen(path, "r")) == NULL){
		return NULL;
	}

	//トークン構造体、生成、初期化
	XFILE_TOKENS* pTokens = (XFILE_TOKENS*) malloc(sizeof(XFILE_TOKENS));
	pTokens->nTokens = 0;
	pTokens->arr_token_size = TOKEN_ARR_SIZE;
	pTokens->arr_token = (char**) malloc(sizeof(char*) * TOKEN_ARR_SIZE);
	for(i=0; i<TOKEN_ARR_SIZE; i++){
		pTokens->arr_token[i] = NULL;
	}

	char buf[READ_BUF_SIZE];
	while(fgets(buf, READ_BUF_SIZE, fp) != NULL){
		chomp(buf); //改行文字消去
		split_token(pTokens, buf);
	}
	fclose(fp);

	return pTokens;
}


///////////////////////////////////////////////////
/*!
	トークンの後始末
	@param[in,out] pTokens 開放するトークンズのポインタへのポインタ
*/
void ReleaseTokens(XFILE_TOKENS** pTokens)
{
	if(*pTokens){
		int i;
		for(i=0; i<(*pTokens)->nTokens; i++){
			if((*pTokens)->arr_token[i]){
				free((*pTokens)->arr_token[i]);
				(*pTokens)->arr_token[i] = NULL;
			}
		}
		free(*pTokens);
		*pTokens = NULL;
	}
}

////////////////////////////////////////////////////
/*!
	トークンのテストダンプ
	@param[in] pTokens ダンプするトークンズ
*/
void DumpTokens(const XFILE_TOKENS* pTokens)
{
	if(!pTokens) return;

	int i;
	for(i=0; i<pTokens->nTokens; i++){
		printf("%s\n", pTokens->arr_token[i]);
	}
	printf("token_size = %d\n", pTokens->nTokens);
	printf("token_arr_size = %d\n", pTokens->arr_token_size);
}