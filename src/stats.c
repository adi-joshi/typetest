#include <stdio.h>
#include <stdlib.h>
#include "stats.h"

typedef struct stats {
  int chars;
  double seconds;
} stats;

stats *stats_create(int chars, double seconds) {
  stats *s = malloc(sizeof(stats));
  s->chars = chars;
  s->seconds = seconds;
  return s;
}

void print_stats(stats *s) {
  printf("You typed %d characters in %.2lf seconds!\n", s->chars, s->seconds);
  printf("Your WPM was: %.2lf\n", (s->chars / s->seconds) * 12);
}

void stats_destroy(stats *s) {
  free(s);
}
