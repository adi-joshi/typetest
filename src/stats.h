#ifndef STATS_H_
#define STATS_H_

#include "test.h"

typedef struct stats stats;

stats *do_test(test *t);

void print_stats(stats *s);

void stats_destroy(stats *s);

#endif
