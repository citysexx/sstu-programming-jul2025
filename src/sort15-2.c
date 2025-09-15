#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEOPLE 1000
#define MAX_LEN 100

typedef struct {
  char surname[MAX_LEN];
  char name[MAX_LEN];
} Person;

// Функция сравнения для сортировки по фамилии и имени
int compare(const Person *a, const Person *b) {
  int cmp = strcmp(a->surname, b->surname);
  if (cmp == 0) {
    return strcmp(a->name, b->name);
  }
  return cmp;
}

void bubble_sort(Person arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (compare(&arr[j], &arr[j + 1]) > 0) {
        Person tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
      }
    }
  }
}

int sort15_2() {
  FILE *fin = fopen("data.txt", "r");
  FILE *fout = fopen("outdata.txt", "w");

  if (!fin || !fout) {
    perror("Ошибка при открытии файлов");
    return 1;
  }

  Person people[MAX_PEOPLE];
  int count = 0;

  // Читаем фамилию и имя
  while (fscanf(fin, "%s %s", people[count].surname, people[count].name) == 2) {
    count++;
    if (count >= MAX_PEOPLE)
      break;
  }

  fclose(fin);

  // Сортировка пузырьком
  bubble_sort(people, count);

  // Записываем в outdata.txt
  for (int i = 0; i < count; i++) {
    fprintf(fout, "%s %s\n", people[i].surname, people[i].name);
  }

  fclose(fout);

  printf("Сортировка завершена! Результат в outdata.txt\n");
  return 0;
}
