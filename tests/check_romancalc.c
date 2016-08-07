#include <stdlib.h>
#include <time.h>
#include <check.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../src/romancalc.h"

rn_pair_strct_type * ptr_tst_pair;

void
setup (void)
{
	ptr_tst_pair = rnum_pair_create();
}

void
teardown (void)
{
	rnum_str_free (ptr_tst_pair);
}

// MARK: input length validation
START_TEST (test_validity_input_len	)
{
	char str_in_tmp[MAX_STR_LEN_ROMAN_NUM + 2];			// check length checking
	(void)memset(str_in_tmp,    0, sizeof(str_in_tmp));	/// init with null termination
	(void)memset(str_in_tmp,  'M', MAX_STR_LEN_ROMAN_NUM);	/// init with null termination
	ck_assert_int_eq (rnum_numeral_len_check (str_in_tmp), RNUM_ERR_NONE);
}
END_TEST

START_TEST (test_validity_input_len_error	)
{
	char str_in_tmp[MAX_STR_LEN_ROMAN_NUM + 2];			// check length checking
	
	ck_assert_int_eq (rnum_numeral_len_check (NULL), RNUM_ERR_INPUT_NULL); // NULL input
	ck_assert_int_eq (rnum_numeral_len_check (""), RNUM_ERR_INPUT_LEN_ZERO); // too large of input value
	
	(void)memset(str_in_tmp,  0, sizeof(str_in_tmp));	/// init with null termination
	(void)memset(str_in_tmp,  'M', sizeof(str_in_tmp)-1);	/// init with null termination
	ck_assert_int_eq (rnum_numeral_len_check (str_in_tmp), RNUM_ERR_INPUT_LEN_EXCEED); // too large of input value
}
END_TEST

Suite *
romancalc_suite_input_numerals_len_check(void)
{
	Suite *s = suite_create ("\nRoman Calc Suite Check Input Length Check");
	
	/* Digits test case */
	TCase *tc_user_input_numeral_len_check = tcase_create ("Check Lentgh\n");
	tcase_add_test (tc_user_input_numeral_len_check, test_validity_input_len);
	suite_add_tcase (s, tc_user_input_numeral_len_check);
	
	/* Digits test case */
	TCase *tc_user_input_numeral_len_check_err = tcase_create ("Check Length Error\n");
	tcase_add_test (tc_user_input_numeral_len_check_err, test_validity_input_len_error);
	suite_add_tcase (s, tc_user_input_numeral_len_check_err);
	
	return s;
}

// MARK: digit check
START_TEST (test_roman_digit_check_individual)
{
	ck_assert_int_eq (rnum_check ("i"), RNUM_ERR_NONE);	// check lower case
	ck_assert_int_eq (rnum_check ("I"), RNUM_ERR_NONE);	// check upper case
	ck_assert_int_eq (rnum_check ("v"), RNUM_ERR_NONE);	// check lower case
	ck_assert_int_eq (rnum_check ("V"), RNUM_ERR_NONE);	// check upper case
	ck_assert_int_eq (rnum_check ("x"), RNUM_ERR_NONE);	// check lower case
	ck_assert_int_eq (rnum_check ("X"), RNUM_ERR_NONE);	// check upper case
	ck_assert_int_eq (rnum_check ("l"), RNUM_ERR_NONE);	// check lower case
	ck_assert_int_eq (rnum_check ("L"), RNUM_ERR_NONE);	// check upper case
	ck_assert_int_eq (rnum_check ("c"), RNUM_ERR_NONE);	// check lower case
	ck_assert_int_eq (rnum_check ("C"), RNUM_ERR_NONE);	// check upper case
	ck_assert_int_eq (rnum_check ("d"), RNUM_ERR_NONE);	// check lower case
	ck_assert_int_eq (rnum_check ("D"), RNUM_ERR_NONE);	// check upper case
	ck_assert_int_eq (rnum_check ("m"), RNUM_ERR_NONE);	// check lower case
	ck_assert_int_eq (rnum_check ("M"), RNUM_ERR_NONE);	// check upper case
}
END_TEST

START_TEST (test_roman_digit_check_individual_error)
{
	char tst_str[2];
	char tst_ch;
	tst_str[1]=0;
	for(tst_ch = 1; tst_ch <= 'B'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), RNUM_ERR_INPUT_NON_NUMERAL);
	}
	for(tst_ch = 'E'; tst_ch <= 'H'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), RNUM_ERR_INPUT_NON_NUMERAL);
	}
	for(tst_ch = 'J'; tst_ch <= 'K'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), RNUM_ERR_INPUT_NON_NUMERAL);
	}
	for(tst_ch = 'N'; tst_ch <= 'U'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), RNUM_ERR_INPUT_NON_NUMERAL);
	}
	ck_assert_int_eq (rnum_check ("W"), RNUM_ERR_INPUT_NON_NUMERAL);
	for(tst_ch = 'Y'; tst_ch <= 'b'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), RNUM_ERR_INPUT_NON_NUMERAL);
	}
	for(tst_ch = 'e'; tst_ch <= 'h'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), RNUM_ERR_INPUT_NON_NUMERAL);
	}
	for(tst_ch = 'j'; tst_ch <= 'k'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), RNUM_ERR_INPUT_NON_NUMERAL);
	}
	for(tst_ch = 'n'; tst_ch <= 'u'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), RNUM_ERR_INPUT_NON_NUMERAL);
	}
	ck_assert_int_eq (rnum_check ("w"), RNUM_ERR_INPUT_NON_NUMERAL);
	for(tst_ch = 'y'; tst_ch <= 126; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), RNUM_ERR_INPUT_NON_NUMERAL);
	}
}
END_TEST

Suite *
romancalc_suite (void)
{
	Suite *s = suite_create ("\nRoman Calc Suite");
	
	/* Core test case */
	TCase *tc_core = tcase_create ("Core\n");
	tcase_add_checked_fixture (tc_core, setup, teardown);
	suite_add_tcase (s, tc_core);
	
	/* Digits test case */
	TCase *tc_digits = tcase_create ("Digits\n");
	tcase_add_test (tc_digits, test_roman_digit_check_individual);
	tcase_add_test (tc_digits, test_roman_digit_check_individual_error);
	suite_add_tcase (s, tc_digits);
	
	return s;
}

// MARK: digit check string
START_TEST (test_roman_digit_check_string	)
{
	ck_assert_int_eq (rnum_check ("III"),    RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_check ("IV"),     RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_check ("XXXVII"), RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_check ("LLL"), RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_check ("MDCLXVI"), RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_check ("MMMDCCCLXXXVIII"), RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_check ("MMMMMMMDCCLXXVI"), RNUM_ERR_NONE);
}
END_TEST

START_TEST (test_roman_digit_check_string_error	)
{
	ck_assert_int_eq (rnum_check ("qIII"),		RNUM_ERR_INPUT_NON_NUMERAL);		// bad char at begin
	ck_assert_int_eq (rnum_check ("IqII"),		RNUM_ERR_INPUT_NON_NUMERAL);		// bad char at mid
	ck_assert_int_eq (rnum_check ("IIIq"),		RNUM_ERR_INPUT_NON_NUMERAL);		// bad char at end
	ck_assert_int_eq (rnum_check ("IqV"),		RNUM_ERR_INPUT_NON_NUMERAL);		// bad char
	ck_assert_int_eq (rnum_check ("XXqXVII"),	RNUM_ERR_INPUT_NON_NUMERAL);		// bad char
	ck_assert_int_eq (rnum_check ("LeLL"),		RNUM_ERR_INPUT_NON_NUMERAL);		// bad char
	ck_assert_int_eq (rnum_check ("MDrCLXVI"),	RNUM_ERR_INPUT_NON_NUMERAL);		// bad char
	ck_assert_int_eq (rnum_check ("MMMDChCCLaXXXVIII"), RNUM_ERR_INPUT_NON_NUMERAL);		//bad char
	ck_assert_int_eq (rnum_check ("MMhMMsMMMxDCCLXXVI"), RNUM_ERR_INPUT_NON_NUMERAL);	// bad char
}
END_TEST

Suite *
romancalc_suite_digit_check (void)
{
	Suite *s = suite_create ("\nRoman Calc Valid Digit Check");
	
	/* Digits test case */
	TCase *tc_string_check = tcase_create ("Test for String Errors, Bad Chars\n");
	tcase_add_test (tc_string_check, test_roman_digit_check_string);
	tcase_add_test (tc_string_check, test_roman_digit_check_string_error);
	suite_add_tcase (s, tc_string_check);
	
	return s;
}

// MARK: fully validate inputs
START_TEST (test_validity_user_input_numeral	)
{
	// should pass all previous checks
	ck_assert_int_eq (rnum_numeral_validity_check ("MDCLXVI"),RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_numeral_validity_check ("IV"),     RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_numeral_validity_check ("IX"),     RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_numeral_validity_check ("XL"),     RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_numeral_validity_check ("XC"),     RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_numeral_validity_check ("CD"),     RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_numeral_validity_check ("CM"),     RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_numeral_validity_check ("XXXVII"), RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_numeral_validity_check ("L"), RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_numeral_validity_check ("MDCLXVI"), RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_numeral_validity_check ("MMMDCCCLXXXVIII"), RNUM_ERR_NONE);
	ck_assert_int_eq (rnum_numeral_validity_check ("MMMMMMMDCCLXXVI"), RNUM_ERR_NONE);
}
END_TEST

START_TEST (test_validity_user_input_length_error	)
{
	ck_assert_int_eq (rnum_numeral_validity_check (NULL),	RNUM_ERR_INPUT_NULL);
	ck_assert_int_eq (rnum_numeral_validity_check (""),		RNUM_ERR_INPUT_LEN_ZERO);
}
END_TEST

START_TEST (test_validity_user_input_numeral_error	)
{
	// should fail all previous checks
	ck_assert_int_eq (rnum_numeral_validity_check ("qIII"),		RNUM_ERR_INPUT_NON_NUMERAL);		// bad char at begin
	ck_assert_int_eq (rnum_numeral_validity_check ("IqII"),		RNUM_ERR_INPUT_NON_NUMERAL);		// bad char at mid
	ck_assert_int_eq (rnum_numeral_validity_check ("IIIq"),		RNUM_ERR_INPUT_NON_NUMERAL);		// bad char at end
	ck_assert_int_eq (rnum_numeral_validity_check ("IqV"),		RNUM_ERR_INPUT_NON_NUMERAL);		// bad char
	ck_assert_int_eq (rnum_numeral_validity_check ("XXqXVII"),	RNUM_ERR_INPUT_NON_NUMERAL);		// bad char
	ck_assert_int_eq (rnum_numeral_validity_check ("LeLL"),		RNUM_ERR_INPUT_NON_NUMERAL);		// bad char
	ck_assert_int_eq (rnum_numeral_validity_check ("MDrCLXVI"),	RNUM_ERR_INPUT_NON_NUMERAL);		// bad char
	ck_assert_int_eq (rnum_numeral_validity_check ("MMMDChCCLaXXXVIII"), RNUM_ERR_INPUT_NON_NUMERAL);		//bad char
	ck_assert_int_eq (rnum_numeral_validity_check ("MMhMMsMMMxDCCLXXVI"), RNUM_ERR_INPUT_NON_NUMERAL);	// bad char
}
END_TEST

START_TEST (test_validity_user_input_improper_error	)
{
	ck_assert_int_eq (rnum_numeral_validity_check ("DD"),		RNUM_ERR_INVALID_NUMERAL_FORMAT);
	ck_assert_int_eq (rnum_numeral_validity_check ("CCCC"),		RNUM_ERR_INVALID_NUMERAL_FORMAT);
	ck_assert_int_eq (rnum_numeral_validity_check ("CCCCCCCCCC"),RNUM_ERR_INVALID_NUMERAL_FORMAT);
	ck_assert_int_eq (rnum_numeral_validity_check ("LL"),		RNUM_ERR_INVALID_NUMERAL_FORMAT);
	ck_assert_int_eq (rnum_numeral_validity_check ("XXXX"),		RNUM_ERR_INVALID_NUMERAL_FORMAT);
	ck_assert_int_eq (rnum_numeral_validity_check ("XXXXXXXXXX"),RNUM_ERR_INVALID_NUMERAL_FORMAT);
	ck_assert_int_eq (rnum_numeral_validity_check ("VV"),		RNUM_ERR_INVALID_NUMERAL_FORMAT);
	ck_assert_int_eq (rnum_numeral_validity_check ("IIII"),		RNUM_ERR_INVALID_NUMERAL_FORMAT);
	ck_assert_int_eq (rnum_numeral_validity_check ("VIIII"),	RNUM_ERR_INVALID_NUMERAL_FORMAT);
	ck_assert_int_eq (rnum_numeral_validity_check ("IIIIIIIIII"),RNUM_ERR_INVALID_NUMERAL_FORMAT);
}
END_TEST

Suite *
romancalc_suite_input_numerals_validation(void)
{
	Suite *s = suite_create ("\nRoman Calc Suite Check Validity of User Input Roman Numeral");
	
	/* Digits test case */
	TCase *tc_user_input_numeral_validity = tcase_create ("\nCheck Validity of User Input Roman Numerals\n");
	tcase_add_test (tc_user_input_numeral_validity, test_validity_user_input_numeral);
	tcase_add_test (tc_user_input_numeral_validity, test_validity_user_input_length_error);
	tcase_add_test (tc_user_input_numeral_validity, test_validity_user_input_numeral_error);
	tcase_add_test (tc_user_input_numeral_validity, test_validity_user_input_improper_error);
	suite_add_tcase (s, tc_user_input_numeral_validity);
	
	return s;
}

// MARK: romancalc_suite_input_split_check
START_TEST (test_input_split )
{
	ptr_tst_pair = rnum_input_split ("V");			//
	ck_assert_ptr_ne( ptr_tst_pair, NULL);						// should return value
	ck_assert_int_eq( (*ptr_tst_pair).err, RNUM_ERR_NONE);		// with no errors
	ck_assert_str_eq( (*ptr_tst_pair).num_str_1, "V");			// and first number loaded
	ck_assert_ptr_eq( (*ptr_tst_pair).num_str_2, NULL);         // and no second number
	ck_assert_ptr_eq( (*ptr_tst_pair).result_str, NULL);        // no result at this test
	teardown();
	
	ptr_tst_pair = rnum_input_split ("V+V");			//
	ck_assert_ptr_ne( ptr_tst_pair, NULL);						// should return value
	ck_assert_int_eq( (*ptr_tst_pair).err, RNUM_ERR_NONE);		// with no errors
	ck_assert_str_eq( (*ptr_tst_pair).num_str_1, "V");			// and first number loaded
	ck_assert_str_eq( (*ptr_tst_pair).num_str_2, "V");          // and no second number
	ck_assert_ptr_eq( (*ptr_tst_pair).result_str, NULL);        // no result at this test
	teardown();
	
	ptr_tst_pair = rnum_input_split ("V+");			//
	ck_assert_ptr_ne( ptr_tst_pair, NULL);						// should return value
	ck_assert_int_eq( (*ptr_tst_pair).err, RNUM_ERR_NONE);		// with no errors
	ck_assert_str_eq( (*ptr_tst_pair).num_str_1, "V");			// and first number loaded
	ck_assert_ptr_eq( (*ptr_tst_pair).num_str_2, NULL);          // and no second number
	ck_assert_ptr_eq( (*ptr_tst_pair).result_str, NULL);        // no result at this test
	teardown();
	
	ptr_tst_pair = rnum_input_split ("+V");			//
	ck_assert_ptr_ne( ptr_tst_pair, NULL);						// should return value
	ck_assert_int_eq( (*ptr_tst_pair).err, RNUM_ERR_NONE);		// with no errors
	ck_assert_str_eq( (*ptr_tst_pair).num_str_1, "V");			// and first number loaded
	ck_assert_ptr_eq( (*ptr_tst_pair).num_str_2, NULL);          // and no second number
	ck_assert_ptr_eq( (*ptr_tst_pair).result_str, NULL);        // no result at this test
	teardown();
	
}
END_TEST

Suite *
romancalc_suite_input_split_check(void)
{
	Suite *s = suite_create ("\nRoman Calc Suite Input Split Check");
	
	/* Digits test case */
	TCase *tc_input_split = tcase_create ("\nCheck Input Splitroutine\n");
	tcase_add_test (tc_input_split, test_input_split);
	suite_add_tcase (s, tc_input_split);
	
	return s;
}

// MARK: romancalc_suite_subtract_simplification_check
START_TEST (test_roman_subtraction_removal	)
{
	ck_assert_str_eq (rnum_subt_removal ("IV"),		"IIII" );	// 4
	ck_assert_str_eq (rnum_subt_removal ("IX"),		"VIIII");	// 9
	ck_assert_str_eq (rnum_subt_removal ("XL"),		"XXXX" );	// 40
	ck_assert_str_eq (rnum_subt_removal ("XC"),		"LXXXX");	// 90
	ck_assert_str_eq (rnum_subt_removal ("CD"),		"CCCC" );	// 400
	ck_assert_str_eq (rnum_subt_removal ("CM"),		"DCCCC");	// 900
	ck_assert_str_eq (rnum_subt_removal ("LIV"),	"LIIII" );	// 54
	ck_assert_str_eq (rnum_subt_removal ("MXCIII"),	"MLXXXXIII");	//1093
	ck_assert_str_eq (rnum_subt_removal ("MCMXLIV"),"MDCCCCXXXXIIII");	// 1944
}
END_TEST

Suite *
romancalc_suite_subtract_simplification_check(void)
{
	Suite *s = suite_create ("\nRoman Calc Suite Subtraction Removal Simplification");
	
	/* Digits test case */
	TCase *tc_sub_removal = tcase_create ("Test Subtractionan removal\n");
	tcase_add_test (tc_sub_removal, test_roman_subtraction_removal);
	suite_add_tcase (s, tc_sub_removal);
	
	return s;
}

// MARK: digit grouping/sorting test
START_TEST (test_roman_digit_grouping	)
{
	ck_assert_str_eq (rnum_digit_group ("MDCLXVI"),"MDCLXVI");
	ck_assert_str_eq (rnum_digit_group ("IVXLCDM"),"MDCLXVI");
	ck_assert_str_eq (rnum_digit_group ("IVXLCDMIVXLCDM"),"MMDDCCLLXXVVII");
}
END_TEST

Suite *
romancalc_suite_digit_grouping_check(void)
{
	Suite *s = suite_create ("\nRoman Calc Suite Digit Grouping Checking");
	
	/* Digits test case */
	TCase *tc_digit_group = tcase_create ("Test Roman Digit Grouping\n");
	tcase_add_test (tc_digit_group, test_roman_digit_grouping);
	suite_add_tcase (s, tc_digit_group);
	
	return s;
}

// MARK: test_numeral_reduction_multi_to_higher_digits
START_TEST (test_numeral_reduction_multi_to_higher_digits	)
{
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("DD"),"M");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("CCCCC"),"D");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("CCCCCCCCCC"),"M");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("LL"),"C");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("XXXXX"),"L");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("XXXXXXXXXX"),"C");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("XXXXXXXXXXXXXXX"),"CL");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("XXXXXXXXXXXXXXXXXXXX"),"CC");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("VV"),"X");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("IIIII"),"V");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("VIIIII"),"X");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("IIIIIIIIII"),"X");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("IIIIIIIIIIIIIII"),"XV");
	ck_assert_str_eq (rnum_reduce_multi_to_higher_digits ("IIIIIIIIIIIIIIIIIIII"),"XX");
}
END_TEST

Suite *
romancalc_suite_digit_reduciton_multi_to_higher_check(void)
{
	Suite *s = suite_create ("\nRoman Calc Suite Digit group reduction");
	
	/* Digits test case */
	TCase *tc_digit_reduce_multi_to_higher_digits = tcase_create ("Test Roman Multi Digit Value to Higher Value\n");
	tcase_add_test (tc_digit_reduce_multi_to_higher_digits, test_numeral_reduction_multi_to_higher_digits);
	suite_add_tcase (s, tc_digit_reduce_multi_to_higher_digits);
	
	return s;
}

// MARK: test_numeral_reduction_improper_to_proper
START_TEST (test_numeral_reduction_improper_to_proper	)
{
	ck_assert_str_eq (rnum_reduce_improper_to_proper_digits ("IIII") ,"IV"); //   4
	ck_assert_str_eq (rnum_reduce_improper_to_proper_digits ("VIIII"),"IX"); //   9
	ck_assert_str_eq (rnum_reduce_improper_to_proper_digits ("XXXX") ,"XL"); //  40
	ck_assert_str_eq (rnum_reduce_improper_to_proper_digits ("LXXXX"),"XC"); //  90
	ck_assert_str_eq (rnum_reduce_improper_to_proper_digits ("CCCC") ,"CD"); // 400
	ck_assert_str_eq (rnum_reduce_improper_to_proper_digits ("DCCCC"),"CM"); // 900
	ck_assert_str_eq (rnum_reduce_improper_to_proper_digits ("MDCCCCLXXXXIIII"),"MCMXCIV"); // 1994
}
END_TEST

Suite *
romancalc_suite_digit_reduction_improper_to_proper_check(void)
{
	Suite *s = suite_create ("\nRoman Calc Suite Improper to Proper Digits");
	
	/* Digits test case */
	TCase *tc_digit_reduce_improper_to_proper = tcase_create ("Test Roman Improper to Proper Digits\n");
	tcase_add_test (tc_digit_reduce_improper_to_proper, test_numeral_reduction_improper_to_proper);
	suite_add_tcase (s, tc_digit_reduce_improper_to_proper);
	
	return s;
}

// MARK: test_numeral_reduction_fully
START_TEST (test_numeral_reduction_fully	)
{
	// this should pass ALL Previously defined tests
	// include tests from "romancalc_suite_digit_grouping_check"
	ck_assert_str_eq (rnum_reduce_fully ("MDCLXVI"),"MDCLXVI");
	ck_assert_str_eq (rnum_reduce_fully ("IVXLCDM"),"MDCLXVI");
	ck_assert_str_eq (rnum_reduce_fully ("IDXLCVM"),"MDCLXVI");
	ck_assert_str_eq (rnum_reduce_fully ("IVXLCDMIVXLCDM"),"MMMCCCXXXII");
	
	// this should pass ALL Previously defined tests
	// include tests from "romancalc_suite_digit_reduciton_multi_to_higher_check"
	ck_assert_str_eq (rnum_reduce_fully ("DD"),"M");
	ck_assert_str_eq (rnum_reduce_fully ("CCCCC"),"D");
	ck_assert_str_eq (rnum_reduce_fully ("CCCCCCCCCC"),"M");
	ck_assert_str_eq (rnum_reduce_fully ("LL"),"C");
	ck_assert_str_eq (rnum_reduce_fully ("XXXXX"),"L");
	ck_assert_str_eq (rnum_reduce_fully ("XXXXXXXXXX"),"C");
	ck_assert_str_eq (rnum_reduce_fully ("XXXXXXXXXXXXXXX"),"CL");
	ck_assert_str_eq (rnum_reduce_fully ("XXXXXXXXXXXXXXXXXXXX"),"CC");
	ck_assert_str_eq (rnum_reduce_fully ("VV"),"X");
	ck_assert_str_eq (rnum_reduce_fully ("IIIII"),"V");
	ck_assert_str_eq (rnum_reduce_fully ("VIIIII"),"X");
	ck_assert_str_eq (rnum_reduce_fully ("IIIIIIIIII"),"X");
	ck_assert_str_eq (rnum_reduce_fully ("IIIIIIIIIIIIIII"),"XV");
	ck_assert_str_eq (rnum_reduce_fully ("IIIIIIIIIIIIIIIIIIII"),"XX");
	
	// this should pass ALL Previously defined tests
	// include tests from "romancalc_suite_digit_reduction_improper_to_proper_check"
	ck_assert_str_eq (rnum_reduce_fully ("IIII") ,"IV"); //   4
	ck_assert_str_eq (rnum_reduce_fully ("VIIII"),"IX"); //   9
	ck_assert_str_eq (rnum_reduce_fully ("XXXX") ,"XL"); //  40
	ck_assert_str_eq (rnum_reduce_fully ("LXXXX"),"XC"); //  90
	ck_assert_str_eq (rnum_reduce_fully ("CCCC") ,"CD"); // 400
	ck_assert_str_eq (rnum_reduce_fully ("DCCCC"),"CM"); // 900
	
	// test ing new combinations
	ck_assert_str_eq (rnum_reduce_fully ("MDCCCCLXXXXIIII"),"MCMXCIV"); // 1994
	ck_assert_str_eq (rnum_reduce_fully ("MCCCCCCCCCXXXXXXXXXIIIIIIIII"),\
					  "MCMXCIX"); // 1999
	
	// test ing new combinations
	ck_assert_str_eq (rnum_reduce_fully ("VIVI"),"XII"); // 6 + 6 = 12
	ck_assert_str_eq (rnum_reduce_fully ("CCXXIICCCXXXIII"),"DLV"); // 222 + 333 = 555
}
END_TEST

Suite *
romancalc_suite_digit_reduction_full_check(void)
{
	Suite *s = suite_create ("\nRoman Calc Suite Testing Full Post-Add Reduction to Proper Roman Numeral check");
	
	/* Digits test case */
	TCase *tc_digit_reduce_fully = tcase_create ("Test Roman Post-Add Full Reduction to Proper Roman Numeral\n");
	tcase_add_test (tc_digit_reduce_fully, test_numeral_reduction_fully);
	suite_add_tcase (s, tc_digit_reduce_fully);
	
	return s;
}

// MARK: romancalc_suite_full_addition_check
START_TEST (test_full_addition	)
{
	ptr_tst_pair = rnum_full_add ("V");			//
	ck_assert_ptr_ne( ptr_tst_pair, NULL);						// should return value
	ck_assert_int_eq( (*ptr_tst_pair).err, RNUM_ERR_NONE);		// with no errors
	ck_assert_str_eq( (*ptr_tst_pair).num_str_1, "V");			// and first number loaded
	ck_assert_ptr_eq( (*ptr_tst_pair).num_str_2, NULL);         // and no second number
	ck_assert_ptr_eq( (*ptr_tst_pair).result_str, NULL);        // no result at this test
	teardown();
	
	ptr_tst_pair = rnum_full_add ("V+V");			//
	ck_assert_ptr_ne( ptr_tst_pair, NULL);						// should return value
	ck_assert_int_eq( (*ptr_tst_pair).err, RNUM_ERR_NONE);		// with no errors
	ck_assert_str_eq( (*ptr_tst_pair).num_str_1, "V");			// and first number loaded
	ck_assert_str_eq( (*ptr_tst_pair).num_str_2, "V");          // and no second number
	ck_assert_ptr_eq( (*ptr_tst_pair).result_str, NULL);        // no result at this test
	teardown();
	
	ptr_tst_pair = rnum_full_add ("V+");			//
	ck_assert_ptr_ne( ptr_tst_pair, NULL);						// should return value
	ck_assert_int_eq( (*ptr_tst_pair).err, RNUM_ERR_NONE);		// with no errors
	ck_assert_str_eq( (*ptr_tst_pair).num_str_1, "V");			// and first number loaded
	ck_assert_ptr_eq( (*ptr_tst_pair).num_str_2, NULL);          // and no second number
	ck_assert_ptr_eq( (*ptr_tst_pair).result_str, NULL);        // no result at this test
	teardown();
	
	ptr_tst_pair = rnum_full_add ("+V");			//
	ck_assert_ptr_ne( ptr_tst_pair, NULL);						// should return value
	ck_assert_int_eq( (*ptr_tst_pair).err, RNUM_ERR_NONE);		// with no errors
	ck_assert_str_eq( (*ptr_tst_pair).num_str_1, "V");			// and first number loaded
	ck_assert_ptr_eq( (*ptr_tst_pair).num_str_2, NULL);          // and no second number
	ck_assert_ptr_eq( (*ptr_tst_pair).result_str, NULL);        // no result at this test
	teardown();
}
END_TEST

Suite *
romancalc_suite_full_addition_check(void)
{
	Suite *s = suite_create ("\nRoman Calc Suite Test Full Addition check");
	
	/* Digits test case */
	TCase *tc_full_addition = tcase_create ("Test Roman Full Addition\n");
	tcase_add_test (tc_full_addition, test_full_addition);
	suite_add_tcase (s, tc_full_addition);
	
	return s;
}

// MARK: Main routine
int
main (void)
{
  int number_failed;
	
  SRunner *sr = srunner_create (romancalc_suite ());
  srunner_add_suite(sr, romancalc_suite_digit_check());
  srunner_add_suite(sr, romancalc_suite_subtract_simplification_check());
  srunner_add_suite(sr, romancalc_suite_digit_grouping_check());
  srunner_add_suite(sr, romancalc_suite_digit_reduciton_multi_to_higher_check());
  srunner_add_suite(sr, romancalc_suite_digit_reduction_improper_to_proper_check());
  srunner_add_suite(sr, romancalc_suite_digit_reduction_full_check());
  srunner_add_suite(sr, romancalc_suite_input_numerals_len_check());
  srunner_add_suite(sr, romancalc_suite_input_numerals_validation());
  srunner_add_suite(sr, romancalc_suite_input_split_check());
  srunner_add_suite(sr, romancalc_suite_full_addition_check());
  srunner_run_all (sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
