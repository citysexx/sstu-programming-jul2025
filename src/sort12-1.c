#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10

// Функция для печати матрицы
void printMatrix12_1(int matrix[MAX_SIZE][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Сортировка вставками по убыванию
void insertionSortDesc(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Чтение матрицы из файла data.txt
int readMatrixFromFile12_1(int matrix[MAX_SIZE][MAX_SIZE]) {
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
void writeResultToFile12_1(int matrix[MAX_SIZE][MAX_SIZE], int n) {
    FILE *file = fopen("outdata.txt", "w");
    if (file != NULL) {
        fprintf(file, "Вариант 12 - Задача 1\n");
        fprintf(file, "Результат сортировки диагоналей выше главной по убыванию методом вставки:\n\n");
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

int sort12_1() {
    printf("===============================================\n");
    printf("ВАРИАНТ 12 - ЗАДАЧА 1\n");
    printf("===============================================\n");
    printf("Дана матрица размерностью nxn, содержащая целые числа.\n");
    printf("Отсортировать диагонали матрицы, расположенные выше главной\n");
    printf("по убыванию элементов методом вставки\n\n");
    
    int matrix[MAX_SIZE][MAX_SIZE];
    int n;
    
    // Пытаемся прочитать из файла
    n = readMatrixFromFile12_1(matrix);
    
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
    printMatrix12_1(matrix, n);
    
    // Сортируем диагонали выше главной
    printf("Сортировка диагоналей выше главной по убыванию:\n");
    for (int k = 1; k < n; k++) {
        int diagonal[MAX_SIZE];
        int size = 0;
        
        // Собираем элементы диагонали
        for (int i = 0; i < n - k; i++) {
            diagonal[size++] = matrix[i][i + k];
        }
        
        printf("Диагональ %d до сортировки: ", k);
        for (int i = 0; i < size; i++) {
            printf("%d ", diagonal[i]);
        }
        
        // Сортируем по убыванию методом вставки
        insertionSortDesc(diagonal, size);
        
        printf("-> после: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", diagonal[i]);
        }
        printf("\n");
        
        // Помещаем отсортированные элементы обратно
        for (int i = 0; i < size; i++) {
            matrix[i][i + k] = diagonal[i];
        }
    }
    
    printf("\nМатрица после сортировки диагоналей:\n");
    printMatrix12_1(matrix, n);
    
    // Записываем результат в файл
    writeResultToFile12_1(matrix, n);
    
    return 0;
}

/*
Инструкции по использованию:

1. Компиляция: gcc -o variant12_task1 variant12_task1.c
2. Запуск: ./variant12_task1

Файлы:
- data.txt (входной, опциональный): первая строка - размер матрицы n, затем n строк по n чисел
- outdata.txt (выходной): результат сортировки

Пример data.txt:
4
5 8 3 2
1 9 7 4
6 2 1 8
3 5 9 2

Программа сортирует только диагонали, расположенные выше главной диагонали.
*/
