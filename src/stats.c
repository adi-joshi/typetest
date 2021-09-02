#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <ctype.h>
#include "stats.h"
#include "ncurses.h"

typedef struct stats {
  int chars;
  double seconds;
} stats;

static stats *stats_create(int chars, double seconds) {
  stats *s = malloc(sizeof(stats));
  s->chars = chars;
  s->seconds = seconds;
  return s;
}

stats *do_test(test *t) {
  // setting up screen
  initscr();
  clear();
  // curs_set(0);
  start_color();
  cbreak();
  noecho();
  
  // colors for correct and wrong chars
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  printw("%s", t->script);
  move(0,0);
  refresh();

  struct timeval start, end;
  gettimeofday(&start, NULL);
  int i = 0;
  while(i < t->len - 1) {
    char c = getch();
    if (t->script[i] == c) {
      // if correct, then print char with green color.
      attroff(COLOR_PAIR(2));
      attron(COLOR_PAIR(1));
      addch(c);
      i++;
    } else if (isprint(c)) {
      // if wrong, then print the char in script with red color.
      attroff(COLOR_PAIR(1));
      attron(COLOR_PAIR(2));
      addch(t->script[i]);
      i++;
    } else if ((int) c == 127) {
      // if backspace, we either ignore (if i == 0), or we "remove" the color
      // from the previous letter.
      if (i == 0) {
        continue;
      } else {
        attroff(COLOR_PAIR(1));
        attroff(COLOR_PAIR(2));
        i--;
        move(0, i);
        addch(t->script[i]);
        move(0, i);
      }
    } else {
      // if it is not a printable character, don't do anything
      continue;
    }
  }
  gettimeofday(&end, NULL);
  getch();
  endwin();
  double time = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) * .000001;
  stats *s = stats_create(t->len, time);
  return s;
}


void print_stats(stats *s) {
  printf("You typed %d characters in %.2lf seconds!\n", s->chars, s->seconds);
  printf("Your WPM was: %.2lf\n", (s->chars / s->seconds) * 12);
}

void stats_destroy(stats *s) {
  free(s);
}
