#include <stdio.h>
#include "ncurses.h"

int main(void) {
  initscr();
  clear();
  refresh();
  noecho();
  char c;
  while(c = getch()) {
    if (c == 127) {
      addch('a');
    }
  }
  return 0;
}
