#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define MAX_NAME_LENGTH 50

// Структура для хранения данных
typedef struct {
    char surname[MAX_NAME_LENGTH];
    int members;
} Family;

// Сортировка семей по убыванию количества членов методом вставки
void insertionSortFamiliesDesc(Family families[], int count) {
    for (int i = 1; i < count; i++) {
        Family key = families[i];
        int j = i - 1;
        
        // Сравниваем по количеству членов семьи (убывание)
        while (j >= 0 && families[j].members < key.members) {
            families[j + 1] = families[j];
            j--;
        }
        families[j + 1] = key;
    }
}

// Печать данных о семьях
void printFamilies(Family families[], int count) {
    printf("%-20s %s\n", "Фамилия", "Количество членов");
    printf("----------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s %d\n", families[i].surname, families[i].members);
    }
    printf("\n");
}

// Чтение данных из файла data.txt
int readFamiliesFromFile(Family families[]) {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Файл data.txt не найден.\n");
        printf("Создайте файл со следующим форматом:\n");
        printf("количество_записей\n");
        printf("фамилия1 количество_членов1\n");
        printf("фамилия2 количество_членов2\n");
        printf("...\n");
        return -1;
    }
    
    int count;
    if (fscanf(file, "%d", &count) != 1 || count < 1 || count > MAX_RECORDS) {
        printf("Ошибка чтения количества записей из файла\n");
        fclose(file);
        return -1;
    }
    
    for (int i = 0; i < count; i++) {
        if (fscanf(file, "%s %d", families[i].surname, &families[i].members) != 2) {
            printf("Ошибка чтения данных семьи %d из файла\n", i + 1);
            fclose(file);
            return -1;
        }
    }
    
    fclose(file);
    return count;
}

// Запись результата в файл outdata.txt
void writeResultToFile12_2(Family families[], int count) {
    FILE *file = fopen("outdata.txt", "w");
    if (file != NULL) {
        fprintf(file, "Вариант 12 - Задача 2\n");
        fprintf(file, "Результат сортировки семей по убыванию количества членов методом вставки:\n\n");
        fprintf(file, "%-20s %s\n", "Фамилия", "Количество членов");
        fprintf(file, "----------------------------------------\n");
        for (int i = 0; i < count; i++) {
            fprintf(file, "%-20s %d\n", families[i].surname, families[i].members);
        }
        fclose(file);
        printf("Результат записан в файл outdata.txt\n");
    } else {
        printf("Ошибка записи в файл outdata.txt\n");
    }
}

// Создание тестовых данных
void createTestData() {
    Family families[] = {
        {"Иванов", 4},
        {"Петров", 2},
        {"Сидоров", 6},
        {"Козлов", 3},
        {"Морозов", 5},
        {"Новиков", 1},
        {"Федоров", 7},
        {"Кузнецов", 4}
    };
    int count = 8;
    
    FILE *file = fopen("data.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d\n", count);
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s %d\n", families[i].surname, families[i].members);
        }
        fclose(file);
        printf("Создан тестовый файл data.txt с %d записями\n", count);
    }
}

int sort12_2() {
    printf("===============================================\n");
    printf("ВАРИАНТ 12 - ЗАДАЧА 2\n");
    printf("===============================================\n");
    printf("Переписать данные из файла data.txt в файл outdata.txt,\n");
    printf("отсортировав их по убыванию количества членов семьи\n");
    printf("методом вставки\n\n");
    
    Family families[MAX_RECORDS];
    int count;
    
    // Пытаемся прочитать данные из файла
    count = readFamiliesFromFile(families);
    
    // Если файл не найден, предлагаем создать тестовые данные
    if (count == -1) {
        char choice;
        printf("Создать тестовый файл data.txt? (y/n): ");
        scanf(" %c", &choice);
        
        if (choice == 'y' || choice == 'Y') {
            createTestData();
            count = readFamiliesFromFile(families);
            if (count == -1) {
                printf("Ошибка создания тестовых данных\n");
                return 1;
            }
        } else {
            printf("Программа завершена\n");
            return 0;
        }
    }
    
    printf("Прочитано %d записей из файла data.txt\n\n", count);
    
    printf("Данные до сортировки:\n");
    printFamilies(families, count);
    
    // Сортируем семьи по убыванию количества членов методом вставки
    printf("Выполняется сортировка по убыванию количества членов семьи...\n");
    insertionSortFamiliesDesc(families, count);
    
    printf("Данные после сортировки:\n");
    printFamilies(families, count);
    
    // Записываем результат в файл
    writeResultToFile12_2(families, count);
    
    return 0;
}

/*
Инструкции по использованию:

1. Компиляция: gcc -o variant12_task2 variant12_task2.c
2. Запуск: ./variant12_task2

Файлы:
- data.txt (входной): первая строка - количество записей, затем записи в формате "фамилия количество_членов"
- outdata.txt (выходной): отсортированные данные

Пример data.txt:
5
Иванов 4
Петров 2
Сидоров 6
Козлов 3
Морозов 5

Программа сортирует семьи по убыванию количества членов методом вставки.
*/
