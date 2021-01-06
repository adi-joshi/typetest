/*
 * Created by: adi-joshi
 * Date: 28 Dec 2020
 * Enjoy!
 */


// This is an implementation of a typing test.

// Program progression:
/*
   - Read words from 1000_most_common_words.txt (read_words)
   - Print out 50 of them randomly (print_rand)
   - Time and scan the input until '\n' (time_and_scan)
   - Print out WPM (time_and_scan)
 */

// IMPORTANT TERMINOLOGY:
//
// words: a character array
// array of words: This is an array that stores pointers to character arrays.
// "words": words is a parameter of the function.

// Includes:
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

// Global constants:
const int TIMES = 50; // number of words printed for each typing test
const int MAX_WORD_LEN = 50; //length of the longest word in the wordlist file

// a struct strarr stores the wordlist and the current and maximum length of
//   wordlist
struct strarr {
  char **wordlist;
  int curlen;
  int maxlen;
};

struct test {
  char *script;
  int curlen;
  int maxlen;
};

struct stats {
  int time;
  int mistakes;
};

// strarr_create() makes a struct strarr with curlen as 0 and maxlen as 1, and
//   returns it.
// effects: writes to memory
// time: O(1)
struct strarr *strarr_create(void) {

  // allocating memory for a struct strarr
  struct strarr *retval = malloc(sizeof(struct strarr));
  assert(retval);

  // setting parameters
  retval->curlen = 0;
  retval->maxlen = 1;

  // allocating memory for the wordlist
  retval->wordlist = malloc(sizeof(char *) * retval->maxlen);
  assert(retval->wordlist);

  return retval;
}

// strarr_destroy(s) frees all allocated memory in s.
// effects: invalidates s and contents of s
// requires: s is a valid pointer.
//           s->wordlist is a valid pointer
//           s->wordlist is a valid pointer to pointers.
// time: O(n), where n is the number of words in wordlist
void strarr_destroy(struct strarr *s) {

  // asserts:
  assert(s);

  int len = s->curlen;

  // freeing all words from wordlist
  for (int i = 0; i < len; i++) {
    free(s->wordlist[i]);
  }

  // freeing wordlist and s
  free(s->wordlist);
  free(s);
}

// read_wordlist(s,path) reads the words from a file, given by path, and
//   stores them in s.
// requires: s and path are valid pointers
//           path is a valid path
// time: O(c) [amortized]??? where c is the number of characters in the file
void read_wordlist(struct strarr *s, char *path) {

  // asserts:
  assert(s);
  assert(path);

  // FILE * is a struct in stdio that handles File I/O
  // We open the file at path, and read ("r") from the file.
  FILE *fp = fopen(path,"r");

  // a character array to store words read from the file
  char fp_word[MAX_WORD_LEN];

  // while we can still read words from the file
  while(fscanf(fp, "%s\n", fp_word) != EOF) {

    // we malloc a character array and copy fp_word onto it.
    int word_len = strlen(fp_word);
    char *word = malloc(sizeof(char) * (word_len + 1));
    strcpy(word,fp_word);

    // we add the character array to the wordlist
    s->wordlist[s->curlen] = word;
    s->curlen++;

    // if we have run out of memory, we use a doubling strategy.
    if (s->curlen == s->maxlen) {
      s->maxlen *= 2;
      s->wordlist = realloc(s->wordlist, sizeof(char *) * s->maxlen);
    }
  }

  // reallocing for efficiency.
  s->wordlist= realloc(s->wordlist, sizeof(char *) * s->curlen);
}




// test_create(s) creates a struct test, which has a selection of words from
//   the wordlist s, and it returns the test.
// requires: s is a valid pointer
// effects: allocates memory
// time: O(n * m), where n is the longest word in the wordlist, and m is the
//   total numbers of words we choose.
struct test *test_create(struct strarr *s) {
  struct test *t = malloc(sizeof(struct test));
  assert(t);

  t->script = malloc(sizeof(char *));
  t->curlen = 0;
  t->maxlen = 1;

  // https://stackoverflow.com/questions/1108780/why-do-i-always-get-the-same-sequence-of-random-numbers-with-rand
  // seeding with time, because need random number each time, so that rand()
  //   returns new numbers after running this file.
  srand(time(NULL));

  for (int i = 0; i < TIMES; i++) {

    // finding a random number, and then using the word at that index in the
    //   wordlist
    int x = rand() % s->curlen;
    char *word = s->wordlist[x];
    int wordlen = strlen(word);

    // copying the word character by character
    for (int i = 0; i < wordlen; i++) {
      t->script[t->curlen] = word[i];
      t->curlen++;

      // doubling strategy (curlen = maxlen - 1, because we are adding a ' '
      //   character later.
      if (t->curlen >= t->maxlen - 1) {
        t->maxlen *= 2;
        t->script = realloc(t->script, sizeof(char) * t->maxlen);
      }
    }

    // adding a space to separate words
    t->script[t->curlen] = ' ';
    t->curlen++;
  }

  // adding null terminator, incrementing curlen, reallocing memory and
  //   returning the test.
  t->script[t->curlen - 1] = '\0';
  t->curlen++;
  t->script = realloc(t->script, sizeof(char) * t->curlen);
  t->maxlen = t->curlen;
  return t;
}




// test_print(t) prints the test t.
// requires: t is a valid pointer
// time: O(l), where l is the number of characters in t.
void test_print(struct test *t) {
  assert(t);

  int len = strlen(t->script);

  // prints the test character by character.
  for (int i = 0; i < len; i++) {
    printf("%c", t->script[i]);
  }
  printf("\n");
}


// test_destroy(t) destroys the test t.
// requires: t is a valid pointer.
// effects: invalidates t
// time: O(1)
void test_destroy(struct test *t) {
  assert(t);

  free(t->script);
}


// scan_input(t) scans the input, and checks if each character matches the
//   test exactly. Outputs the number of mistakes (i.e. the number of places
//   where the input and the test differ).
// requires: t is a valid pointer.
// effects: reads input
// time: O(l), where l is the number of characters in t.
int scan_input(struct test *t) {
  assert(t);

  int len = strlen(t->script);
  int mistakes = 0;

  int i = 0;
  while (i < len) {

    // scanning characters, and checking if they differ from the script.
    char c = ' ';
    scanf("%c", &c);    
    if (c != t->script[i]) {
      mistakes++;
    }
    i++;
  }

  return mistakes;
}


// stats_create(time, mistakes) creates a struct stats with the fields time
//   (in seconds) and mistakes.
// requires: time >= 0
//           mistakes >= 0
// effects: allocates memory
// time: O(1)
struct stats *stats_create(int time, int mistakes) {
  struct stats *retval = malloc(sizeof(struct stats));
  assert(retval);

  // Floating point exception: 8
  if (time == 0) {
    time++;
  }

  // assigning fields
  retval->time = time;
  retval->mistakes = mistakes;

  return retval;
}

// stats_destroy(s) destroys s.
// requires: s is a valid pointer.
// effects: invalidates s.
// time: O(1)
void stats_destroy(struct stats *s) {
  assert(s);

  free(s);
}

// stats_prints(s) prints the stats in s in a nice way.
// requires: s is a valid pointer
// time: O(1)
void stats_print(struct stats *s) {
  assert(s);

  unsigned long long int wpm = (TIMES * 6000) / s->time;

  printf("WPM: %llu.%.2llu with %d mistakes\n", wpm / 100, wpm % 100,
                                                s->mistakes);
}


// Handles functions and user input.
int main(void) {

  // instructions for the user.
  printf("Welcome to my Typing Test!\n");
  printf("Press enter to start.\n");

  // waiting for a newline char to start the typing test.
  char c = ' ';
  while (c != '\n') {
    scanf("%c", &c);
  }

  // reading in the wordlist from a .txt file, and creating a test.
  char *dir = "1000_most_common_words.txt";
  struct strarr *s = strarr_create();
  read_wordlist(s,dir);
  struct test *t = test_create(s);
  test_print(t);

  // for timing the input
  time_t start_t = 0;
  time_t end_t = 0;

  // timing the input
  time(&start_t);
  int mistakes = scan_input(t);
  time(&end_t);
  double actual_t = difftime(end_t, start_t);
  
  // Floating Point Exception: 8  
  if (actual_t == 0) {
    actual_t = 1;
  }

  // Creates a struct stats and outputs the stats.
  struct stats *wpm = stats_create(actual_t, mistakes);
  stats_print(wpm);
  strarr_destroy(s);
  test_destroy(t);
  stats_destroy(wpm);
  return 0;
}
