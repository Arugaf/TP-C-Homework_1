#include "utils.h"

int main() {
    size_t rows = 0;
    size_t cols = 0;
    scanf("%zu %zu", &rows, &cols);

    matrix* test_matrix = create_matrix(rows, cols);
    fill_matrix(test_matrix);

    matrix* sorted_matrix = sort_matrix(test_matrix);

    print_matrix(test_matrix);
    print_matrix(sorted_matrix);

    free_matrix(test_matrix);
    free_matrix(sorted_matrix);
    return 0;
}

// Составить программу перестановки столбцов двумерной матрицы в порядке возрастания элементов первой строки.
// Матрица задана в виде одномерного линеаризованного массива (сначала в ней следуют элементы первой строки,
// затем — второй и т.д.). На выход функция должна возвращать указатель на результирующую структуру.
