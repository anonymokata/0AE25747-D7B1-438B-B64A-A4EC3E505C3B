#include <stdlib.h>
#include <time.h>
#include <check.h>
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
	TCase *tc_digit_test = tcase_create("Digits Individual Individual");
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
	TCase *tc_digit_test = tcase_create("Digits Individual Error");
	ck_assert_int_eq (rnum_check ("Z"), -1);
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
	TCase *tc_digit_check_str = tcase_create("Digits String");
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
	TCase *tc_digit_check_str = tcase_create("Digits String For Bad Char");
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

START_TEST (test_roman_subtraction_removal	)
{
	TCase *tc_subt_remov = tcase_create("Subtraction Removal test");
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
romancalc_suite_string (void)
{
	Suite *s = suite_create ("\nRoman Calc Suite Strings Manipulation");
	
	/* Digits test case */
	TCase *tc_string_check = tcase_create ("Test for String Errors, Bad Chars/n");
	tcase_add_test (tc_string_check, test_roman_digit_check_string);
	tcase_add_test (tc_string_check, test_roman_digit_check_string_error);
	suite_add_tcase (s, tc_string_check);
	
	/* Digits test case */
	TCase *tc_sub_removal = tcase_create ("Test Subtractionan removal/n");
	tcase_add_test (tc_sub_removal, test_roman_subtraction_removal);
	suite_add_tcase (s, tc_sub_removal);
	return s;
}

int
main (void)
{
  int number_failed;
  SRunner *sr = srunner_create (romancalc_suite ());
  srunner_add_suite(sr, romancalc_suite_string());
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
