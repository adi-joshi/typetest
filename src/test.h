#ifndef TEST_H_
#define TEST_H_

#include "quotelist.h"
#include "stats.h"

// the test struct
typedef struct test {
  char *script;
  int len;
} test;

// makes a test by taking n number of quotes from qt, and returns a heap allocated pointer.
test *make_test(quotelist *qt, int n);

// starts the test and creates a stats struct that records the stats for the test
stats *do_test(test *t);

// frees a heap allocated test pointer.
void test_destroy(test *t);

#endif
