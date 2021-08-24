#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

char **parsewordlist(const char *fname, int *len) {
  FILE *fp = fopen(fname, "r");
  if (fp == NULL) {
    printf("Could not open file %s\n", fname);
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
  *len = wd_curlen;
  return wd;
}


int main(void) {
  printf("\033[H");
  printf("\033[J");
  char c;
  printf("Hi! Type a character to return to the command prompt");
  scanf("%c", &c);
  const char *fname = "1000_most_common_words.txt";
  if (access(fname, F_OK) == 0) {
    printf("Success! File %s found\n", fname);
    int len = 0;
    char **wordlist = parsewordlist(fname, &len);
    for (int i = 0; i < len; i++) {
      printf("%s\n", wordlist[i]);
    }
  } else {
    printf("File %s does not exist\n", fname);
  }

  // sidenote: tv_sec counts seconds since epoch. tv_usec counts microseconds
  //           between seconds (eg. if you do sleep(1), then it will show 1
  //           second has passed and 100 microseconds. If you do sleep(10), it
  //           will show 10 seconds have passed and 100 microseconds
  struct timeval st, ed;
  gettimeofday(&st, NULL);
  sleep(1);
  gettimeofday(&ed, NULL);
  printf("Current time (by clock_t): %ld\n", ed.tv_usec - st.tv_usec);
  return 0;
}
