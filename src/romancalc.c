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

void roman_numeral_str_clear(char* roman_numeral_str){
	(void)memset((void*)roman_numeral_str,0,MAX_STR_LEN_ROMAN_NUM);
}
char *roman_numeral_str_create(void){
	char *str = (char*)malloc(MAX_STR_LEN_ROMAN_NUM);
	roman_numeral_str_clear(str);
	return str;
}
void  roman_numeral_str_free(char* roman_numeral_str){
	free (roman_numeral_str);
}

int   rnum_check(char *rnum_str){						// check roman number string for valid digits
	char *rslt_ptr;										// result from stirng check
	if(rnum_str){										// if not give empty roman numer string check
		while(*rnum_str){								// check each digit see if valid roman numeral
			rslt_ptr = strchr(rdigits, toupper(*rnum_str));		// check current character against reference list
			if(rslt_ptr == NULL){						// if character is not roman numeral (in ref list)
				break;									// then exit out and report non valid value
			}
			rnum_str++;									// check next digit;
		}
	}
	else
		return -1;										// was given NULL string
	
														// if we did not make it to end of string
	if(*rnum_str)										// then there was a non-roman numeral characters
		return -1;										// invalid value
	return 0;
}


/* end of romancalc.c */
