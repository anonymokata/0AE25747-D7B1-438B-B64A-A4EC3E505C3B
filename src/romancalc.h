#ifndef __ROMANCALC_H__
#define __ROMANCALC_H__
//*******************************************/
//*  Roman calculator                       *
//*  20160730   July-30-2016 created        *
//*  Micah Wilson							*
//* Rules for inputs
//* Digit	Value	MaxDigit
//*	I		   1		3
//*	V		   5		1
//*	X		  10		3
//*	L		  50		1
//*	C		 100		3
//*	D		 500		1
//*	M		1000		3					*
//*											*
//* Max Digit Inputs MMMDCCCLXXXVIII		3888	*
//* Max Digit Output MMMMMMMDCCLXXVI		7776
//* (Using defined roman numerals)
//* Max Output string width 15+1 (null terminated)
//* Max Input  string width 15+1 (null terminated)
//********************************************/


#define MAX_STR_LEN_ROMAN_NUM (75 + 1)
void roman_numeral_str_clear(char* roman_numeral_str);
char *rnum_str_create(void);
void  rnum_str_clear(char* roman_numeral_str);
void  rnum_str_free(char* roman_numeral_str);
int   rnum_check(char *rnum_str);						// check roman number string for valid digits
char *rnum_subt_removal(char *rnum_str);
char *rnum_digit_group(char *rnum_str);
#endif

