#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10

// Функция для печати матрицы
void printMatrix15_1(int matrix[MAX_SIZE][MAX_SIZE], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%4d ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// Сортировка пузырьком по возрастанию
void bubbleSortAsc(int arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

// Чтение матрицы из файла data.txt
int readMatrixFromFile15_1(int matrix[MAX_SIZE][MAX_SIZE]) {
  FILE *file = fopen("data.txt", "r");
  if (file == NULL) {
    printf("Файл data.txt не найден. Будет создана случайная матрица.\n");
    return -1;
  }

  int n;
  if (fscanf(file, "%d", &n) != 1 || n < 1 || n > MAX_SIZE) {
    printf("Ошибка чтения размера матрицы из файла\n");
    fclose(file);
    return -1;
  }

  // Читаем матрицу из файла
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (fscanf(file, "%d", &matrix[i][j]) != 1) {
        printf("Ошибка чтения матрицы из файла\n");
        fclose(file);
        return -1;
      }
    }
  }

  fclose(file);
  return n;
}

// Запись результата в файл outdata.txt
void writeResultToFile15_1(int matrix[MAX_SIZE][MAX_SIZE], int n) {
  FILE *file = fopen("outdata.txt", "w");
  if (file != NULL) {
    fprintf(file, "Вариант 15 - Задача 1\n");
    fprintf(file, "Результат сортировки главных диагоналей по возрастанию "
                  "методом пузырька:\n\n");
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        fprintf(file, "%4d ", matrix[i][j]);
      }
      fprintf(file, "\n");
    }
    fclose(file);
    printf("Результат записан в файл outdata.txt\n");
  } else {
    printf("Ошибка записи в файл outdata.txt\n");
  }
}

int sort15_1() {
  printf("===============================================\n");
  printf("ВАРИАНТ 15 - ЗАДАЧА 1\n");
  printf("===============================================\n");
  printf("Дана матрица размерностью nxn, содержащая целые числа.\n");
  printf("Отсортировать главные диагонали матрицы по возрастанию\n");
  printf("элементов методом пузырька\n\n");

  int matrix[MAX_SIZE][MAX_SIZE];
  int n;

  // Пытаемся прочитать из файла
  n = readMatrixFromFile15_1(matrix);

  // Если не удалось, создаем случайную матрицу
  if (n == -1) {
    printf("Введите размер матрицы n (1-%d): ", MAX_SIZE);
    scanf("%d", &n);

    if (n > MAX_SIZE || n < 1) {
      printf("Размер матрицы должен быть от 1 до %d\n", MAX_SIZE);
      return 1;
    }

    // Заполняем матрицу случайными числами
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        matrix[i][j] = rand() % 21 - 10; // числа от -10 до 10
      }
    }
  }

  printf("Исходная матрица %dx%d:\n", n, n);
  printMatrix15_1(matrix, n);

  // Работаем с главной диагональю (слева-направо, сверху-вниз)
  int mainDiagonal[MAX_SIZE];
  printf("Главная диагональ до сортировки: ");
  for (int i = 0; i < n; i++) {
    mainDiagonal[i] = matrix[i][i];
    printf("%d ", mainDiagonal[i]);
  }
  printf("\n");

  // Сортируем главную диагональ по возрастанию методом пузырька
  bubbleSortAsc(mainDiagonal, n);

  printf("Главная диагональ после сортировки: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", mainDiagonal[i]);
  }
  printf("\n");

  // Помещаем отсортированную главную диагональ обратно
  for (int i = 0; i < n; i++) {
    matrix[i][i] = mainDiagonal[i];
  }

  // Работаем с побочной диагональю (справа-налево, сверху-вниз)
  int antiDiagonal[MAX_SIZE];
  printf("Побочная диагональ до сортировки: ");
  for (int i = 0; i < n; i++) {
    antiDiagonal[i] = matrix[i][n - 1 - i];
    printf("%d ", antiDiagonal[i]);
  }
  printf("\n");

  // Сортируем побочную диагональ по возрастанию методом пузырька
  bubbleSortAsc(antiDiagonal, n);

  printf("Побочная диагональ после сортировки: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", antiDiagonal[i]);
  }
  printf("\n");

  // Помещаем отсортированную побочную диагональ обратно
  for (int i = 0; i < n; i++) {
    matrix[i][n - 1 - i] = antiDiagonal[i];
  }

  printf("\nМатрица после сортировки обеих главных диагоналей:\n");
  printMatrix15_1(matrix, n);

  // Записываем результат в файл
  writeResultToFile15_1(matrix, n);

  return 0;
}

/*
Инструкции по использованию:

1. Компиляция: gcc -o variant15_task1 variant15_task1.c
2. Запуск: ./variant15_task1

Файлы:
- data.txt (входной, опциональный): первая строка - размер матрицы n, затем n
строк по n чисел
- outdata.txt (выходной): результат сортировки

Пример data.txt:
4
9 2 3 1
5 8 7 4
6 2 1 3
7 5 9 2

Программа сортирует главную диагональ (слева-направо) и побочную диагональ
(справа-налево) по возрастанию методом пузырька.

Примечание: если элемент находится на пересечении диагоналей (для нечетного n),
он будет изменен дважды - сначала при сортировке главной, потом побочной
диагонали.
*/
