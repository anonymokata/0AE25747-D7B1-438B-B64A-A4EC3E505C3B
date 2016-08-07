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

// allows for expansion and contraction of roman numerals
#define TSTR_LEN (MAX_STR_LEN_ROMAN_NUM * 16)

// single digit numerals
#define RN_1000 "M"
#define RN_500  "D"
#define RN_100  "C"
#define RN_50   "L"
#define RN_10   "X"
#define RN_5    "V"
#define RN_1    "I"

// proper multi numeral sequences
#define RN_900  RN_100 RN_1000
#define RN_400  RN_100 RN_500
#define RN_90   RN_10  RN_100
#define RN_40   RN_10  RN_50
#define RN_9    RN_1   RN_10
#define RN_4    RN_1   RN_5

// improper multi numeral sequences
#define TWO_500s  RN_500 RN_500
#define TWO_50s   RN_50  RN_50
#define TWO_5s    RN_5   RN_5

#define FIVE_100s RN_100 RN_100 RN_100 RN_100 RN_100
#define FIVE_10s  RN_10  RN_10  RN_10  RN_10  RN_10
#define FIVE_1s   RN_1   RN_1   RN_1   RN_1   RN_1

#define FOUR_100s RN_100 RN_100 RN_100 RN_100
#define FOUR_10s  RN_10  RN_10  RN_10  RN_10
#define FOUR_1s   RN_1   RN_1   RN_1   RN_1

#define IMP_900 RN_500 FOUR_100s
#define IMP_400 FOUR_100s
#define IMP_90  RN_50  FOUR_10s
#define IMP_40  FOUR_10s
#define IMP_9   RN_5   FOUR_1s
#define IMP_4   FOUR_1s

// addition delimeter
#define ADD_DELIMETER "+"

char *rdigits=RN_1000 RN_500 RN_100 RN_50 RN_10 RN_5 RN_1;	// roman numerals in order


// returnable error for user access
static int rn_err = RNUM_ERR_NONE;							// initialize error

void rnum_error_clear(void){
	rn_err = RNUM_ERR_NONE;
}

int rnum_error_get_last_clear(void){
	int lcl_err;
	lcl_err = rn_err;										// temp store so we can clear it
	rnum_error_clear();										// clear up the error
	return lcl_err;
}

void rnum_str_clear(char* roman_numeral_str){
	(void)memset((void*)roman_numeral_str,0,MAX_STR_LEN_ROMAN_NUM+1); // null terminated
}

rn_pair_strct_type * rnum_pair_create(void){
	rn_pair_strct_type *rn_pair = malloc (sizeof (rn_pair_strct_type));
	if (rn_pair == NULL)
	{
		return NULL;
	}
	
	// initialize values
	(*rn_pair).num_str_1	= NULL;
	(*rn_pair).num_str_2	= NULL;
	(*rn_pair).result_str	= NULL;
	(*rn_pair).err		= RNUM_ERR_NONE;
	
	return rn_pair;						// return value
}

void  rnum_str_free(rn_pair_strct_type * rnum_pair){
	if(rnum_pair){
		if((*rnum_pair).num_str_1)
			free((*rnum_pair).num_str_1);
		if((*rnum_pair).num_str_2)
			free((*rnum_pair).num_str_2);
		if((*rnum_pair).result_str)
			free((*rnum_pair).result_str);
		free (rnum_pair);
	}
}

//////////////////////////////////////////
// Stores the trimmed input string into the given output buffer, which must be
// large enough to store the result.  If it is too small, the output is
// truncated.
// borrowed code
// http://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
// modified fromoriginal code
size_t trimwhitespace(char *out, size_t len, const char *str)
{
	
	if(len == 0)
		return 0;
	
	const char *end;
	size_t out_size;
	
	// Trim leading space
	while(isspace(*str)) str++;
	
	if(*str == 0)  // All spaces?
	{
		*out = 0;
		return 1;
	}
	
	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace(*end)) end--;
	end++;
	
	// Set output size to minimum of trimmed string length and buffer size minus 1
	out_size = (end - str) < len-1 ? (end - str) : len-1;
	
	// Copy trimmed string and add null terminator
	memcpy(out, str, out_size);
	out[out_size] = 0;
	
	return out_size;
}
//////////////////////////////////////////

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
	while(*rnum_str){									// check each digit see if valid roman numeral
		rslt_ptr = strchr(rdigits, toupper(*rnum_str));		// check current character against reference list
		if(rslt_ptr == NULL)							// if character is not roman numeral (in ref list)
			break;										// then exit out and report non valid value
		rnum_str++;										// check next digit;
	}	//while
														// if we did not make it to end of string
	if(*rnum_str)										// then there was a non-roman numeral characters
		return RNUM_ERR_INPUT_NON_NUMERAL;				// invalid value
	return RNUM_ERR_NONE;
} // end of rnum_check

/*******************************************************
 * rnum_check check digits to ensure they are only roman
 * numerals.
 * input:
 *	     rnum_str  NULL terminated string
 * returns:
 *      0 input string rnum_str has only roman numerals
 *     -1 either too long or no value or NULL input
 *******************************************************/
int   rnum_numeral_len_check(char *rnum_str){
	int  rslt_tst;											// result of test
	rslt_tst = RNUM_ERR_INPUT_NULL;							// check null input first
	if(rnum_str != NULL){									// see if given a string at all
		rslt_tst = RNUM_ERR_INPUT_LEN_ZERO;					// check if any input
		if(*rnum_str != 0){									// make sure at least 1 char in input
			rslt_tst = RNUM_ERR_INPUT_LEN_EXCEED;			// check if string too long
			if(strlen(rnum_str) <= MAX_STR_LEN_ROMAN_NUM){	// make sure string does not exceed input length
				rslt_tst = RNUM_ERR_NONE;					// no problems with length
			}
		}
	}
	
	rn_err = rslt_tst;										// store any error that may have occurred
	return rslt_tst;										// report error
}

/*******************************************************
 * rnum_numeral_validity_check 
 * check fully that a value input into the routines is
 * a valid roman numeral
 *
 * input:
 *	     rnum_str  NULL terminated string
 * returns:
 *      0 input string rnum_str has only roman numerals
 *     -1 invalid character (non-roman numerals) found
 *        within the string
 *     -2 string too long, software criteria max
 *        value input is MMMDCCCLXXXVIII
 *******************************************************/
int   rnum_numeral_validity_check(char *rnum_str){
	char str_in_tmp[TSTR_LEN];								// temp store input value for re-running loop
	char *psrc;												// pointer
	char *ptr_mid_out_str_1;								// mid-stage output string
	char *ptr_mid_out_str_2;								// mid-stage output string
	int  rslt_tst;											// result of test
	
	rslt_tst = RNUM_ERR_NONE;								// assume good input
	memset(str_in_tmp,  0, TSTR_LEN);						// init tstr null

	rslt_tst = rnum_numeral_len_check(rnum_str);			// first check length
	
	if( rslt_tst == RNUM_ERR_NONE){							// if valid length
		strcpy(str_in_tmp, rnum_str);						// make working copy
		rslt_tst = rnum_check(str_in_tmp);					// ensure only valid roman numerals are present
	
		if(rslt_tst == RNUM_ERR_NONE){						// no error then next validity check
			for(psrc = str_in_tmp; *psrc; psrc++)			//  process roman numerals as caps
				*psrc = toupper(*psrc);						// capitalize it for processing
			// check roman numeral for valid format
			// the output of this step should match the input
			// 1) remove roman numeral subtraction
			ptr_mid_out_str_1 = rnum_subt_removal(str_in_tmp);
			// 2) re-reduce the roman numerals back to proper numeral
			ptr_mid_out_str_2 = rnum_reduce_fully(ptr_mid_out_str_1);
			// 3) output had better match input or it was not a good number
			if(strcmp(str_in_tmp, ptr_mid_out_str_2))		// if in and out not equal
				rslt_tst = RNUM_ERR_INVALID_NUMERAL_FORMAT;	// then bad format, improper sequence
															// within roman numeral string
		}
	}

	rn_err = rslt_tst;										// store any error that may have occurred
	return rslt_tst;
}

/*******************************************************
 * rnum_input_split
 *  splits math equation into 2 roman numerals with error
 *  error if necessary
 * input:
 *	     rn_exp_str  NULL terminated string containg
 *                 roman numeral
 * returns:
 *       rn_pair_strct_type
 *
 * typedef struct {
 *   char *num_str_1;
 *   char *num_str_2;
 *   int err;
 *  } rn_pair_strct_type;
 * input examples
 * Input      num_str_1   num_str_2    err
 *  V+V          V          V        RNUM_ERR_NONE
 *  V+           V          V        RNUM_ERR_NONE
 *  +V           V         NULL      RNUM_ERR_NONE
 *   V           V         NULL      RNUM_ERR_NONE
 *  ""          NULL       NULL      RNUM_ERR_INPUT_LEN_ZERO
 * NULL         NULL       NULL      RNUM_ERR_INPUT_NULL
 * (string      NULL       NULL      RNUM_ERR_INPUT_LEN_EXCEED
 * too long)
 * (badly       NULL       NULL      RNUM_ERR_INVALID_NUMERAL_FORMAT
 * formatted number)
 * (bad chars   NULL       NULL      RNUM_ERR_INPUT_NON_NUMERAL
 * in number)

 *******************************************************/
rn_pair_strct_type * rnum_input_split(char *rn_exp_str){
	char str_in_tmp[TSTR_LEN];								// temp store input value for re-running loop
	int  rslt_tst;											// result of test
	char *ptr_str_1;										//
	char *ptr_str_2;										//

	rslt_tst = RNUM_ERR_NONE;								// assume good input
	memset(str_in_tmp,  0, TSTR_LEN);						// init tstr null
	rn_pair_strct_type *rn_pair = rnum_pair_create();

	strcpy(str_in_tmp, rn_exp_str);							// make working copy
	
	ptr_str_1 = strtok(str_in_tmp, ADD_DELIMETER);			// split the string
	ptr_str_2 = strtok(NULL, ADD_DELIMETER);				// split the string

	if((ptr_str_1 != NULL) && (*ptr_str_1 != 0)){
		(*rn_pair).num_str_1 = strdup(ptr_str_1);			// make copy of string
	} else {
		ptr_str_1 = NULL;
	}
	
	if((ptr_str_2 != NULL) && (*ptr_str_2 != 0)){
		if((ptr_str_1 == NULL) || (*ptr_str_1 == 0)){
			(*rn_pair).num_str_1 = strdup(ptr_str_2);		// make copy of string
			(*rn_pair).num_str_2 = NULL;					// make copy of string
		} else {
			(*rn_pair).num_str_2 = strdup(ptr_str_2);		// make copy of string
		}
	} else {
		ptr_str_2 = NULL;
	}

	return rn_pair;						// return value
}

/*******************************************************
 * rnum_subt_removal
 * removes subtractions from within roman numerals
 * it is easier to do roman math all 
 * in addition so we remove subtractions
 * input:
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
				if(strncmp(rnum_str, RN_4, strlen(RN_4)) == 0){		// 4
					strcpy(cptr_dest, FOUR_1s);				// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str += strlen(RN_4);				// move source pointer past unsubtracted pair
				} else if(strncmp(rnum_str, RN_9, strlen(RN_9)) == 0){	// 9
					strcpy(cptr_dest, RN_5 FOUR_1s);		// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str += strlen(RN_9);				// move source pointer past unsubtracted pair
				} else if(strncmp(rnum_str, RN_40, strlen(RN_40)) == 0){ // 40
					strcpy(cptr_dest, FOUR_10s);			// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str += strlen(RN_40);				// move source pointer past unsubtracted pair
				} else if(strncmp(rnum_str, RN_90, strlen(RN_90)) == 0){ // 90
					strcpy(cptr_dest, RN_50 FOUR_10s);		// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str += strlen(RN_90);				// move source pointer past unsubtracted pair
				} else if(strncmp(rnum_str, RN_400, strlen(RN_400)) == 0){ // 400
					strcpy(cptr_dest, FOUR_100s);			// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str += strlen(RN_400);				// move source pointer past unsubtracted pair
				} else if(strncmp(rnum_str, RN_900, strlen(RN_900)) == 0){ // 900
					strcpy(cptr_dest, RN_500 FOUR_100s);	// add in unsubtracted value
					cptr_dest = strchr(cptr_dest,0);		// point to new end of string
					rnum_str += strlen(RN_900);				// move source pointer past unsubtracted pair
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
 * rnum_reduce_multi_to_higher_digits reduce multiple roman numeral digits to
 * next higher value when necessary
 * input:
 *	     rnum_str  NULL terminated string
 * returns:
 *       null terminated string properly order by value
 *       if a value is reduced that may need to be
 *       reduced again, then we may ned to reduce again
 *       so we are not done and loop agian
 *******************************************************/
char *rnum_reduce_multi_to_higher_digits(char *rnum_str){
	char str_in_tmp[TSTR_LEN];								// temp store input value for re-running loop
	char str_out_tmp[TSTR_LEN];								// temp storage while grouping/sorting digits
	
	char *psrc;												// input ptr
	bool done;												// exit when done
	
	memset(str_in_tmp,  0, TSTR_LEN);						// init tstr null
	memset(str_out_tmp, 0, TSTR_LEN);						// init tstr null
	strncpy(str_in_tmp, rnum_str, TSTR_LEN);				// copy into working storage
	done = false;											// init
	
	while(! done){
		done = true;										// assume done, and clear if further
															// reduction may need to occurr
		
		psrc  = str_in_tmp;									// start at beginning of working input string
		
		//"MDCLXVI";
		while(*psrc){										// until end of string
			if(strncmp(TWO_500s, psrc, strlen(TWO_500s)) == 0){ // if 500*2
				psrc += strlen(TWO_500s);					// push past the reduced digits
				(void)strcat(str_out_tmp, RN_1000);			// then insert 1000
			} else if(strncmp(FIVE_100s, psrc, strlen(FIVE_100s)) == 0){ // if 100*5
				psrc += strlen(FIVE_100s);					// push past the reduced digits
				(void)strcat(str_out_tmp, RN_500);			// then insert 500
				done = false;								// reduced value, may need to reduce again
			} else if(strncmp(TWO_50s, psrc, strlen(TWO_50s)) == 0){	// if 50*2
				psrc += strlen(TWO_50s);					// push past the reduced digits
				(void)strcat(str_out_tmp, RN_100);			// then insert 100
				done = false;								// reduced value, may need to reduce again
			} else if(strncmp(FIVE_10s, psrc, strlen(FIVE_10s)) == 0){		// if 10*5
				psrc += strlen(FIVE_10s);					// push past the reduced digits
				(void)strcat(str_out_tmp, RN_50);			// then insert 50
				done = false;								// reduced value, may need to reduce again
			} else if(strncmp(TWO_5s,psrc,strlen(TWO_5s)) == 0){			// if 5*2
				psrc += strlen(TWO_5s);						// push past the reduced digits
				(void)strcat(str_out_tmp, RN_10);			// then insert 10
				done = false;								// reduced value, may need to reduce again
			} else if(strncmp(FIVE_1s, psrc, strlen(FIVE_1s)) == 0){		// if 1*5
				psrc += strlen(FIVE_1s);					// push past the reduced digits
				(void)strcat(str_out_tmp, RN_5);			// then insert 5
				done = false;								// reduced value, may need to reduce again
			} else {										// non-reduced digit
				(void)strncat(str_out_tmp, psrc, 1);		// store and bump forward
				psrc++;
			}
		}
		if(!done){
			memset(str_in_tmp, 0, TSTR_LEN);				// init tstr null
			strncpy(str_in_tmp, str_out_tmp, TSTR_LEN);		// store in temp storage
			memset(str_out_tmp, 0, TSTR_LEN);				// init tstr null
		}
	}
	return strdup(str_out_tmp);								// return result
}

/*******************************************************
 * rnum_reduce_improper_to_proper_digits
 * reduce improper digits to proper
 * i.e. IIII to IV, VIIII to IX, XXXX to XL, LXXXX to XC etc
 * input:
 *	     rnum_str  NULL terminated string
 * returns:
 *       null terminated string properly order by value
 *******************************************************/

char *rnum_reduce_improper_to_proper_digits(char *rnum_str){
	char str_out_tmp[TSTR_LEN];								// temp storage while grouping/sorting digits
	char *psrc;												// input ptr
	
	memset(str_out_tmp, 0, TSTR_LEN);						// init tstr null
	
	psrc  = rnum_str;										// start at beginning of working input string
	
	while(*psrc){										// until end of string
		if(strncmp(IMP_900, psrc, strlen(IMP_900)) == 0){ // if improper DCCCC
			psrc += strlen(IMP_900);					// push past the reduced digits
			(void)strcat(str_out_tmp, RN_900);			// then insert proper CM
		} else if(strncmp(IMP_400, psrc, strlen(IMP_400)) == 0){ // if CCCC
			psrc += strlen(IMP_400);					// push past the reduced digits
			(void)strcat(str_out_tmp, RN_400);			// then insert CD
		} else if(strncmp(IMP_90, psrc, strlen(IMP_90)) == 0){	// if LXXXX
			psrc += strlen(IMP_90);						// push past the reduced digits
			(void)strcat(str_out_tmp, RN_90);			// then insert XC
		} else if(strncmp(IMP_40, psrc, strlen(IMP_40)) == 0){		// if XXXX
			psrc += strlen(IMP_40);						// push past the reduced digits
			(void)strcat(str_out_tmp, RN_40);			// then insert XL
		} else if(strncmp(IMP_9,psrc,strlen(IMP_9)) == 0){		// if VIIII
			psrc += strlen(IMP_9);						// push past the reduced digits
			(void)strcat(str_out_tmp, RN_9);			// then insert IX
		} else if(strncmp(IMP_4, psrc, strlen(IMP_4)) == 0){		// if IIII
			psrc += strlen(IMP_4);						// push past the reduced digits
			(void)strcat(str_out_tmp, RN_4);			// then insert IV
		} else {										// non-reduced digit
			(void)strncat(str_out_tmp, psrc, 1);		// store and bump forward
			psrc++;
		}
	}
	
	return strdup(str_out_tmp);								// return result
}

/*******************************************************
 * rnum_reduce_fully
 * reduce fully the post-add answer into a properly
 * formatted roman numeral readable answer
 * input:
 *	     rnum_str  NULL terminated string
 * returns:
 *       null terminated string properly order by value
 *******************************************************/

char *rnum_reduce_fully(char *rnum_str){
	char str_in_tmp[TSTR_LEN];								// temp store input value for re-running loop
	char *ptr_mid_out_str_1;								// mid-stage output string
	char *ptr_mid_out_str_2;								// mid-stage output string
	char *ptr_mid_out_str_3;								// mid-stage output string
	
	memset(str_in_tmp,  0, TSTR_LEN);						// init tstr null
	strncpy(str_in_tmp, rnum_str, TSTR_LEN);				// copy into working storage
	ptr_mid_out_str_1 = NULL;								// init ptrs
	ptr_mid_out_str_2 = NULL;								// init ptrs
	ptr_mid_out_str_3 = NULL;								// init ptrs
	
	
	ptr_mid_out_str_1 = rnum_digit_group(str_in_tmp);		// make sure digits
	
															// Multi-ddigit reduction of
	ptr_mid_out_str_2 = rnum_reduce_multi_to_higher_digits(ptr_mid_out_str_1);
	
															// improper to proper test running first
	ptr_mid_out_str_3 = rnum_reduce_improper_to_proper_digits(ptr_mid_out_str_2);
	
	free(ptr_mid_out_str_1);								// avoid memory leaks of left over memory
	free(ptr_mid_out_str_2);								// avoid memory leaks of left over memory
	return ptr_mid_out_str_3;								// return output
}


/*******************************************************
 * rnum_full_add
 *   full expression add
 * input:
 *	     rn_exp_str  NULL terminated string containg
 *                 roman numeral
 * returns:
 *       rn_pair_strct_type
 *
 * typedef struct {
 *   char *num_str_1;
 *   char *num_str_2;
 *   char *result_str;
 *   int err;
 *  } rn_pair_strct_type;
 * input examples
 * Input      num_str_1 num_str_2 result_str   err
 *  V+V          V        V          X     RNUM_ERR_NONE
 *  V+           V        V          X     RNUM_ERR_NONE
 *  +V           V       NULL        V     RNUM_ERR_NONE
 *   V           V       NULL        V     RNUM_ERR_NONE
 *  ""          NULL     NULL       NULL   RNUM_ERR_INPUT_LEN_ZERO
 * NULL         NULL     NULL       NULL   RNUM_ERR_INPUT_NULL
 * (string      NULL     NULL       NULL   RNUM_ERR_INPUT_LEN_EXCEED
 * too long)
 * (badly       NULL     NULL       NULL   RNUM_ERR_INVALID_NUMERAL_FORMAT
 * formatted number)
 * (bad chars   NULL     NULL       NULL   RNUM_ERR_INPUT_NON_NUMERAL
 * in number)
 
 *******************************************************/
rn_pair_strct_type* rnum_full_add(char *rn_exp_str){
	rn_pair_strct_type *rn_rslt;							// result storage
	
	rn_rslt = rnum_input_split(rn_exp_str);					// split the input
	
	
	return rn_rslt;
}


/* end of romancalc.c */
