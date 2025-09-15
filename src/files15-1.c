#include <ctype.h>
#include <stdio.h>
#include <string.h>

int files15_1() {
  FILE *input;
  char line[1000];
  char result[2000]; // Буфер для накопления результата
  int result_pos = 0;

  // Открываем входной файл для чтения
  input = fopen("input.txt", "r");
  if (input == NULL) {
    printf("Ошибка открытия входного файла\n");
    return 1;
  }

  printf("Слово, образованное k-ыми символами каждой строки:\n");

  // Читаем файл построчно
  while (fgets(line, sizeof(line), input)) {
    int len = strlen(line);

    // Убираем символ новой строки, если есть
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
      len--;
    }

    // Обрабатываем каждую позицию k
    for (int k = 0; k < len; k++) {
      printf("\nПозиция %d: ", k + 1);

      // Сбрасываем позицию в начало файла
      rewind(input);
      result_pos = 0;

      // Читаем файл заново для каждой позиции k
      while (fgets(line, sizeof(line), input)) {
        int line_len = strlen(line);

        // Убираем символ новой строки
        if (line_len > 0 && line[line_len - 1] == '\n') {
          line[line_len - 1] = '\0';
          line_len--;
        }

        // Если в строке есть k-й символ (позиция k считается с 1)
        if (k < line_len) {
          result[result_pos++] = line[k];
        }
      }

      // Завершаем строку
      result[result_pos] = '\0';

      // Выводим полученное слово
      if (result_pos > 0) {
        printf("%s", result);
      } else {
        printf("(нет символов на этой позиции)");
      }

      // Возвращаемся к началу файла для следующей итерации
      rewind(input);
      // Читаем первую строку, чтобы определить длину для следующей итерации
      if (!fgets(line, sizeof(line), input)) {
        break;
      }
      len = strlen(line);
      if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
        len--;
      }
    }

    // Выходим после обработки первой строки (для определения максимального k)
    break;
  }

  printf("\n");

  // Закрываем файл
  fclose(input);

  return 0;
}
