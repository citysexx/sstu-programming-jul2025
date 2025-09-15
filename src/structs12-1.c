#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для хранения даты
typedef struct {
  int day;
  int month;
  int year;
} DATE;

// Функция ввода даты с клавиатуры
void inputDate(DATE *date) {
  printf("Введите день: ");
  scanf("%d", &date->day);
  printf("Введите месяц: ");
  scanf("%d", &date->month);
  printf("Введите год: ");
  scanf("%d", &date->year);
}

// Функция вывода даты на экран
void printDate(DATE date) {
  printf("%02d.%02d.%04d", date.day, date.month, date.year);
}

// Функция проверки високосного года
int isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Функция получения количества дней в месяце
int getDaysInMonth(int month, int year) {
  int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (month == 2 && isLeapYear(year)) {
    return 29;
  }
  return days[month - 1];
}

// Функция вычисления номера дня в году
int getDayOfYear(DATE date) {
  int dayNum = 0;

  // Добавляем дни за полные месяцы
  for (int month = 1; month < date.month; month++) {
    dayNum += getDaysInMonth(month, date.year);
  }

  // Добавляем дни текущего месяца
  dayNum += date.day;

  return dayNum;
}

// Функция вычисления номера дня и месяца по номеру дня в году
DATE getDateFromDayOfYear(int dayOfYear, int year) {
  DATE result;
  result.year = year;
  result.month = 1;
  result.day = dayOfYear;

  // Вычитаем дни каждого месяца, пока не найдем нужный
  while (result.day > getDaysInMonth(result.month, result.year)) {
    result.day -= getDaysInMonth(result.month, result.year);
    result.month++;

    // Проверка на переход в следующий год
    if (result.month > 12) {
      result.month = 1;
      result.year++;
    }
  }

  return result;
}

// Функция поиска даты самой поздней в массиве
DATE findLatestDate(DATE dates[], int count) {
  DATE latest = dates[0];

  for (int i = 1; i < count; i++) {
    // Сравниваем годы
    if (dates[i].year > latest.year) {
      latest = dates[i];
    } else if (dates[i].year == latest.year) {
      // Годы равны, сравниваем месяцы
      if (dates[i].month > latest.month) {
        latest = dates[i];
      } else if (dates[i].month == latest.month) {
        // Месяцы равны, сравниваем дни
        if (dates[i].day > latest.day) {
          latest = dates[i];
        }
      }
    }
  }

  return latest;
}

// Функция загрузки дат из файла
int loadDatesFromFile(DATE dates[], int maxCount) {
  FILE *file = fopen("dates.txt", "r");
  if (file == NULL) {
    printf("Не удалось открыть файл dates.txt\n");
    return 0;
  }

  int count = 0;
  while (count < maxCount &&
         fscanf(file, "%d %d %d", &dates[count].day, &dates[count].month,
                &dates[count].year) == 3) {
    count++;
  }

  fclose(file);
  printf("Загружено %d дат из файла\n", count);
  return count;
}

// Функция сохранения дат в файл
void saveDatesToFile(DATE dates[], int count) {
  FILE *file = fopen("dates.txt", "w");
  if (file == NULL) {
    printf("Не удалось создать файл dates.txt\n");
    return;
  }

  for (int i = 0; i < count; i++) {
    fprintf(file, "%d %d %d\n", dates[i].day, dates[i].month, dates[i].year);
  }

  fclose(file);
  printf("Сохранено %d дат в файл\n", count);
}

// Главное меню
void showMenu12_1() {
  printf("\n===== МЕНЮ РАБОТЫ С ДАТАМИ =====\n");
  printf("1. Ввод новой даты\n");
  printf("2. Вычислить номер дня в году для даты\n");
  printf("3. Вычислить дату по номеру дня в году\n");
  printf("4. Найти самую позднюю дату из массива\n");
  printf("5. Показать все даты\n");
  printf("6. Загрузить даты из файла\n");
  printf("7. Сохранить даты в файл\n");
  printf("0. Выход\n");
  printf("Выберите пункт: ");
}

int structs12_1() {
  DATE dates[100];
  int dateCount = 0;
  int choice;

  printf("Программа работы с датами\n");
  printf("Автоматическая попытка загрузки дат из файла...\n");
  dateCount = loadDatesFromFile(dates, 100);

  do {
    showMenu12_1();
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
      if (dateCount >= 100) {
        printf("Массив дат заполнен!\n");
      } else {
        printf("\n--- Ввод новой даты ---\n");
        inputDate(&dates[dateCount]);
        printf("Дата добавлена: ");
        printDate(dates[dateCount]);
        printf("\n");
        dateCount++;
      }
      break;
    }

    case 2: {
      if (dateCount == 0) {
        printf("Нет дат в массиве!\n");
      } else {
        printf("\n--- Вычисление номера дня в году ---\n");
        printf("Выберите дату (1-%d): ", dateCount);
        int index;
        scanf("%d", &index);
        if (index >= 1 && index <= dateCount) {
          printf("Дата: ");
          printDate(dates[index - 1]);
          int dayNum = getDayOfYear(dates[index - 1]);
          printf(" - это %d-й день года\n", dayNum);
        } else {
          printf("Неверный индекс!\n");
        }
      }
      break;
    }

    case 3: {
      printf("\n--- Вычисление даты по номеру дня ---\n");
      int dayNum, year;
      printf("Введите номер дня в году: ");
      scanf("%d", &dayNum);
      printf("Введите год: ");
      scanf("%d", &year);

      if (dayNum < 1 || dayNum > (isLeapYear(year) ? 366 : 365)) {
        printf("Неверный номер дня для указанного года!\n");
      } else {
        DATE result = getDateFromDayOfYear(dayNum, year);
        printf("%d-й день %d года - это ", dayNum, year);
        printDate(result);
        printf("\n");
      }
      break;
    }

    case 4: {
      if (dateCount == 0) {
        printf("Нет дат в массиве!\n");
      } else {
        printf("\n--- Поиск самой поздней даты ---\n");
        DATE latest = findLatestDate(dates, dateCount);
        printf("Самая поздняя дата: ");
        printDate(latest);
        printf("\n");
      }
      break;
    }

    case 5: {
      if (dateCount == 0) {
        printf("Нет дат в массиве!\n");
      } else {
        printf("\n--- Список всех дат ---\n");
        for (int i = 0; i < dateCount; i++) {
          printf("%d. ", i + 1);
          printDate(dates[i]);
          printf(" (день %d в году)\n", getDayOfYear(dates[i]));
        }
      }
      break;
    }

    case 6: {
      printf("\n--- Загрузка дат из файла ---\n");
      dateCount = loadDatesFromFile(dates, 100);
      break;
    }

    case 7: {
      printf("\n--- Сохранение дат в файл ---\n");
      saveDatesToFile(dates, dateCount);
      break;
    }

    case 0:
      printf("Выход из программы...\n");
      break;

    default:
      printf("Неверный выбор!\n");
    }
  } while (choice != 0);

  return 0;
}
