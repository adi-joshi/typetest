#include <stdio.h>
#include "quotelist.h"
#include "test.h"
#include "stats.h"

int main(int argc, char **argv) {
  quotelist *qt = quotelist_from_file("../1000_most_common_words.txt");
  test *t = make_test(qt, 10);
  stats *s = do_test(t);
  print_stats(s);

  quotelist_destroy(qt);
  test_destroy(t);
  stats_destroy(s);
  return 0;
}
