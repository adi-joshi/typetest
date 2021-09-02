#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <ctype.h>
#include "test.h"
#include "ncurses.h"

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
  script = realloc(script, sizeof(char) * curlen);
  test *t = test_create(script, curlen);
  return t;
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

void test_destroy(test *t) {
  free(t->script);
  free(t);
}
