#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "quotelist.h"

// creates quotelist with quotes with length len
static quotelist *quotelist_create(char **quotes, int len) {
  quotelist *qt = malloc(sizeof(quotelist));
  qt->len = len;
  qt->quotes = quotes;
  return qt;
}

quotelist *quotelist_from_file(const char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Could not open file %s\n", filename);
    printf("Exiting...\n");
    exit(1);
  }
  int wd_curlen = 0;
  int wd_maxlen = 1;
  char **wd = malloc(sizeof(char *) * wd_maxlen);

  // code modified from stackoverflow.com/questions/3501338/c-read-file-line-by-line
  size_t l_len = 0;
  char *line = NULL;
  ssize_t read;
  while((read = getline(&line, &l_len, fp)) != -1) {
    char *quote = malloc(sizeof(char) * l_len);
    int i = 0;
    for(; i < l_len; i++) {
      if (line[i] == '\n') {
        break;
      } else {
        quote[i] = line[i];
      }
    }
    quote[i] = '\0';
    i++;
    quote = realloc(quote, sizeof(char) * i);
    wd[wd_curlen] = quote;
    wd_curlen++;
    if (wd_curlen == wd_maxlen) {
      wd_maxlen *= 2;
      wd = realloc(wd, sizeof(char *) * wd_maxlen);
    }
  }
  fclose(fp);
  wd = realloc(wd, sizeof(char *) * wd_curlen);
  quotelist *qt = quotelist_create(wd, wd_curlen);
  return qt;
}

void quotelist_destroy(quotelist *qt) {
  for (int i = 0; i < qt->len; i++) {
    free(qt->quotes[i]);
  }
  free(qt->quotes);
  free(qt);
}
