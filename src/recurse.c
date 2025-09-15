#include <limits.h>
#include <stdio.h>

// Рекурсивная функция для поиска минимального элемента массива
int findMin(int arr[], int n) {
  // Базовый случай: если массив содержит только один элемент
  if (n == 1) {
    return arr[0];
  }

  // с минимумом остальной части массива
  int minRest = findMin(arr + 1, n - 1);

  // Возвращаем меньший из двух элементов
  return (arr[0] < minRest) ? arr[0] : minRest;
}

int recurse() {
  int n;

  printf("Введите количество элементов массива: ");
  scanf("%d", &n);

  // Проверка корректности ввода
  if (n <= 0) {
    printf("Количество элементов должно быть больше 0\n");
    return 1;
  }

  int arr[n];

  printf("Введите %d элементов массива:\n", n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  // Вывод массива
  printf("Массив: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  // Поиск минимального элемента с помощью первой функции
  int min1 = findMin(arr, n);
  printf("Минимальный элемент: %d\n", min1);

  return 0;
}
