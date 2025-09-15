#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int structs15_2() {
  FILE *file1, *file2, *file3;
  char line1[1000], line2[1000];
  char **lines1 = NULL, **lines2 = NULL;
  int count1 = 0, count2 = 0;
  int maxLines = 0;
  int startLine;

  printf("=== Программа объединения двух файлов ===\n\n");

  // Открываем первый файл для чтения
  file1 = fopen("file1.txt", "r");
  if (file1 == NULL) {
    printf("Ошибка: не удалось открыть file1.txt\n");
    printf("Создайте файл file1.txt с текстом.\n");
    return 1;
  }

  // Открываем второй файл для чтения
  file2 = fopen("file2.txt", "r");
  if (file2 == NULL) {
    printf("Ошибка: не удалось открыть file2.txt\n");
    printf("Создайте файл file2.txt с текстом.\n");
    fclose(file1);
    return 1;
  }

  // Подсчитываем количество строк в первом файле
  while (fgets(line1, sizeof(line1), file1)) {
    count1++;
  }

  // Подсчитываем количество строк во втором файле
  while (fgets(line2, sizeof(line2), file2)) {
    count2++;
  }

  printf("Файл file1.txt содержит %d строк\n", count1);
  printf("Файл file2.txt содержит %d строк\n", count2);

  // Определяем максимальное количество строк
  maxLines = (count1 > count2) ? count1 : count2;

  if (maxLines == 0) {
    printf("Оба файла пусты!\n");
    fclose(file1);
    fclose(file2);
    return 1;
  }

  // Выделяем память для хранения строк
  lines1 = (char **)malloc(count1 * sizeof(char *));
  lines2 = (char **)malloc(count2 * sizeof(char *));

  for (int i = 0; i < count1; i++) {
    lines1[i] = (char *)malloc(1000 * sizeof(char));
  }
  for (int i = 0; i < count2; i++) {
    lines2[i] = (char *)malloc(1000 * sizeof(char));
  }

  // Перематываем файлы и читаем строки в массивы
  rewind(file1);
  rewind(file2);

  for (int i = 0; i < count1; i++) {
    fgets(lines1[i], 1000, file1);
    // Удаляем символ новой строки
    int len = strlen(lines1[i]);
    if (len > 0 && lines1[i][len - 1] == '\n') {
      lines1[i][len - 1] = '\0';
    }
  }

  for (int i = 0; i < count2; i++) {
    fgets(lines2[i], 1000, file2);
    // Удаляем символ новой строки
    int len = strlen(lines2[i]);
    if (len > 0 && lines2[i][len - 1] == '\n') {
      lines2[i][len - 1] = '\0';
    }
  }

  // Закрываем входные файлы
  fclose(file1);
  fclose(file2);

  // Запрашиваем у пользователя номер строки
  printf("\nС какой строки начать объединение? (1-%d): ", maxLines);
  scanf("%d", &startLine);

  // Проверка корректности ввода
  if (startLine < 1 || startLine > maxLines) {
    printf("Некорректный номер строки! Используется строка 1.\n");
    startLine = 1;
  }

  // Открываем третий файл для записи
  file3 = fopen("file3.txt", "w");
  if (file3 == NULL) {
    printf("Ошибка создания file3.txt\n");
    // Освобождаем память
    for (int i = 0; i < count1; i++)
      free(lines1[i]);
    for (int i = 0; i < count2; i++)
      free(lines2[i]);
    free(lines1);
    free(lines2);
    return 1;
  }

  printf("\nЗаписываем в file3.txt, начиная со строки %d...\n\n", startLine);

  // Записываем строки начиная с указанной
  int linesWritten = 0;
  for (int i = startLine - 1; i < maxLines; i++) {
    fprintf(file3, "Строка %d: ", i + 1);

    // Добавляем строку из первого файла, если она существует
    if (i < count1) {
      fprintf(file3, "%s", lines1[i]);
    }

    // Добавляем разделитель, если есть строки в обоих файлах
    if (i < count1 && i < count2) {
      fprintf(file3, " | ");
    }

    // Добавляем строку из второго файла, если она существует
    if (i < count2) {
      fprintf(file3, "%s", lines2[i]);
    }

    fprintf(file3, "\n");
    linesWritten++;
  }

  // Теперь дописываем строки с начала до указанной (циклическое объединение)
  if (startLine > 1) {
    printf("Дописываем строки с начала (1-%d)...\n", startLine - 1);
    for (int i = 0; i < startLine - 1; i++) {
      fprintf(file3, "Строка %d: ", i + 1);

      // Добавляем строку из первого файла
      if (i < count1) {
        fprintf(file3, "%s", lines1[i]);
      }

      // Добавляем разделитель
      if (i < count1 && i < count2) {
        fprintf(file3, " | ");
      }

      // Добавляем строку из второго файла
      if (i < count2) {
        fprintf(file3, "%s", lines2[i]);
      }

      fprintf(file3, "\n");
      linesWritten++;
    }
  }

  // Закрываем выходной файл
  fclose(file3);

  printf("\nОбъединение завершено!\n");
  printf("Записано %d строк в файл file3.txt\n", linesWritten);
  printf("\nПример вывода:\n");
  printf("Если файлы содержали:\n");
  printf("  file1.txt: строка1, строка2, строка3\n");
  printf("  file2.txt: текст1, текст2\n");
  printf("И выбрана строка %d, то в file3.txt будет:\n", startLine);
  printf("  Сначала строки с %d до конца, затем с 1 до %d\n", startLine,
         startLine - 1);

  // Освобождаем память
  for (int i = 0; i < count1; i++)
    free(lines1[i]);
  for (int i = 0; i < count2; i++)
    free(lines2[i]);
  free(lines1);
  free(lines2);

  return 0;
}
