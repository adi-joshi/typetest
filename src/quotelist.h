#ifndef QUOTELIST_H_
#define QUOTELIST_H_

typedef struct quotelist {
  char **quotes;
  int len;
} quotelist;

quotelist *quotelist_from_file(const char *filename);

void quotelist_destroy(quotelist *qt);

#endif
