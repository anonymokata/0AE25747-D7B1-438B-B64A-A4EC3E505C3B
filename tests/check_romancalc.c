#include <stdlib.h>
#include <time.h>
#include <check.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../src/romancalc.h"

//char *tst_roman_numeral_str;
char *tst_str;

void
setup (void)
{
	tst_str = rnum_str_create ();
}

void
teardown (void)
{
	rnum_str_free (tst_str);
}

START_TEST (test_roman_digit_check_individual)
{
	ck_assert_int_eq (rnum_check ("i"), 0);	// check lower case
	ck_assert_int_eq (rnum_check ("I"), 0);	// check upper case
	ck_assert_int_eq (rnum_check ("v"), 0);	// check lower case
	ck_assert_int_eq (rnum_check ("V"), 0);	// check upper case
	ck_assert_int_eq (rnum_check ("x"), 0);	// check lower case
	ck_assert_int_eq (rnum_check ("X"), 0);	// check upper case
	ck_assert_int_eq (rnum_check ("l"), 0);	// check lower case
	ck_assert_int_eq (rnum_check ("L"), 0);	// check upper case
	ck_assert_int_eq (rnum_check ("c"), 0);	// check lower case
	ck_assert_int_eq (rnum_check ("C"), 0);	// check upper case
	ck_assert_int_eq (rnum_check ("d"), 0);	// check lower case
	ck_assert_int_eq (rnum_check ("D"), 0);	// check upper case
	ck_assert_int_eq (rnum_check ("m"), 0);	// check lower case
	ck_assert_int_eq (rnum_check ("M"), 0);	// check upper case
}
END_TEST

START_TEST (test_roman_digit_check_individual_error)
{
	char tst_str[2];
	char tst_ch;
	tst_str[1]=0;
	for(tst_ch = 1; tst_ch <= 'B'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), -1);
	}
	for(tst_ch = 'E'; tst_ch <= 'H'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), -1);
	}
	for(tst_ch = 'J'; tst_ch <= 'K'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), -1);
	}
	for(tst_ch = 'N'; tst_ch <= 'U'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), -1);
	}
	ck_assert_int_eq (rnum_check ("W"), -1);
	for(tst_ch = 'Y'; tst_ch <= 'b'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), -1);
	}
	for(tst_ch = 'e'; tst_ch <= 'h'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), -1);
	}
	for(tst_ch = 'j'; tst_ch <= 'k'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), -1);
	}
	for(tst_ch = 'n'; tst_ch <= 'u'; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), -1);
	}
	ck_assert_int_eq (rnum_check ("w"), -1);
	for(tst_ch = 'y'; tst_ch <= 126; tst_ch++){
		*tst_str = tst_ch;
		ck_assert_int_eq (rnum_check (tst_str), -1);
	}
}
END_TEST

Suite *
romancalc_suite (void)
{
	Suite *s = suite_create ("\nRoman Calc Suite");
	
	/* Core test case */
	TCase *tc_core = tcase_create ("Core/n");
	tcase_add_checked_fixture (tc_core, setup, teardown);
	suite_add_tcase (s, tc_core);
	
	/* Digits test case */
	TCase *tc_digits = tcase_create ("Digits/n");
	tcase_add_test (tc_digits, test_roman_digit_check_individual);
	tcase_add_test (tc_digits, test_roman_digit_check_individual_error);
	suite_add_tcase (s, tc_digits);
	
	return s;
}

START_TEST (test_roman_digit_check_string	)
{
	ck_assert_int_eq (rnum_check ("III"),    0);	// check lower case
	ck_assert_int_eq (rnum_check ("IV"),     0);	// check upper case
	ck_assert_int_eq (rnum_check ("XXXVII"), 0);	// check lower case
	ck_assert_int_eq (rnum_check ("LLL"), 0);	// check upper case
	ck_assert_int_eq (rnum_check ("MDCLXVI"), 0);	// check lower case
	ck_assert_int_eq (rnum_check ("MMMDCCCLXXXVIII"), 0);	// check upper case
	ck_assert_int_eq (rnum_check ("MMMMMMMDCCLXXVI"), 0);	// check lower case
}
END_TEST

START_TEST (test_roman_digit_check_string_error	)
{
	ck_assert_int_eq (rnum_check ("qIII"),		-1);		// bad char at begin
	ck_assert_int_eq (rnum_check ("IqII"),		-1);		// bad char at mid
	ck_assert_int_eq (rnum_check ("IIIq"),		-1);		// bad char at end
	ck_assert_int_eq (rnum_check ("IqV"),		-1);		// bad char
	ck_assert_int_eq (rnum_check ("XXqXVII"),	-1);		// bad char
	ck_assert_int_eq (rnum_check ("LeLL"),		-1);		// bad char
	ck_assert_int_eq (rnum_check ("MDrCLXVI"),	-1);		// bad char
	ck_assert_int_eq (rnum_check ("MMMDChCCLaXXXVIII"), -1);		//bad char
	ck_assert_int_eq (rnum_check ("MMhMMsMMMxDCCLXXVI"), -1);	// bad char
}
END_TEST

Suite *
romancalc_suite_digit_check (void)
{
	Suite *s = suite_create ("\nRoman Calc Valid Digit Check");
	
	/* Digits test case */
	TCase *tc_string_check = tcase_create ("Test for String Errors, Bad Chars/n");
	tcase_add_test (tc_string_check, test_roman_digit_check_string);
	tcase_add_test (tc_string_check, test_roman_digit_check_string_error);
	suite_add_tcase (s, tc_string_check);
	
	return s;
}

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
	TCase *tc_sub_removal = tcase_create ("Test Subtractionan removal/n");
	tcase_add_test (tc_sub_removal, test_roman_subtraction_removal);
	suite_add_tcase (s, tc_sub_removal);
	
	return s;
}

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
	TCase *tc_digit_group = tcase_create ("Test Roman Digit Grouping/n");
	tcase_add_test (tc_digit_group, test_roman_digit_grouping);
	suite_add_tcase (s, tc_digit_group);
	
	return s;
}

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
	TCase *tc_digit_reduce_multi_to_higher_digits = tcase_create ("Test Roman Multi Digit Value to Higher Value/n");
	tcase_add_test (tc_digit_reduce_multi_to_higher_digits, test_numeral_reduction_multi_to_higher_digits);
	suite_add_tcase (s, tc_digit_reduce_multi_to_higher_digits);
	
	return s;
}

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
	TCase *tc_digit_reduce_improper_to_proper = tcase_create ("Test Roman Improper to Proper Digits/n");
	tcase_add_test (tc_digit_reduce_improper_to_proper, test_numeral_reduction_improper_to_proper);
	suite_add_tcase (s, tc_digit_reduce_improper_to_proper);
	
	return s;
}


START_TEST (test_numeral_reduction_fully	)
{
	ck_assert_str_eq (rnum_reduce_fully ("IIII") ,"IV"); //   4
}
END_TEST

Suite *
romancalc_suite_digit_reduction_full_check(void)
{
	Suite *s = suite_create ("\nRoman Calc Suite Testing Full Post-Add Reduction to Proper Roman Numeral check");
	
	/* Digits test case */
	TCase *tc_digit_reduce_fully = tcase_create ("Test Roman Post-Add Full Reduction to Proper Roman Numeral/n");
	tcase_add_test (tc_digit_reduce_fully, test_numeral_reduction_fully);
	suite_add_tcase (s, tc_digit_reduce_fully);
	
	return s;
}

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
  srunner_run_all (sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
