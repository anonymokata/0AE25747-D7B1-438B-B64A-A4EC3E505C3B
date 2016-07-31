/*******************************************
 *  Roman calculator                       *
 *  20160730   July-30-2016 created        *
 *  Micah Wilson                           *
 *******************************************/
#include "romancalc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *rdigits="IVXLCDM";	//roman numerals in order

char *roman_numeral_str_create(void){
	char *str = (char*)malloc(MAX_STR_LEN_ROMAN_NUM);
	roman_numeral_str_clear(str);
	return str;
}
void roman_numeral_str_clear(char* roman_numeral_str){
	(void)memset((void*)roman_numeral_str,0,MAX_STR_LEN_ROMAN_NUM);
}
void  roman_numeral_str_free(char* roman_numeral_str){
	free (roman_numeral_str);
}

int   rnum_check(char *rnum_str){						// check roman number string for valid digits
	if(rnum_str){
		
		return 0;
	}
	return -1;	// was given NULL string or invalid value
}