#include <stdio.h>

int files15_2() {
  FILE *file1, *file2, *file3;
  char line1[1000], line2[1000];
  int max_lines = 0;
  int current_line = 0;

  // Открываем первый файл для чтения
  file1 = fopen("file1.txt", "r");
  if (file1 == NULL) {
    printf("Ошибка открытия file1.txt\n");
    return 1;
  }

  // Открываем второй файл для чтения
  file2 = fopen("file2.txt", "r");
  if (file2 == NULL) {
    printf("Ошибка открытия file2.txt\n");
    fclose(file1);
    return 1;
  }

  // Сначала определяем количество строк в файлах
  while (fgets(line1, sizeof(line1), file1)) {
    max_lines++;
  }

  int lines_in_file2 = 0;
  while (fgets(line2, sizeof(line2), file2)) {
    lines_in_file2++;
  }

  // Берем максимальное количество строк
  if (lines_in_file2 > max_lines) {
    max_lines = lines_in_file2;
  }

  // Перематываем файлы в начало
  rewind(file1);
  rewind(file2);

  // Открываем третий файл для записи
  file3 = fopen("file3.txt", "w");
  if (file3 == NULL) {
    printf("Ошибка создания file3.txt\n");
    fclose(file1);
    fclose(file2);
    return 1;
  }

  // Выясняем, с какой строки начинать
  int start_line;
  printf("С какой строки начать объединение? (1 - %d): ", max_lines);
  scanf("%d", &start_line);

  if (start_line < 1 || start_line > max_lines) {
    printf("Некорректный номер строки. Используется строка 1.\n");
    start_line = 1;
  }

  current_line = 1;

  // Пропускаем строки до нужной
  while (current_line < start_line) {
    if (fgets(line1, sizeof(line1), file1) == NULL) {
      // Если в первом файле кончились строки, очищаем буфер
      line1[0] = '\0';
    }
    if (fgets(line2, sizeof(line2), file2) == NULL) {
      // Если во втором файле кончились строки, очищаем буфер
      line2[0] = '\0';
    }
    current_line++;
  }

  // Объединяем строки начиная с указанной
  while (current_line <= max_lines) {
    int has_line1 = 0, has_line2 = 0;

    // Читаем строку из первого файла
    if (fgets(line1, sizeof(line1), file1) != NULL) {
      has_line1 = 1;
    }

    // Читаем строку из второго файла
    if (fgets(line2, sizeof(line2), file2) != NULL) {
      has_line2 = 1;
    }

    // Если есть хотя бы одна строка
    if (has_line1 || has_line2) {
      fprintf(file3, "Строка %d: ", current_line);

      if (has_line1) {
        // Убираем символ новой строки из line1
        int len = 0;
        while (line1[len] != '\0' && line1[len] != '\n') {
          len++;
        }
        line1[len] = '\0';
        fputs(line1, file3);
      }

      if (has_line1 && has_line2) {
        fputs(" | ", file3);
      }

      if (has_line2) {
        // Убираем символ новой строки из line2
        int len = 0;
        while (line2[len] != '\0' && line2[len] != '\n') {
          len++;
        }
        line2[len] = '\0';
        fputs(line2, file3);
      }

      fputs("\n", file3);
    }

    current_line++;
  }

  // Теперь копируем строки с начала до указанной (циклическое объединение)
  if (start_line > 1) {
    rewind(file1);
    rewind(file2);

    current_line = 1;
    while (current_line < start_line) {
      int has_line1 = 0, has_line2 = 0;

      if (fgets(line1, sizeof(line1), file1) != NULL) {
        has_line1 = 1;
      }

      if (fgets(line2, sizeof(line2), file2) != NULL) {
        has_line2 = 1;
      }

      if (has_line1 || has_line2) {
        fprintf(file3, "Строка %d: ", current_line);

        if (has_line1) {
          int len = 0;
          while (line1[len] != '\0' && line1[len] != '\n') {
            len++;
          }
          line1[len] = '\0';
          fputs(line1, file3);
        }

        if (has_line1 && has_line2) {
          fputs(" | ", file3);
        }

        if (has_line2) {
          int len = 0;
          while (line2[len] != '\0' && line2[len] != '\n') {
            len++;
          }
          line2[len] = '\0';
          fputs(line2, file3);
        }

        fputs("\n", file3);
      }

      current_line++;
    }
  }

  // Закрываем все файлы
  fclose(file1);
  fclose(file2);
  fclose(file3);

  printf("Объединение завершено. Результат записан в file3.txt\n");

  return 0;
}
