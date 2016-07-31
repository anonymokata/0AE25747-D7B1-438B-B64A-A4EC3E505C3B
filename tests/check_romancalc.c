#include <stdlib.h>
#include <time.h>
#include <check.h>
#include "../src/romancalc.h"

//char *tst_roman_numeral_str;
char *tst_str;

void
setup (void)
{
	tst_str = roman_numeral_str_create ();
}

void
teardown (void)
{
	roman_numeral_str_free (tst_str);
}

START_TEST (test_roman_digit_check_individual)
{
	TCase *tc_digit_test = tcase_create("Digits Individual");
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
  Suite *s = suite_create ("Roman Calc Suite");

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

int
main (void)
{
  int number_failed;
  Suite *s = romancalc_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
