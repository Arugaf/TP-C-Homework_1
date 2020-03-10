#include "utils.h"

int main() {
    size_t rows = 0;
    size_t cols = 0;
    if (!scanf("%zu %zu", &rows, &cols)) {
        return -1;
    }

    matrix* test_matrix = NULL;
    if (create_matrix(&test_matrix, rows, cols)) {
        return -1;
    }

    if (fill_matrix(test_matrix, stdin)) {
        free_matrix(test_matrix);
        return -1;
    }

    matrix* sorted_matrix = NULL;
    if (sort_matrix(test_matrix, &sorted_matrix)) {
        return -1;
    }

    print_matrix(test_matrix, stdout);
    print_matrix(sorted_matrix, stdout);

    free_matrix(test_matrix);
    free_matrix(sorted_matrix);
    return 0;
}

// Составить программу перестановки столбцов двумерной матрицы в порядке возрастания элементов первой строки.
// Матрица задана в виде одномерного линеаризованного массива (сначала в ней следуют элементы первой строки,
// затем — второй и т.д.). На выход функция должна возвращать указатель на результирующую структуру.
