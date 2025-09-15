#include <ctype.h>
#include <stdio.h>
#include <string.h>

int files12_1() {
  FILE *input, *output;
  char line[1000];
  char result[1000];

  // Открываем входной файл для чтения
  input = fopen("input.txt", "r");
  if (input == NULL) {
    printf("Ошибка открытия входного файла\n");
    return 1;
  }

  // Открываем выходной файл для записи
  output = fopen("output.txt", "w");
  if (output == NULL) {
    printf("Ошибка открытия выходного файла\n");
    fclose(input);
    return 1;
  }

  // Читаем файл построчно
  while (fgets(line, sizeof(line), input)) {
    int j = 0;

    // Обрабатываем каждый символ в строке
    for (int i = 0; line[i] != '\0'; i++) {
      // Копируем все символы, кроме тех, что стоят на нечетных местах
      // Позиции считаем с 1, поэтому нечетные - это индексы 0, 2, 4...
      if (i % 2 == 1) { // Четные позиции (2, 4, 6...) имеют нечетные индексы
        result[j++] = line[i];
      }
    }
    result[j] = '\0';

    // Записываем результат в выходной файл
    fputs(result, output);
  }

  // Закрываем файлы
  fclose(input);
  fclose(output);

  printf("Обработка завершена. Результат записан в output.txt\n");

  return 0;
}
