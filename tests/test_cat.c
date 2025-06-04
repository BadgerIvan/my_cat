#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void compare_cat_output(const char *filename, const char *flags) {
  char my_cat[256];
  char real_cat[256];

  snprintf(my_cat, sizeof(my_cat), "./my_cat %s %s", flags, filename);
  snprintf(real_cat, sizeof(real_cat), "cat %s %s", flags, filename);

  FILE *your_output = popen(my_cat, "r");
  FILE *real_output = popen(real_cat, "r");

  char my_line[1024], real_line[1024];
  while (fgets(my_line, sizeof(my_line), your_output) &&
         fgets(real_line, sizeof(real_line), real_output)) {
    ck_assert_str_eq(my_line, real_line);
  }

  pclose(your_output);
  pclose(real_output);
}

// simple tests
START_TEST(test_one_file) {
  compare_cat_output("../tests/test_cases/test1", "");
}
END_TEST

START_TEST(test_two_files) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2", "");
}
END_TEST

START_TEST(test_three_files) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2 "
      "../tests/test_cases/test3",
      "");
}
END_TEST

// flag b and number-nonblank tests
START_TEST(test_one_file_flag_b) {
  compare_cat_output("../tests/test_cases/test1", "-b");
}
END_TEST

START_TEST(test_two_files_flag_b) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2",
      "--number-nonblank");
}
END_TEST

START_TEST(test_three_files_flag_b) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2 "
      "../tests/test_cases/test3",
      "-b --number-nonblank");
}
END_TEST

// flag e tests
START_TEST(test_one_file_flag_e) {
  compare_cat_output("../tests/test_cases/test1", "-e");
}
END_TEST

START_TEST(test_two_files_flag_e) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2",
      "-e");
}
END_TEST

START_TEST(test_three_files_flag_e) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2 "
      "../tests/test_cases/test3",
      "-e");
}
END_TEST

// flag E tests
START_TEST(test_one_file_flag_E) {
  compare_cat_output("../tests/test_cases/test1", "-E");
}
END_TEST

START_TEST(test_two_files_flag_E) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2",
      "-E");
}
END_TEST

START_TEST(test_three_files_flag_E) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2 "
      "../tests/test_cases/test3",
      "-E");
}
END_TEST

// flag n and number tests
START_TEST(test_one_file_flag_n) {
  compare_cat_output("../tests/test_cases/test1", "-n");
}
END_TEST

START_TEST(test_two_files_flag_n) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2",
      "--number");
}
END_TEST

START_TEST(test_three_files_flag_n) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2 "
      "../tests/test_cases/test3",
      "-n --number");
}
END_TEST

// flag s and squeeze-blank tests
START_TEST(test_one_file_flag_s) {
  compare_cat_output("../tests/test_cases/test1", "-s");
}
END_TEST

START_TEST(test_two_files_flag_s) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2",
      "--squeeze-blank");
}
END_TEST

START_TEST(test_three_files_flag_s) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2 "
      "../tests/test_cases/test3",
      "-s --squeeze-blank");
}
END_TEST

// flag t tests
START_TEST(test_one_file_flag_t) {
  compare_cat_output("../tests/test_cases/test1", "-t");
}
END_TEST

START_TEST(test_two_files_flag_t) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2",
      "-t");
}
END_TEST

START_TEST(test_three_files_flag_t) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2 "
      "../tests/test_cases/test3",
      "-t");
}
END_TEST

// flag T tests
START_TEST(test_one_file_flag_T) {
  compare_cat_output("../tests/test_cases/test1", "-T");
}
END_TEST

START_TEST(test_two_files_flag_T) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2",
      "-T");
}
END_TEST

START_TEST(test_three_files_flag_T) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2 "
      "../tests/test_cases/test3",
      "-T");
}
END_TEST

// flag v tests
START_TEST(test_one_file_flag_v) {
  compare_cat_output("../tests/test_cases/test1", "-v");
}
END_TEST

START_TEST(test_two_files_flag_v) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2",
      "-v");
}
END_TEST

START_TEST(test_three_files_flag_v) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2 "
      "../tests/test_cases/test3",
      "-v");
}
END_TEST

// flags shake tests
START_TEST(test_one_file_flags_shake) {
  compare_cat_output("../tests/test_cases/test1", "-b -E -s -T");
}
END_TEST

START_TEST(test_two_files_flags_shake) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2",
      "-b -n -e -s");
}
END_TEST

START_TEST(test_three_files_flags_shake) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2 "
      "../tests/test_cases/test3",
      "-n -v -t");
}
END_TEST

// all flags tests
START_TEST(test_one_file_all_flags) {
  compare_cat_output("../tests/test_cases/test1",
                     "-b -E -e -n --number -s --squeeze-blank -T -t -v");
}
END_TEST

START_TEST(test_two_files_all_flags) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2",
      "-b -E -e -n --number -s --squeeze-blank -T -t -v");
}
END_TEST

START_TEST(test_three_files_all_flags) {
  compare_cat_output(
      "../tests/test_cases/test1 ../tests/test_cases/test2 "
      "../tests/test_cases/test3",
      "-b -E -e -n --number -s --squeeze-blank -T -t -v");
}
END_TEST

// hard tests
START_TEST(test_one_empty_file) {
  compare_cat_output("../tests/test_cases/test4",
                     "-b -E -e -n --number -s --squeeze-blank -T -t -v");
}
END_TEST

START_TEST(test_two_empty_files) {
  compare_cat_output(
      "../tests/test_cases/test4 ../tests/test_cases/test4",
      "-b -E -e -n --number -s --squeeze-blank -T -t -v");
}
END_TEST

START_TEST(test_three_empty_files) {
  compare_cat_output(
      "../tests/test_cases/test4 ../tests/test_cases/test4 "
      "../tests/test_cases/test4",
      "-b -E -e -n --number -s --squeeze-blank -T -t -v");
}
END_TEST

START_TEST(test_one_bin_file) {
  compare_cat_output("../tests/test_cases/test5", "");
}

START_TEST(test_one_bin_file_with_flags) {
  compare_cat_output("../tests/test_cases/test5",
                     "-b -E -e -n --number -s --squeeze-blank -T -t -v");
}

START_TEST(test_three_bin_files) {
  compare_cat_output(
      "../tests/test_cases/test5 ../tests/test_cases/test5 "
      "../tests/test_cases/test5",
      "");
}

START_TEST(test_three_bin_files_with_flags) {
  compare_cat_output(
      "../tests/test_cases/test5 ../tests/test_cases/test5 "
      "../tests/test_cases/test5",
      "-b -E -e -n --number -s --squeeze-blank -T -t -v");
}

Suite *suite_simple() {
  Suite *suite = suite_create("simple");
  TCase *simple = tcase_create("simple");
  tcase_add_test(simple, test_one_file);
  tcase_add_test(simple, test_two_files);
  tcase_add_test(simple, test_three_files);
  suite_add_tcase(suite, simple);
  return suite;
}

Suite *suite_flag_b() {
  Suite *suite = suite_create("flag_b");
  TCase *flag_b = tcase_create("flag_b");
  tcase_add_test(flag_b, test_one_file_flag_b);
  tcase_add_test(flag_b, test_two_files_flag_b);
  tcase_add_test(flag_b, test_three_files_flag_b);
  suite_add_tcase(suite, flag_b);
  return suite;
}

Suite *suite_flag_e() {
  Suite *suite = suite_create("flag_e");
  TCase *flag_e = tcase_create("flag_e");
  tcase_add_test(flag_e, test_one_file_flag_e);
  tcase_add_test(flag_e, test_two_files_flag_e);
  tcase_add_test(flag_e, test_three_files_flag_e);
  suite_add_tcase(suite, flag_e);
  return suite;
}

Suite *suite_flag_E() {
  Suite *suite = suite_create("flag_E");
  TCase *flag_E = tcase_create("flag_E");
  tcase_add_test(flag_E, test_one_file_flag_E);
  tcase_add_test(flag_E, test_two_files_flag_E);
  tcase_add_test(flag_E, test_three_files_flag_E);
  suite_add_tcase(suite, flag_E);
  return suite;
}

Suite *suite_flag_n() {
  Suite *suite = suite_create("flag_n");
  TCase *flag_n = tcase_create("flag_n");
  tcase_add_test(flag_n, test_one_file_flag_n);
  tcase_add_test(flag_n, test_two_files_flag_n);
  tcase_add_test(flag_n, test_three_files_flag_n);
  suite_add_tcase(suite, flag_n);
  return suite;
}

Suite *suite_flag_s() {
  Suite *suite = suite_create("flag_s");
  TCase *flag_s = tcase_create("flag_s");
  tcase_add_test(flag_s, test_one_file_flag_s);
  tcase_add_test(flag_s, test_two_files_flag_s);
  tcase_add_test(flag_s, test_three_files_flag_s);
  suite_add_tcase(suite, flag_s);
  return suite;
}

Suite *suite_flag_t() {
  Suite *suite = suite_create("flag_t");
  TCase *flag_t = tcase_create("flag_t");
  tcase_add_test(flag_t, test_one_file_flag_t);
  tcase_add_test(flag_t, test_two_files_flag_t);
  tcase_add_test(flag_t, test_three_files_flag_t);
  suite_add_tcase(suite, flag_t);
  return suite;
}

Suite *suite_flag_T() {
  Suite *suite = suite_create("flag_T");
  TCase *flag_T = tcase_create("flag_T");
  tcase_add_test(flag_T, test_one_file_flag_T);
  tcase_add_test(flag_T, test_two_files_flag_T);
  tcase_add_test(flag_T, test_three_files_flag_T);
  suite_add_tcase(suite, flag_T);
  return suite;
}

Suite *suite_flag_v() {
  Suite *suite = suite_create("flag_v");
  TCase *flag_v = tcase_create("flag_v");
  tcase_add_test(flag_v, test_one_file_flag_v);
  tcase_add_test(flag_v, test_two_files_flag_v);
  tcase_add_test(flag_v, test_three_files_flag_v);
  suite_add_tcase(suite, flag_v);
  return suite;
}

Suite *suite_flags_shake() {
  Suite *suite = suite_create("flags_shake");
  TCase *flags_shake = tcase_create("flags_shake");
  tcase_add_test(flags_shake, test_one_file_flags_shake);
  tcase_add_test(flags_shake, test_two_files_flags_shake);
  tcase_add_test(flags_shake, test_three_files_flags_shake);
  suite_add_tcase(suite, flags_shake);
  return suite;
}

Suite *suite_all_flags() {
  Suite *suite = suite_create("all_flags");
  TCase *all_flags = tcase_create("all_flags");
  tcase_add_test(all_flags, test_one_file_all_flags);
  tcase_add_test(all_flags, test_two_files_all_flags);
  tcase_add_test(all_flags, test_three_files_all_flags);
  suite_add_tcase(suite, all_flags);
  return suite;
}

Suite *suite_hard() {
  Suite *suite = suite_create("hard");
  TCase *hard = tcase_create("hard");
  tcase_add_test(hard, test_one_empty_file);
  tcase_add_test(hard, test_two_empty_files);
  tcase_add_test(hard, test_three_empty_files);
  tcase_add_test(hard, test_one_bin_file);
  tcase_add_test(hard, test_one_bin_file_with_flags);
  tcase_add_test(hard, test_three_bin_files);
  tcase_add_test(hard, test_three_bin_files_with_flags);
  suite_add_tcase(suite, hard);
  return suite;
}

int main() {
  SRunner *sr = srunner_create(NULL);
  srunner_add_suite(sr, suite_simple());
  srunner_add_suite(sr, suite_flag_b());
  srunner_add_suite(sr, suite_flag_e());
  srunner_add_suite(sr, suite_flag_E());
  srunner_add_suite(sr, suite_flag_n());
  srunner_add_suite(sr, suite_flag_s());
  srunner_add_suite(sr, suite_flag_t());
  srunner_add_suite(sr, suite_flag_T());
  srunner_add_suite(sr, suite_flag_v());
  srunner_add_suite(sr, suite_flags_shake());
  srunner_add_suite(sr, suite_all_flags());
  srunner_add_suite(sr, suite_hard());
  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}