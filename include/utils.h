//
// Created by arugaf on 26.02.2020.
//

#ifndef TP_C_HOMEWORK_UTILS_H_1
#define TP_C_HOMEWORK_UTILS_H_1

#define INVALID_DATA -1

#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {
    long double* elements;
    size_t rows;
    size_t cols;
} matrix;

typedef struct ElementsWithIndexes {
    long double element_value;
    size_t index;
} elems_with_indexes;

matrix* create_matrix(size_t rows, size_t cols);
matrix* sort_matrix(const matrix* source_matrix);
void print_matrix(const matrix* source_matrix);
int free_matrix(matrix* source_matrix);
int fill_matrix(matrix* source_matrix);
int comparator(const void* ls, const void* rs);

#endif  // TP_C_HOMEWORK_UTILS_H_1
