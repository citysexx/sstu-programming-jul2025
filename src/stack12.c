// variant12.c
// Вариант 12:
// Создать список из слов, в который все слова исходного текста входят только
// один раз. Чтение из stdin, вывод уникальных слов (по одному на строку) в
// порядке первого появления. Слова: последовательности букв/цифр/подчёркиваний.
// Сравнение без учёта регистра.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAP 128

static char *strdup_range(const char *s, size_t len) {
  char *res = malloc(len + 1);
  if (!res) {
    perror("malloc");
    exit(1);
  }
  memcpy(res, s, len);
  res[len] = '\0';
  return res;
}

int stack12(void) {
  // будем читать stdin побайтно, выделяя слова [A-Za-z0-9_]
  int c;
  char *word = NULL;
  size_t wcap = 0, wlen = 0;

  char **words = malloc(INIT_CAP * sizeof(char *));
  char **words_lower =
      malloc(INIT_CAP * sizeof(char *)); // для сравнения (lowercase)
  if (!words || !words_lower) {
    perror("malloc");
    return 1;
  }
  size_t cap = INIT_CAP, count = 0;

  while ((c = getchar()) != EOF) {
    if (isalnum(c) || c == '_') {
      if (wlen + 1 >= wcap) {
        size_t newcap = wcap ? wcap * 2 : 64;
        char *tmp = realloc(word, newcap);
        if (!tmp) {
          perror("realloc");
          return 1;
        }
        word = tmp;
        wcap = newcap;
      }
      word[wlen++] = (char)c;
    } else {
      if (wlen > 0) {
        // завершить слово
        char *orig = strdup_range(word, wlen);
        // lower for comparison
        char *low = malloc(wlen + 1);
        if (!low) {
          perror("malloc");
          return 1;
        }
        for (size_t i = 0; i < wlen; ++i)
          low[i] = (char)tolower((unsigned char)orig[i]);
        low[wlen] = '\0';

        // проверить на дубликат (по lower)
        int found = 0;
        for (size_t i = 0; i < count; ++i) {
          if (strcmp(words_lower[i], low) == 0) {
            found = 1;
            break;
          }
        }
        if (!found) {
          if (count >= cap) {
            size_t ncap = cap * 2;
            char **nw = realloc(words, ncap * sizeof(char *));
            char **nl = realloc(words_lower, ncap * sizeof(char *));
            if (!nw || !nl) {
              perror("realloc");
              return 1;
            }
            words = nw;
            words_lower = nl;
            cap = ncap;
          }
          words[count] = orig;
          words_lower[count] = low;
          count++;
        } else {
          free(orig);
          free(low);
        }
        wlen = 0;
      }
      // игнорируем символы-разделители
    }
  }
  // в конце — если осталось слово (EOF сразу после слова)
  if (wlen > 0) {
    char *orig = strdup_range(word, wlen);
    char *low = malloc(wlen + 1);
    if (!low) {
      perror("malloc");
      return 1;
    }
    for (size_t i = 0; i < wlen; ++i)
      low[i] = (char)tolower((unsigned char)orig[i]);
    low[wlen] = '\0';
    int found = 0;
    for (size_t i = 0; i < count; ++i) {
      if (strcmp(words_lower[i], low) == 0) {
        found = 1;
        break;
      }
    }
    if (!found) {
      if (count >= cap) {
        size_t ncap = cap * 2;
        char **nw = realloc(words, ncap * sizeof(char *));
        char **nl = realloc(words_lower, ncap * sizeof(char *));
        if (!nw || !nl) {
          perror("realloc");
          return 1;
        }
        words = nw;
        words_lower = nl;
        cap = ncap;
      }
      words[count] = orig;
      words_lower[count] = low;
      count++;
    } else {
      free(orig);
      free(low);
    }
  }

  free(word);

  // выводим уникальные слова (нижний регистр для единообразия)
  for (size_t i = 0; i < count; ++i) {
    printf("%s\n", words_lower[i]);
    free(words[i]);
    free(words_lower[i]);
  }

  free(words);
  free(words_lower);
  return 0;
}
