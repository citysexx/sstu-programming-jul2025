// variant15.c
// Вариант 15:
// Создать список из чисел. Создать новый список, записав в него сначала
// все отрицательные элементы из исходного списка, затем все положительные.
// Чтение: сначала n (кол-во), затем n целых чисел. Вывод: новый список по
// одному числу в строке.

#include <stdio.h>
#include <stdlib.h>

int stack15(void) {
  long n;
  if (scanf("%ld", &n) != 1) {
    fprintf(stderr, "Expected number of elements 'n' on input\n");
    return 1;
  }
  if (n < 0) {
    fprintf(stderr, "n must be non-negative\n");
    return 1;
  }
  long *a = malloc(sizeof(long) * n);
  if (!a) {
    perror("malloc");
    return 1;
  }
  for (long i = 0; i < n; ++i) {
    if (scanf("%ld", &a[i]) != 1) {
      fprintf(stderr, "Failed to read element %ld\n", i);
      free(a);
      return 1;
    }
  }

  // Сначала отрицательные
  for (long i = 0; i < n; ++i) {
    if (a[i] < 0)
      printf("%ld\n", a[i]);
  }
  // Затем все неотрицательные (0 и положительные)
  for (long i = 0; i < n; ++i) {
    if (a[i] >= 0)
      printf("%ld\n", a[i]);
  }

  free(a);
  return 0;
}
