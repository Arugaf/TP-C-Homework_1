//
// Created by arugaf on 26.02.2020.
//

#ifndef TP_C_HOMEWORK_UTILS_H_1
#define TP_C_HOMEWORK_UTILS_H_1

#define INVALID_DATA -1
#define ALLOCATION_FAILED -2
#define INVALID_STREAM -3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix {
    double* elements;
    size_t rows;
    size_t cols;
} matrix;

typedef struct ElementsWithIndexes {
    double element_value;
    size_t index;
} elems_with_indexes;

int create_matrix(matrix** dest, const size_t rows, const size_t cols);
int sort_matrix(const matrix* source_matrix, matrix** dest, int (*compar)(const void*, const void*));
void print_matrix(const matrix* source_matrix, FILE* output);
int free_matrix(matrix* source_matrix);
int fill_matrix(matrix* source_matrix, FILE* input);

#endif  // TP_C_HOMEWORK_UTILS_H_1
