#include <stdio.h>
#include <stdlib.h>

/* объявления функций ... */
int files12_1();
int files12_2();
int stack12();
int stack15();
int sort12_1();
int sort12_2();
int sort15_1();
int sort15_2();
int structs12_1();
int structs12_2();
int structs15_1();
int structs15_2();
int recurse();

void print_menu() {
  printf("\n==== Меню ====\n");
  printf("1. files12-1\n");
  printf("2. files12-2\n");
  printf("3. stack12\n");
  printf("4. stack15\n");
  printf("5. sort12-1\n");
  printf("6. sort12-2\n");
  printf("7. sort15-1\n");
  printf("8. sort15-2\n");
  printf("9. structs12-1\n");
  printf("10. structs12-2\n");
  printf("11. structs15-1\n");
  printf("12. structs15-2\n");
  printf("13. recurse\n");
  printf("0. Выход\n");
}

int main() {
  int choice;
  while (1) {
    print_menu();
    printf("Выбор: ");
    fflush(stdout); // <--- важно

    /* пробел в формате заставит scanf пропустить любые пробельные символы */
    int rc = scanf(" %d", &choice);
    if (rc == EOF) { // если stdin закрыт — выход
      printf("\nEOF on stdin, exiting\n");
      return 0;
    }
    if (rc != 1) { // некорректный ввод — очистим строку и продолжим
      printf("Некорректный ввод!\n");
      int ch;
      while ((ch = getchar()) != '\n' && ch != EOF) {
      } // очистка входного буфера
      continue;
    }

    switch (choice) {
    case 1:
      files12_1();
      break;
    case 2:
      files12_2();
      break;
    case 3:
      stack12();
      break;
    case 4:
      stack15();
      break;
    case 5:
      sort12_1();
      break;
    case 6:
      sort12_2();
      break;
    case 7:
      sort15_1();
      break;
    case 8:
      sort15_2();
      break;
    case 9:
      structs12_1();
      break;
    case 10:
      structs12_2();
      break;
    case 11:
      structs15_1();
      break;
    case 12:
      structs15_2();
      break;
    case 13:
      recurse();
      break;
    case 0:
      printf("Выход...\n");
      return 0;
    default:
      printf("Нет такого пункта!\n");
      break;
    }
  }
}
