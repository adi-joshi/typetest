#include "test.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

/*
typedef struct test {
  char *script;
  int len;
} test;
*/

// creates a test struct for a given script and length of script.
static test *test_create(char *script, int len) {
  test *t = malloc(sizeof(test));
  t->script = script;
  t->len = len;
  return t;
}


test *make_test(quotelist *qt, int n) {
  int curlen = 0;
  int maxlen = 5;
  char *script = malloc(sizeof(char) * maxlen);
  srand(time(NULL));
  for (int i = 0; i < n; i++) {
    int x = rand() % qt->len;
    char *quote = qt->quotes[x];
    int quotelen = strlen(quote);
    for (int i = 0; i < quotelen; i++) {
      script[curlen] = quote[i];
      curlen++;
      if (curlen >= maxlen - 1) {
        maxlen *= 2;
        script = realloc(script, sizeof(char) * maxlen);
      }
    }

    script[curlen] = ' ';
    curlen++;
  }

  script[curlen - 1] = '\0';
  curlen++;
  script = realloc(script, sizeof(char) * curlen);
  test *t = test_create(script, curlen);
  return t;
}

void test_destroy(test *t) {
  free(t->script);
  free(t);
}
