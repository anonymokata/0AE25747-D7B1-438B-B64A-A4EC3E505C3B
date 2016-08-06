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
//* (Using defined roman numerals)
//* Max Output string width 15+1 (null terminated)
//* Max Input  string width 15+1 (null terminated)
//********************************************/

// maximum input length 1024 roman numeral digits
// allows the the user to be
#define MAX_STR_LEN_ROMAN_NUM (1024)
typedef enum rnum_err_enum {
	RNUM_ERR_NONE				= 0,
	RNUM_ERR_GENERAL			= -1,		// temp lump in while developing,
	RNUM_ERR_INPUT_NULL			= -2,		// was given null rather than valid string
	RNUM_ERR_INPUT_LEN_ZERO		= -3,		// was give no content string
	RNUM_ERR_INPUT_LEN_EXCEED	= -4,		// numeral was too long to process
	RNUM_ERR_INPUT_NON_NUMERAL	= -5,		// invalid character withing numeral string
	RNUM_ERR_INVALID_NUMERAL_FORMAT = -6,	// good numerals, bad order for proper roman numeral
	RNUM_ERR_ = -999
};
void roman_numeral_str_clear(char* roman_numeral_str);
char *rnum_str_create(void);
void  rnum_str_clear(char* roman_numeral_str);
void  rnum_str_free(char* roman_numeral_str);
int   rnum_check(char *rnum_str);						// check roman number string for valid digits
int   rnum_numeral_len_check(char *rnum_str);
int   rnum_numeral_validity_check(char *rnum_str);
char *rnum_subt_removal(char *rnum_str);
char *rnum_digit_group(char *rnum_str);
char *rnum_reduce_multi_to_higher_digits(char *rnum_str);
char *rnum_reduce_improper_to_proper_digits(char *rnum_str);
char *rnum_reduce_fully(char *rnum_str);

#endif

