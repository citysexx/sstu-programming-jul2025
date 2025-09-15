#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Структура для рационального числа
typedef struct {
    int numerator;   // ЧИСЛИТЕЛЬ
    int denominator; // ЗНАМЕНАТЕЛЬ
} RATIONAL;

// Функция нахождения НОД (наибольший общий делитель)
int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция сокращения дроби
RATIONAL reduce(RATIONAL r) {
    int g = gcd(r.numerator, r.denominator);
    r.numerator /= g;
    r.denominator /= g;
    
    // Если знаменатель отрицательный, переносим знак в числитель
    if (r.denominator < 0) {
        r.numerator = -r.numerator;
        r.denominator = -r.denominator;
    }
    
    return r;
}

// Функция ввода рационального числа
void inputRational(RATIONAL *r) {
    printf("Введите числитель: ");
    scanf("%d", &r->numerator);
    do {
        printf("Введите знаменатель (не 0): ");
        scanf("%d", &r->denominator);
        if (r->denominator == 0) {
            printf("Знаменатель не может быть равен 0!\n");
        }
    } while (r->denominator == 0);
}

// Функция вывода рационального числа
void printRational(RATIONAL r) {
    if (r.denominator == 1) {
        printf("%d", r.numerator);
    } else {
        printf("%d/%d", r.numerator, r.denominator);
    }
}

// Функция поиска в массиве X[N] рациональных чисел всех чисел, равных заданному
void findEqual(RATIONAL arr[], int n, RATIONAL target) {
    printf("Поиск чисел, равных ");
    printRational(target);
    printf(":\n");
    
    RATIONAL targetReduced = reduce(target);
    int found = 0;
    
    for (int i = 0; i < n; i++) {
        RATIONAL currentReduced = reduce(arr[i]);
        // Сравниваем сокращенные дроби
        if (currentReduced.numerator == targetReduced.numerator && 
            currentReduced.denominator == targetReduced.denominator) {
            printf("  Найдено на позиции %d: ", i + 1);
            printRational(arr[i]);
            printf("\n");
            found++;
        }
    }
    
    if (found == 0) {
        printf("  Равных чисел не найдено.\n");
    } else {
        printf("  Всего найдено: %d\n", found);
    }
}

// Функция подсчета количества чисел с заданным знаменателем
int countWithDenominator(RATIONAL arr[], int n, int targetDenom) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        RATIONAL reduced = reduce(arr[i]);
        if (reduced.denominator == targetDenom) {
            count++;
        }
    }
    return count;
}

// Функция загрузки чисел из файла
int loadFromFile(RATIONAL arr[], int maxCount) {
    FILE *file = fopen("rationals.txt", "r");
    if (file == NULL) {
        return 0;
    }
    
    int count = 0;
    while (count < maxCount && 
           fscanf(file, "%d %d", &arr[count].numerator, &arr[count].denominator) == 2) {
        if (arr[count].denominator != 0) {
            count++;
        }
    }
    
    fclose(file);
    return count;
}

// Функция сохранения чисел в файл
void saveToFile(RATIONAL arr[], int count) {
    FILE *file = fopen("rationals.txt", "w");
    if (file == NULL) {
        printf("Ошибка создания файла!\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %d\n", arr[i].numerator, arr[i].denominator);
    }
    
    fclose(file);
    printf("Данные сохранены в файл rationals.txt\n");
}

// Главное меню
void showMenu15_1() {
    printf("\n========== МЕНЮ РАБОТЫ С РАЦИОНАЛЬНЫМИ ЧИСЛАМИ ==========\n");
    printf("1. Ввод нового рационального числа\n");
    printf("2. Вывод всех чисел на экран\n");
    printf("3. Поиск чисел, равных заданному\n");
    printf("4. Подсчет чисел с заданным знаменателем\n");
    printf("5. Примеры дробей (2/4, 4/8 равны 1/2)\n");
    printf("6. Загрузить числа из файла\n");
    printf("7. Сохранить числа в файл\n");
    printf("0. Выход\n");
    printf("Выберите пункт: ");
}

// Функция создания примеров дробей
void createExamples(RATIONAL arr[], int *count) {
    // Добавляем примеры дробей, равных 1/2
    arr[*count].numerator = 1; arr[*count].denominator = 2; (*count)++;
    arr[*count].numerator = 2; arr[*count].denominator = 4; (*count)++;
    arr[*count].numerator = 4; arr[*count].denominator = 8; (*count)++;
    
    // Добавляем примеры дробей, равных 2/3
    arr[*count].numerator = 2; arr[*count].denominator = 3; (*count)++;
    arr[*count].numerator = 4; arr[*count].denominator = 6; (*count)++;
    
    // Добавляем другие дроби
    arr[*count].numerator = 3; arr[*count].denominator = 4; (*count)++;
    arr[*count].numerator = 5; arr[*count].denominator = 7; (*count)++;
    arr[*count].numerator = -1; arr[*count].denominator = 2; (*count)++;
    
    printf("Добавлено 8 примеров рациональных чисел.\n");
}

int structs15_1() {
    RATIONAL numbers[100];
    int count = 0;
    int choice;
    
    // Попытка автоматической загрузки из файла
    count = loadFromFile(numbers, 100);
    if (count > 0) {
        printf("Загружено %d рациональных чисел из файла rationals.txt\n", count);
    }
    
    do {
        showMenu15_1();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // Ввод нового числа
                if (count >= 100) {
                    printf("Массив заполнен!\n");
                } else {
                    printf("\n--- Ввод рационального числа ---\n");
                    inputRational(&numbers[count]);
                    printf("Добавлено число: ");
                    printRational(numbers[count]);
                    printf(" (сокращенная форма: ");
                    printRational(reduce(numbers[count]));
                    printf(")\n");
                    count++;
                }
                break;
            
            case 2: // Вывод всех чисел
                if (count == 0) {
                    printf("Массив пуст!\n");
                } else {
                    printf("\n--- Список рациональных чисел ---\n");
                    for (int i = 0; i < count; i++) {
                        printf("%d. ", i + 1);
                        printRational(numbers[i]);
                        printf(" = ");
                        printRational(reduce(numbers[i]));
                        printf("\n");
                    }
                    printf("Всего чисел: %d\n", count);
                }
                break;
            
            case 3: // Поиск равных заданному
                if (count == 0) {
                    printf("Массив пуст!\n");
                } else {
                    printf("\n--- Поиск равных чисел ---\n");
                    RATIONAL target;
                    inputRational(&target);
                    findEqual(numbers, count, target);
                }
                break;
            
            case 4: // Подсчет с заданным знаменателем
                if (count == 0) {
                    printf("Массив пуст!\n");
                } else {
                    printf("\n--- Подсчет чисел с заданным знаменателем ---\n");
                    printf("После сокращения дробей!\n");
                    printf("Введите знаменатель: ");
                    int denom;
                    scanf("%d", &denom);
                    if (denom == 0) {
                        printf("Знаменатель не может быть 0!\n");
                    } else {
                        int cnt = countWithDenominator(numbers, count, abs(denom));
                        printf("Количество дробей со знаменателем %d: %d\n", abs(denom), cnt);
                        
                        // Показываем найденные дроби
                        if (cnt > 0) {
                            printf("Это дроби:\n");
                            for (int i = 0; i < count; i++) {
                                RATIONAL reduced = reduce(numbers[i]);
                                if (reduced.denominator == abs(denom)) {
                                    printf("  ");
                                    printRational(numbers[i]);
                                    printf(" = ");
                                    printRational(reduced);
                                    printf("\n");
                                }
                            }
                        }
                    }
                }
                break;
            
            case 5: // Создание примеров
                if (count + 8 > 100) {
                    printf("Недостаточно места для добавления примеров!\n");
                } else {
                    createExamples(numbers, &count);
                }
                break;
            
            case 6: // Загрузка из файла
                printf("\n--- Загрузка из файла ---\n");
                count = loadFromFile(numbers, 100);
                if (count > 0) {
                    printf("Загружено %d чисел.\n", count);
                } else {
                    printf("Файл пуст или не найден.\n");
                }
                break;
            
            case 7: // Сохранение в файл
                if (count == 0) {
                    printf("Нет данных для сохранения!\n");
                } else {
                    saveToFile(numbers, count);
                }
                break;
            
            case 0:
                printf("Выход из программы...\n");
                break;
            
            default:
                printf("Неверный выбор!\n");
        }
    } while (choice != 0);
    
    return 0;
}
