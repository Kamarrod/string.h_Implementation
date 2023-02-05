#include "alltests.h"
int main(void) {
  //setlocale(LC_ALL, "");
  setlocale(LC_ALL, "en_US.UTF-8");
  int nf;
  SRunner *sr;
  sr = srunner_create(test_sprintf_unsigned());
  srunner_add_suite(sr, test_sprintf_string());
  srunner_add_suite(sr, test_sprintf_percent());
  srunner_add_suite(sr, test_sprintf_signed_i());
  srunner_add_suite(sr, test_sprintf_signed());
  srunner_add_suite(sr, test_sprintf_c());
  srunner_add_suite(sr, test_sprintf_f());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);

  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
