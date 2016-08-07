#include "romancalc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


/* only main should be in this file, to make all other functions in
   the prograble testable by Check.  in order to test main(), use a
   whole program testing framework like Autotest.
*/


void printhelp(void){
	printf("\n************* REALLY BASIC HELP *************\n");
	printf(" USAGE:  <progname> romannumeral1 + romannumeral2\n");
}

int main (int argc, char *argv[])
{
	rn_pair_strct_type* lcl_rslt = NULL;
	char str_exp_temp[MAX_STR_LEN_ROMAN_NUM];					// buffer to pass expression into calculator
	bool help = false;							// checking for help
	int arg_idx;										// argument iterator
	
	
	(void)memset((void*)str_exp_temp,0,MAX_STR_LEN_ROMAN_NUM);
	
	
	// check to see if needing help,
	help = (argc == 1);
	for(arg_idx = 1; (!help && (arg_idx < arg_idx)); arg_idx++){
		help |= (strcmp(argv[arg_idx], "--help") == 0);
		help |= (strcmp(argv[arg_idx], "--HELP") == 0);
		help |= (strcmp(argv[arg_idx], "-H") == 0);
		help |= (strcmp(argv[arg_idx], "-?") == 0);
		help |= (strcmp(argv[arg_idx], "--help") == 0);
	}
	
	if(help){
		printhelp();
		exit -1;
	} else {
		for(arg_idx = 1; arg_idx < argc; arg_idx++){
			strcat(str_exp_temp, argv[arg_idx]);			// tack in each argument of the expression
			strcat(str_exp_temp, " ");						// pad it with space to catch bad typing
															// of input values i.e. "X+ X I"
															// rather than "X+ XI"
		}

		lcl_rslt = rnum_full_add(str_exp_temp);
		switch(lcl_rslt->err){
			case RNUM_ERR_NONE:
				printf("%s\n", lcl_rslt->result_str);		// print result
				break;
			case RNUM_ERR_GENERAL:
				printf("RNUM_ERR_GENERAL             = -1,        // temp lump in while developing,\n");
				break;
			case RNUM_ERR_INPUT_NULL:
				printf("RNUM_ERR_INPUT_NULL          = -2,        // was given null rather than valid string\n");
				break;
			case RNUM_ERR_INPUT_LEN_ZERO:
				printf("RNUM_ERR_INPUT_LEN_ZERO      = -3,        // was give no content string\n");
				break;
			case RNUM_ERR_INPUT_LEN_EXCEED:
				printf("RNUM_ERR_INPUT_LEN_EXCEED    = -4,        // numeral was too long to process\n");
				break;
			case RNUM_ERR_INPUT_NON_NUMERAL:
				printf("RNUM_ERR_INPUT_NON_NUMERAL   = -5,        // invalid character withing numeral string\n");
				break;
			case RNUM_ERR_INVALID_NUMERAL_FORMAT:
				printf("RNUM_ERR_INVALID_NUMERAL_FORMAT = -6,     // good numerals, bad order for proper roman numeral\n");
				break;
			case RNUM_ERR_EMPTY_INPUT:
				printf("RNUM_ERR_EMPTY_INPUT         = -7,        // bad numerals on both sides of delimeter\n");
				break;
			case RNUM_ERR_MULTIPLE_DELIMETER:
				printf("RNUM_ERR_MULTIPLE_DELIMETER  = -8,        // more than 1 "+" sign\n");
				break;
			default:
				printf("error # %i\n",lcl_rslt->err);
				break;
		}
		return lcl_rslt->err;
	}
  return 0;
}


