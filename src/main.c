#include "utils.h"

int main() {
    size_t rows = 0;
    size_t cols = 0;
    scanf("%zu %zu", &rows, &cols);

    Matrix* matrix = CreateMatrix(rows, cols);
    FillMatrix(matrix);

    Matrix* sorted_matrix = SortMatrix(matrix);

    PrintMatrix(matrix);
    PrintMatrix(sorted_matrix);

    FreeMatrix(matrix);
    FreeMatrix(sorted_matrix);
    return 0;
}

// Составить программу перестановки столбцов двумерной матрицы в порядке возрастания элементов первой строки.
// Матрица задана в виде одномерного линеаризованного массива (сначала в ней следуют элементы первой строки,
// затем — второй и т.д.). На выход функция должна возвращать указатель на результирующую структуру.
