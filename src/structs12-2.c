#include <ctype.h>
#include <stdio.h>
#include <string.h>

int structs12_2() {
  FILE *input, *output;
  char line[1000];
  char result[1000];

  // Открываем входной файл для чтения
  input = fopen("input.txt", "r");
  if (input == NULL) {
    printf("Ошибка: не удалось открыть файл input.txt\n");
    printf("Создайте файл input.txt с текстом для обработки.\n");
    return 1;
  }

  // Открываем выходной файл для записи
  output = fopen("output.txt", "w");
  if (output == NULL) {
    printf("Ошибка: не удалось создать файл output.txt\n");
    fclose(input);
    return 1;
  }

  printf("Обработка файла input.txt...\n");
  printf("Переписываем строки, удаляя символы на нечетных местах.\n\n");

  int lineNum = 0;

  // Читаем файл построчно
  while (fgets(line, sizeof(line), input)) {
    lineNum++;
    int j = 0;

    printf("Строка %d:\n", lineNum);
    printf("  Исходная: %s", line);

    // Обрабатываем каждый символ в строке
    for (int i = 0; line[i] != '\0'; i++) {
      // Копируем символы на четных местах (позиции 2, 4, 6...)
      // В массиве это индексы 1, 3, 5... (т.к. индексация с 0)
      if (i % 2 == 1) {
        result[j++] = line[i];
      }
    }
    result[j] = '\0';

    printf("  Результат: %s", result);
    if (result[strlen(result) - 1] != '\n') {
      printf("\n");
    }
    printf("\n");

    // Записываем результат в выходной файл
    fputs(result, output);
  }

  // Закрываем файлы
  fclose(input);
  fclose(output);

  printf("Обработка завершена!\n");
  printf("Результат записан в файл output.txt\n");

  return 0;
}
