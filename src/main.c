#include "utils.h"

static int comparator(const void* ls, const void* rs) {
    if ((!ls && !rs) || !ls) {
        return 1;
    } else if (!rs) {
        return 0;
    }
    return (((elems_with_indexes*)ls)->element_value < ((elems_with_indexes*)rs)->element_value);
}

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
    if (sort_matrix(test_matrix, &sorted_matrix, comparator)) {
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
