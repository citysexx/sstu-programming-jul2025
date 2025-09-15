#include <stdio.h>
#include <string.h>

int files12_2() {
  FILE *input, *output;
  char line[1000];
  char word[100];

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
    int len = strlen(line);
    int word_start = 0;
    int in_word = 0;

    // Обрабатываем строку посимвольно
    for (int i = 0; i <= len; i++) {
      // Проверяем, является ли текущий символ разделителем
      if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' ||
          line[i] == '\0') {
        if (in_word) {
          // Копируем слово
          int word_len = i - word_start;
          strncpy(word, &line[word_start], word_len);
          word[word_len] = '\0';

          // Меняем местами первый и последний символы слова
          if (word_len > 1) {
            char temp = word[0];
            word[0] = word[word_len - 1];
            word[word_len - 1] = temp;
          }

          // Записываем измененное слово
          fputs(word, output);

          // Если это не конец строки, добавляем разделитель
          if (line[i] != '\0') {
            fputc(line[i], output);
          }

          in_word = 0;
        } else if (line[i] == ' ' || line[i] == '\t') {
          // Записываем разделитель
          fputc(line[i], output);
        }
      } else {
        if (!in_word) {
          word_start = i;
          in_word = 1;
        }
      }
    }
  }

  // Закрываем файлы
  fclose(input);
  fclose(output);

  printf("Обработка завершена. Результат записан в output.txt\n");

  return 0;
}
