#include <stdio.h>
#include "quotelist.h"
#include "test.h"
#include "stats.h"
#include <string.h>
#include <limits.h>
#include <stdlib.h>

void invalid_switch(char *swtch) {
  printf("Invalid switch: ");
  puts(swtch);
  exit(1);
}

void invalid_arg(char *swtch, char *arg) {
  printf("Invalid argument for switch ");
  fputs(swtch, stdout);
  printf(": ");
  puts(arg);
  exit(1);
}

int main(int argc, char **argv) {
  quotelist *qt = NULL;
  test *t = NULL;
  int test_words = 10;
  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      char *first = strtok(argv[i], "=");
      char *second = strtok(NULL, "=");
      if (first == NULL) {
        invalid_switch(argv[i]);
        continue;
      } else if (!strcmp(first, "-t")) {
        if (second == NULL) {
          invalid_arg(first, argv[i]);
        } else {
          long in = strtol(second, NULL, 10);
          if (in <= 0 || in >= INT_MAX) {
            invalid_arg(first, second);
          } else {
            test_words = in;
          }
        }
      } else if (!strcmp(first, "-w")) {
        if (second == NULL) {
          invalid_arg(first, argv[i]);
        } else {
          qt = quotelist_from_file(second);
        }
      } else {
        invalid_switch(argv[i]);
        return 0;
      }
    }
  }
  if (qt == NULL) {
    qt = quotelist_from_file("1000_most_common_words.txt");
  }
  t = make_test(qt, test_words);
  stats *s = do_test(t);
  print_stats(s);

  quotelist_destroy(qt);
  test_destroy(t);
  stats_destroy(s);
  return 0;
}
