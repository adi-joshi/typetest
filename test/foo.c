#include <stdio.h>
#include "ncurses.h"

int main(void) {
  initscr();
  printw("Hello World!");
  refresh();
  while(1) {
    char c = getch();
    if (c == 'a') {
      printf("\033[42m");
    } else {
      printf("\033[41m");
    }
    printf("%c", c);
  }
  endwin();
  return 0;
}
