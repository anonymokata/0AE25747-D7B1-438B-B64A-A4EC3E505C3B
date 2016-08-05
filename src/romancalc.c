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
#include <stdbool.h>
#define TSTR_LEN 100

char *rdigits="MDCLXVI";	// roman numerals in order

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

/*******************************************************
 * rnum_check check digits to ensure they are only roman
 * numerals.
 * input:
 *	     rnum_str  NULL terminated string
 * returns:
 *      0 input string rnum_str has only roman numerals
 *     -1 invalid character (non-roman numerals) found
 *        within the string
 *******************************************************/
int   rnum_check(char *rnum_str){						// check roman number string for valid digits
	char *rslt_ptr;										// result from stirng check
	if(rnum_str){										// if not give empty roman numer string check
		while(*rnum_str){								// check each digit see if valid roman numeral
			rslt_ptr = strchr(rdigits, toupper(*rnum_str));		// check current character against reference list
			if(rslt_ptr == NULL)						// if character is not roman numeral (in ref list)
				break;									// then exit out and report non valid value
			rnum_str++;									// check next digit;
		}	//while
	}	// if
	else
		return -1;										// was given NULL string
														// if we did not make it to end of string
	if(*rnum_str)										// then there was a non-roman numeral characters
		return -1;										// invalid value
	return 0;
} // end of rnum_check

/*******************************************************
 * rnum_subt_removal
 * removes subtractions from within roman numerals
 * it is easier to do roman math all 
 * in addition so we remove subtractions
 *	     rnum_str  NULL terminated string containg 
 *                 roman numeral
 * returns:
 *       NULL terminated string
 *     roman        replaced
 *     numeral      by
 *       iv         iiii
 *       ix         viii
 *       xl         xxxx
 *       xc         lxxxx
 *       cd         cccc
 *       cm         dcccc
 *******************************************************/
char *rnum_subt_removal(char *rnum_str){
	char * ch_rslt;
	char tstr[TSTR_LEN];
	char *cptr_dest = tstr;								// point to destination of next chunchk
	
	memset(tstr, 0, TSTR_LEN);
	if(rnum_str){										// ensure we were given a string
		if(strlen(rnum_str) >= 2){						// roman subtraction can only occur in 2 or more chars
			while(*rnum_str){
				if(strncmp(rnum_str, "IV", 2) == 0){		// 4
					strcpy(cptr_dest, "IIII");				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str += 2;							// move source pointer past unsubtracted pair
				} else if(strncmp(rnum_str, "IX", 2) == 0){	// 9
					strcpy(cptr_dest, "VIIII");				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str += 2;							// move source pointer past unsubtracted pair
				} else if(strncmp(rnum_str, "XL", 2) == 0){		// 40
					strcpy(cptr_dest, "XXXX");				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str += 2;							// move source pointer past unsubtracted pair
				} else if(strncmp(rnum_str, "XC", 2) == 0){		// 90
					strcpy(cptr_dest, "LXXXX");				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str += 2;							// move source pointer past unsubtracted pair
				} else if(strncmp(rnum_str, "CD", 2) == 0){		// 400
					strcpy(cptr_dest, "CCCC");				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str += 2;							// move source pointer past unsubtracted pair
				} else if(strncmp(rnum_str, "CM", 2) == 0){		// 900
					strcpy(cptr_dest, "DCCCC");				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str += 2;							// move source pointer past unsubtracted pair
				} else {									// else just sd in character
					*cptr_dest++ = *rnum_str++;				// and fix next source and destination
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

/*******************************************************
 * rnum_digit_group sort roman numerals by value in
 * correct order
 * input:
 *	     rnum_str  NULL terminated string
 * returns:
 *       null terminated string properly order by value
 
 *******************************************************/
char *rnum_digit_group(char *rnum_str){
	char str_out_tmp[TSTR_LEN];								// temp storage while grouping/sorting digits
	
	char *psrc;												// input ptr
	char *pdest;											// output ptr
	char *pref;												// roman numeral order reference value
	
	memset(str_out_tmp, 0, TSTR_LEN);						// init tstr null
	
	pdest = str_out_tmp;									// init output pointer
	for(pref = rdigits; *pref; pref++){						// step through roman digits in value order
		for(psrc  = rnum_str; *psrc; psrc++){				// step through values to be sorted
			if(*psrc == *pref)								// if digits in order are found
				*pdest++ = *pref;							// store in numerical value in order
		}
	}
	
	return strdup(str_out_tmp);								// return result
}

/*******************************************************
 * rnum_reduce reduce multiple roman numeral digits to
 * next higher value when necessary
 * input:
 *	     rnum_str  NULL terminated string
 * returns:
 *       null terminated string properly order by value
 *       if a value is reduced that may need to be
 *       reduced again, then we may ned to reduce again
 *       so we are not done and loop agian
 *******************************************************/
char *rnum_reduce(char *rnum_str){
	char str_in_tmp[TSTR_LEN];								// temp store input value for re-running loop
	char str_out_tmp[TSTR_LEN];								// temp storage while grouping/sorting digits
	
	char *psrc;												// input ptr
	char *pdest;											// output ptr
	bool done;												// exit when done
	
	memset(str_in_tmp, 0, TSTR_LEN);						// init tstr null
	strncpy(str_in_tmp, rnum_str, TSTR_LEN);				// store in temp storage
	done = false;											// init
	
	while(! done){
		done = true;										// assume done, and clear if further
															// reduction may need to occurr
		memset(str_out_tmp, 0, TSTR_LEN);					// init tstr null
		
		psrc  = str_in_tmp;									// point to input string
		pdest = str_out_tmp;								// init output pointer
		
		//"MDCLXVI";
		while(*psrc){										// until end of string
			if(strncmp("DD",psrc,2) == 0){					// if 500*2
				*pdest++ = 'M';								// then insert 1000
				psrc += 2;									// push past the 2 digits
			} else if(strncmp("CCCCC",psrc,5) == 0){		// if 100*5
				*pdest++ = 'D';								// then insert 500
				psrc += 5;									// push past the 5 digits
				done = false;								// reduced value, may need to reduce again
			} else if(strncmp("LL",psrc,2) == 0){			// if 50*2
				*pdest++ = 'C';								// then insert 100
				psrc += 2;									// push past the 2 digits
				done = false;								// reduced value, may need to reduce again
			} else if(strncmp("XXXXX",psrc,5) == 0){		// if 10*5
				*pdest++ = 'L';								// then insert 50
				psrc += 5;									// push past the 5 digits
				done = false;								// reduced value, may need to reduce again
			} else if(strncmp("VV",psrc,2) == 0){			// if 5*2
				*pdest++ = 'X';								// then insert 10
				psrc += 2;									// push past the 2 digits
				done = false;								// reduced value, may need to reduce again
			} else if(strncmp("IIIII",psrc,5) == 0){		// if 1*5
				*pdest++ = 'V';								// then insert 5
				psrc += 5;									// push past the 5 digits
				done = false;								// reduced value, may need to reduce again
			} else {										// non-reduced digit
				*pdest++ = *psrc++;							// store and bump forward
			}
		}
		if(!done){
			memset(str_in_tmp, 0, TSTR_LEN);				// init tstr null
			strncpy(str_in_tmp, str_out_tmp, TSTR_LEN);		// store in temp storage
		}
	}
	return strdup(str_out_tmp);								// return result
}


/* end of romancalc.c */
