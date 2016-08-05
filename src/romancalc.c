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

void rnum_str_clear(char* roman_numeral_str){
	(void)memset((void*)roman_numeral_str,0,MAX_STR_LEN_ROMAN_NUM);
}
char *rnum_str_create(void){
	char *str = (char*)malloc(MAX_STR_LEN_ROMAN_NUM);
	rnum_str_clear(str);
	return str;
}
void  rnum_str_free(char* roman_numeral_str){
	free (roman_numeral_str);
}

int   rnum_check(char *rnum_str){						// check roman number string for valid digits
	char *rslt_ptr;										// result from stirng check
	if(rnum_str){										// if not give empty roman numer string check
		while(*rnum_str){								// check each digit see if valid roman numeral
			rslt_ptr = strchr(rdigits, toupper(*rnum_str));		// check current character against reference list
			if(rslt_ptr == NULL)						// if character is not roman numeral (in ref list)
				break;									// then exit out and report non valid value
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

/*************************************
 * rnum_subt_removal
 * it is easier to do roman math all 
 * in addition so we remove subtractions
 *************************************/
char *rnum_subt_removal(char *rnum_str){
#define TSTR_LEN 100
	char * ch_rslt;
	char tstr[TSTR_LEN];
	char tmp_str_cmp[3];								// store next 2 chars from input string
	memset(tmp_str_cmp,0,3);
	char *cptr_dest = tstr;								// point to destination of next chunchk
	memset(tstr, 0, TSTR_LEN);
	if(rnum_str){										// ensure we were given a string
		if(strlen(rnum_str) >= 2){						// roman subtraction can only occur in 2 or more chars
			while(*rnum_str){
				strncpy(tmp_str_cmp,rnum_str,2);			// get next 2 chars to compare
				if(strcmp(tmp_str_cmp, "IV") == 0){			// 4
					strcpy(cptr_dest, "IIII");				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str++; rnum_str++;					// move source pointer past unsubtracted pair
				} else if(strcmp(tmp_str_cmp, "IX") == 0){		// 9
					strcpy(cptr_dest, "VIIII");				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str++; rnum_str++;					// move source pointer past unsubtracted pair
				} else if(strcmp(tmp_str_cmp, "XL") == 0){		// 40
					strcpy(cptr_dest, "XXXX");				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str++; rnum_str++;					// move source pointer past unsubtracted pair
				} else if(strcmp(tmp_str_cmp, "XC") == 0){		// 90
					strcpy(cptr_dest, "LXXXX");				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str++; rnum_str++;					// move source pointer past unsubtracted pair
				} else if(strcmp(tmp_str_cmp, "CD") == 0){		// 400
					strcpy(cptr_dest, "CCCC");				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str++; rnum_str++;					// move source pointer past unsubtracted pair
				} else if(strcmp(tmp_str_cmp, "CM") == 0){		// 900
					strcpy(cptr_dest, "DCCCC");				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str++; rnum_str++;					// move source pointer past unsubtracted pair
				} else {									// else just sd in character
					*cptr_dest++ = *rnum_str++;					// and fix next source and destination
				}
			}
			ch_rslt = strdup(tstr);							// use strdup to alloc memory
			return ch_rslt;
		}
		else
			return rnum_str;
	}
	return NULL;
}

char *rnum_digit_group(char *rnum_str){
	return strdup(rnum_str);
}


/* end of romancalc.c */
