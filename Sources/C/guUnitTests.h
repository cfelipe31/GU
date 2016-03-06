
#include  <stdio.h>
#include "guErrors.h"

#define KNRM 	"\x1B[0m"
#define KRED 	"\x1B[31m"
#define KGRN 	"\x1B[32m"
#define KYLW 	"\x1B[33m"
#define KCYN 	"\x1B[36m"


int tests_run = 0;
int functions_run =0;
int tests_failed =0;
int tests_passed =0;

#define _test_start(functionName) do { printf("\n" KYLW "----Testing Function: %s ----" KNRM "\n", functionName); functions_run++;} while (0)

#define _it_should(message, test) do { if (!(test))  { printf(KRED "**FAIL**: %s" KNRM "\n", message); tests_failed++; } else { printf(KGRN "**PASS**: %s" KNRM "\n", message); tests_passed++; }} while (0)

#define _run_test(test) do { test(); tests_run++; } while (0)

#define _test_result() do { printf("\n" KYLW "----Test Result: %d tests executed in %d functions,"KGRN" %d passed "KYLW","KRED" %d failed"KYLW" ----" KNRM "\n", tests_run, functions_run, tests_passed, tests_failed); } while (0)



