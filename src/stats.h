#ifndef STATS_H_
#define STATS_H_

typedef struct stats stats;

stats *stats_create(int chars, double seconds);

void print_stats(stats *s);

void stats_destroy(stats *s);

#endif
