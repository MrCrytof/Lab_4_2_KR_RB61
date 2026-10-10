#include <time.h>
#include "funcs.h"

int** memory_allocation(int rows, int cols) {
    // Перевірка коректності вхідних розмірностей
    if (rows <= 0 || cols <= 0) return NULL;

    // Виділення пам'яті для масиву вказівників на рядки
    int **matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) return NULL;

    // Виділення пам'яті для стовпців кожного рядка
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        // Якщо виділення не вдалося, очищуємо вже виділену пам'ять
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    return matrix;
}

void clearMemory(int** matrix, int rows) {
    // Перевірка на нульовий вказівник
    if (matrix == NULL) return;

    // Послідовне звільнення пам'яті кожного рядка
    for (int i = 0; i < rows; i++) {
        if (matrix[i] != NULL) {
            free(matrix[i]);
        }
    }

    // Звільнення масиву вказівників
    free(matrix);
}

void print_matrix(int** matrix, int rows, int cols) {
    if (matrix == NULL) return;

    // Виведення матриці по рядках та стовпцях з відступами
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void fill_matrix(int** matrix, int rows, int cols, char matrix_name) {
    int choice;
    printf("Choose a matrix filling method:\n");
    printf("1. Enter values manually\n");
    printf("2. Fill with random numbers\n");
    printf("3. Fill using a formula (%c[i][j] = i + j)\n", matrix_name);
    printf("Your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    printf("Enter element [%d][%d]: ", i, j);
                    scanf("%d", &matrix[i][j]);
                }
            }
            break;

        case 2:
            srand((unsigned int)time(NULL));
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] = rand() % 20 - 10;
                }
            }
            printf("The matrix has been filled with random numbers.\n");
            break;

        case 3:
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] = i + j;
                }
            }
            printf("The matrix has been filled using the formula i + j.\n");
            break;

        default:
            printf("Invalid choice. The matrix has been filled with zeros.\n");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] = 0;
                }
            }
    }
}

void max_min(int** A, int r_a, int* max_a, int* min_a) {
    if (A == NULL || max_a == NULL || min_a == NULL || r_a < 2) {
        return;
    }

    *max_a = A[0][1];
    *min_a = A[0][1];

    for (int i = 0; i < r_a; i++) {
        for (int j = i + 1; j < r_a; j++) {
            if (A[i][j] > *max_a) {
                *max_a = A[i][j];
            }

            if (A[i][j] < *min_a) {
                *min_a = A[i][j];
            }
        }
    }
}

int** transpose(int** B, int r_b, int c_b) {
    if (B == NULL || r_b <= 0 || c_b <= 0) return NULL;

    // Виділення пам'яті під транспоновану матрицю з інвертованими розмірами (c_b x r_b)
    int** transposed = memory_allocation(c_b, r_b);
    if (transposed == NULL) return NULL;

    // Перестановка місцями рядків та стовпців
    for (int i = 0; i < c_b; i++) {
        for (int j = 0; j < r_b; j++) {
            transposed[i][j] = B[j][i];
        }
    }

    return transposed;
}

int** mult_a_b(int** A, int r_a, int c_a, int** B, int r_b, int c_b) {
    // Перевірка умови узгодженості матриць (кількість стовпців A має дорівнювати кількості рядків B)
    if (A == NULL || B == NULL || c_a != r_b || r_a <= 0 || c_a <= 0 || c_b <= 0) {
        return NULL;
    }

    // Результуюча матриця матиме розмірність r_a x c_b
    int** result = memory_allocation(r_a, c_b);
    if (result == NULL) return NULL;

    // Обчислення елементів матричного добутку за правилом суми добутків рядка на стовпець
    for (int i = 0; i < r_a; i++) {
        for (int j = 0; j < c_b; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c_a; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

void sort_matrix(int** A, int n, int mode, int row_index) {
    if (A == NULL || n <= 0) return;

    if (mode == 1) {
        // Сортування всієї матриці: копіюємо у тимчасовий лінійний масив
        int total = n * n;
        int* temp = (int*)malloc(total * sizeof(int));
        if (temp == NULL) return;

        int k = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp[k++] = A[i][j];
            }
        }

        // Сортування бульбашкою за зростанням
        for (int i = 0; i < total - 1; i++) {
            for (int j = 0; j < total - i - 1; j++) {
                if (temp[j] > temp[j + 1]) {
                    int tmp = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = tmp;
                }
            }
        }

        // Перенесення відсортованих даних назад у двовимірну матрицю
        k = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = temp[k++];
            }
        }
        free(temp);
    } else if (mode == 2) {
        // Сортування лише обраного рядка за зростанням
        if (row_index < 0 || row_index >= n) return;

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (A[row_index][j] > A[row_index][j + 1]) {
                    int tmp = A[row_index][j];
                    A[row_index][j] = A[row_index][j + 1];
                    A[row_index][j + 1] = tmp;
                }
            }
        }
    }
}

void print_sums(int** A, int r_a, int c_a, int** B, int r_b, int c_b) {
    // Обчислення та виведення суми елементів для кожного рядка матриці A
    printf("\n--- Sum of elements in each row of matrix A ---\n");
    for (int i = 0; i < r_a; i++) {
        int sum = 0;
        for (int j = 0; j < c_a; j++) {
            sum += A[i][j];
        }
        printf("Row %d: %d\n", i, sum);
    }

    // Обчислення та виведення суми елементів для кожного стовпця матриці B
    printf("\n--- Sum of elements in each column of matrix B ---\n");
    for (int j = 0; j < c_b; j++) {
        int sum = 0;
        for (int i = 0; i < r_b; i++) {
            sum += B[i][j];
        }
        printf("Column %d: %d\n", j, sum);
    }
}
