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
//* Large Test Inputs MMMDCCCLXXXVIII		3888	*
//* Large Test Inputs MMMMMMMDCCLXXVI		7776
//* (Using defined roman numerals)
//* Max Output string width 15+1 (null terminated)
//* Max Input  string width 15+1 (null terminated)
//********************************************/

// maximum input length 1024 roman numeral digits
// allows the the user to be
#define MAX_STR_LEN_ROMAN_NUM (1024)
typedef enum {
	RNUM_ERR_NONE				= 0,
	RNUM_ERR_GENERAL			= -1,		// temp lump in while developing,
	RNUM_ERR_INPUT_NULL			= -2,		// was given null rather than valid string
	RNUM_ERR_INPUT_LEN_ZERO		= -3,		// was give no content string
	RNUM_ERR_INPUT_LEN_EXCEED	= -4,		// numeral was too long to process
	RNUM_ERR_INPUT_NON_NUMERAL	= -5,		// invalid character withing numeral string
	RNUM_ERR_INVALID_NUMERAL_FORMAT = -6,	// good numerals, bad order for proper roman numeral
	RNUM_ERR_ = -999
} rnum_err_enum ;
void rnum_error_clear(void);
int  rnum_error_get_last(void);

/******************************************************
 * rn_pair_strct_type
 * Roman Numeral input pair for addition
 *
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
 ******************************************************/
typedef struct {
	char *num_str_1;
	char *num_str_2;
	char *result_str;
	int err;
} rn_pair_strct_type;

void roman_numeral_str_clear(char* roman_numeral_str);
rn_pair_strct_type * rnum_pair_create(void);
void  rnum_str_clear(char* roman_numeral_str);
void  rnum_str_free(rn_pair_strct_type * rnum_pair);
int   rnum_check(char *rnum_str);						// check roman number string for valid digits
int   rnum_numeral_len_check(char *rnum_str);
int   rnum_numeral_validity_check(char *rnum_str);
rn_pair_strct_type* rnum_input_split(char *rn_exp_str);
char *rnum_subt_removal(char *rnum_str);
char *rnum_digit_group(char *rnum_str);
char *rnum_reduce_multi_to_higher_digits(char *rnum_str);
char *rnum_reduce_improper_to_proper_digits(char *rnum_str);
char *rnum_reduce_fully(char *rnum_str);

#endif

