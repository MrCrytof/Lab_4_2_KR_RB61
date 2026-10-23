#include <stdio.h>
#include <windows.h>
#include "funcs.h"

int main() {
    int rows_A = 7; // Задаємо розмірність для варіанта 7 (квадратна матриця 7x7)
    int cols_A = 7;
    int rows_B = 7; // Кількість рядків B дорівнює кількості рядків A для множення
    int cols_B = 0;

    printf("Your variant: 7. Matrix A dimensions: %d x %d\n", rows_A, cols_A);
    printf("Enter the number of columns for rectangular matrix B: ");

    scanf("%d", &cols_B);

    // Виділення динамічної пам'яті під матриці A та B
    int** arr_A = memory_allocation(rows_A, cols_A);
    int** arr_B = memory_allocation(rows_B, cols_B);

    // Перевірка успішності виділення пам'яті
    if (arr_A == NULL || arr_B == NULL) {
        printf("\nMemory allocation error!\n");
        clearMemory(arr_A, rows_A);
        clearMemory(arr_B, rows_B);
        return 1;
    }

    // Ініціалізація та заповнення матриці A за вибором користувача
    printf("\n=== Filling matrix A ===\n");
    fill_matrix(arr_A, rows_A, cols_A, 'A');

    // Ініціалізація та заповнення матриці B за вибором користувача
    printf("\n=== Filling matrix B ===\n");
    fill_matrix(arr_B, rows_B, cols_B,'B');

    // Очищення екрана перед запуском головного меню
    printf("\n");
    // Головний цикл інтерактивного текстового інтерфейсу
    while (1) {
        int choice = 0;
        printf("\n================ MATRIX OPERATIONS ================\n");
        printf("1. Display current matrices A and B\n");
        printf("2. Find the maximum of matrix A and the minimum above the main diagonal\n");
        printf("3. Transpose matrix B\n");
        printf("4. Matrix multiplication A * B\n");
        printf("5. Sort matrix A (entire matrix or a single row)\n");
        printf("6. Display row sums of A and column sums of B\n");
        printf("0. Exit and free memory\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Виведення матриць
                printf("\nMatrix A (%dx%d):\n", rows_A, cols_A);
                print_matrix(arr_A, rows_A, cols_A);
                printf("\nMatrix B (%dx%d):\n", rows_B, cols_B);
                print_matrix(arr_B, rows_B, cols_B);
                break;

            case 2: { // Пошук макс. і мін. елементів
                int max = 0, min = 0;
                max_min(arr_A, rows_A, &max, &min);
                printf("\nMaximum element of matrix A: %d\n", max);
                printf("Minimum element above the main diagonal: %d\n", min);
                break;
            }

            case 3: { // Транспонування матриці B
                printf("\nTransposed matrix B (%dx%d):\n", cols_B, rows_B);
                int** transposed_B = transpose(arr_B, rows_B, cols_B);
                if (transposed_B != NULL) {
                    print_matrix(transposed_B, cols_B, rows_B);
                    clearMemory(transposed_B, cols_B); // Звільнення тимчасової пам'яті
                }
                break;
            }

            case 4: { // Множення матриць A * B
                int** ab = mult_a_b(arr_A, rows_A, cols_A, arr_B, rows_B, cols_B);
                if (ab == NULL) {
                    printf("\nError: Matrix multiplication A * B is not possible (cols_A != rows_B)!\n");
                } else {
                    printf("\nResult of A * B multiplication (%dx%d):\n", rows_A, cols_B);
                    print_matrix(ab, rows_A, cols_B);
                    clearMemory(ab, rows_A); // Звільнення тимчасової пам'яті
                }
                break;
            }

            case 5: { // Сортування матриці або рядка
                int mode, row_idx = 0;
                printf("Sorting mode:\n1. Entire matrix A\n2. A single row of matrix A\nChoice: ");
                scanf("%d", &mode);
                if (mode != 1 && mode != 2) {
                    printf("Invalid sorting mode!\n");
                    break;
                }
                if (mode == 2) {
                    printf("Enter row index (0 - %d): ", rows_A - 1);
                    scanf("%d", &row_idx);
                }
                sort_matrix(arr_A, rows_A, mode, row_idx);
                printf("\nMatrix A after sorting:\n");
                print_matrix(arr_A, rows_A, cols_A);
                break;
            }

            case 6: // Виведення сум рядків A та стовпців B
                print_sums(arr_A, rows_A, cols_A, arr_B, rows_B, cols_B);
                break;

            case 0: // Завершення роботи програми та очищення динамічної пам'яті
                clearMemory(arr_A, rows_A);
                clearMemory(arr_B, rows_B);
                printf("\nMemory successfully freed. Program terminated.\n");
                return 0;

            default:
                printf("\nInvalid operation choice!\n");
                break;
        }
    }

    return 0;
}