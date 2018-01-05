#include "SkinMeshGL/XLex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define READ_BUF_SIZE 512	//$B%U%!%$%kFI$_9~$_%P%C%U%!%5%$%:(B
#define TOKEN_ARR_SIZE 400000 //$B%H!<%/%sG[Ns$N%5%$%:(B
							//$BB-$j$J$/$J$C$?>l9g$O?7$?$K$3$N%5%$%:J,3NJ](B

////////////////////////////////////////////////////
/*!
	$B:G8eHx$,2~9T$N>l9g$=$l$r(B\0$B$KCV$-49$($k(B
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
	$B6h@Z$jJ8;z$+$I$&$+$rJV$9(B
	@param[in] c $BD4$Y$kJ8;z(B
	@return $B6h@Z$jJ8;z$J$i(BTRUE,$B$=$&$G$J$$$J$i(BFALSE$B$rJV$9(B
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
	src$B$+$i(Bcnt$BJ8;z$^$G$NHO0O$NJ8;z$r(Bdst$B$K%L%kJ8;z$rB-$7$F%3%T!<(B
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
	token$B$r(BpTokens$B$KDI2C$9$k(B
*/
void add_token(XFILE_TOKENS* pTokens, char* token)
{
	if(pTokens->nTokens + 1 > pTokens->arr_token_size){
		//$BNN0h$,B-$j$J$C$?>l9g$O3HD%$9$k!#(B
		//$B?7NN0h3NJ](B
		char** new_arr = (char**) malloc(
			sizeof(char*) * (TOKEN_ARR_SIZE + pTokens->arr_token_size));
		//$B?7NN0h$K%3%T!<(B
		int i;
		for(i=0; i<pTokens->arr_token_size; i++){
			new_arr[i] = pTokens->arr_token[i];
		}
		for(i=pTokens->arr_token_size; i<TOKEN_ARR_SIZE; i++){
			new_arr[i] = NULL;
		}

		//$B8E$$NN0h$r3+J|(B
		free(pTokens->arr_token);
		//$B:9$7BX$((B
		pTokens->arr_token = new_arr;
		pTokens->arr_token_size += TOKEN_ARR_SIZE;
	}

	pTokens->arr_token[ pTokens->nTokens++ ] = token;
}

////////////////////////////////////////////////////
/*!
	buf$B$r2r@O$7$F%H!<%/%s$KJ,3d(B
*/
void split_token(XFILE_TOKENS* pTokens, const char* buf)
{
	int cnt_str=0; //$B%3%T!<J8;z?t%+%&%s%H(B
	char* index_pC = (char*)&(buf[0]); //$B%3%T!<3+;O0LCV$r5-21(B

	int i;
	for(i=0; buf[i] != '\0'; i++){
		if(isDelimiter(buf[i])){ //$B6h@Z$jJ8;z$J$i(B
			if(cnt_str){
				//$B%3%T!<$9$kJ8;z$,$"$k$J$i%3%T!<(B
				char* token = (char*) malloc(sizeof(char)*(cnt_str+1));
				str_range_copy(token, index_pC, cnt_str);
				//tokens$B$K(Btoken$B$rDI2C(B
				add_token(pTokens, token);
			}
			//$B6h@Z$jJ8;z$r%H!<%/%s$H$7$F=PNO(B
			char* token = (char*) malloc(sizeof(char)*2);
			str_range_copy(token, &(buf[i]), 1);
			add_token(pTokens, token);

			//
			cnt_str=0;
			index_pC = (char*)&(buf[i+1]);
		}
		else if(isspace(buf[i])){//$B6uGrJ8;z(B
			if(cnt_str){
				//$B%3%T!<$9$kJ8;z$,$"$k$J$i%3%T!<(B
				char* token = (char*) malloc(sizeof(char)*(cnt_str+1));
				str_range_copy(token, index_pC, cnt_str);
				//tokens$B$K(Btoken$B$rDI2C(B
				add_token(pTokens, token);
			}
			cnt_str=0;
			index_pC = (char*)&(buf[i+1]);
		}
		else{ //$BDL>oJ8;z(B
			cnt_str++;
		}
	}

	if(cnt_str != 0){ //$B;D$j$,$"$k$J$i%3%T!<(B
		char* token = (char*) malloc(sizeof(char)*(cnt_str+1));
		str_range_copy(token, index_pC, cnt_str);
		//tokens$B$K(Btoken$B$rDI2C(B
		add_token(pTokens, token);
	}
}

///////////////////////////////////////////////////
/*!
	X$B%U%!%$%k(B($B%F%-%9%H7A<0(B)$B$r;z6g2r@O$7$F%H!<%/%s%:$rJV$9!#(B
	@param[in] path X$B%U%!%$%k%Q%9(B
	@return $B%H!<%/%s!"<:GT$7$?>l9g$O(BNULL
*/
XFILE_TOKENS* XLexFmtTxt(const char* path)
{
	int i;
	FILE *fp;
	if((fp = fopen(path, "r")) == NULL){
		return NULL;
	}

	//$B%H!<%/%s9=B$BN!"@8@.!"=i4|2=(B
	XFILE_TOKENS* pTokens = (XFILE_TOKENS*) malloc(sizeof(XFILE_TOKENS));
	pTokens->nTokens = 0;
	pTokens->arr_token_size = TOKEN_ARR_SIZE;
	pTokens->arr_token = (char**) malloc(sizeof(char*) * TOKEN_ARR_SIZE);
	for(i=0; i<TOKEN_ARR_SIZE; i++){
		pTokens->arr_token[i] = NULL;
	}

	char buf[READ_BUF_SIZE];
	while(fgets(buf, READ_BUF_SIZE, fp) != NULL){
		chomp(buf); //$B2~9TJ8;z>C5n(B
		split_token(pTokens, buf);
	}
	fclose(fp);

	return pTokens;
}


///////////////////////////////////////////////////
/*!
	$B%H!<%/%s$N8e;OKv(B
	@param[in,out] pTokens $B3+J|$9$k%H!<%/%s%:$N%]%$%s%?$X$N%]%$%s%?(B
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
	$B%H!<%/%s$N%F%9%H%@%s%W(B
	@param[in] pTokens $B%@%s%W$9$k%H!<%/%s%:(B
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