//
// Created by arugaf on 26.02.2020.
//

#ifndef TP_C_HOMEWORK_UTILS_H_1
#define TP_C_HOMEWORK_UTILS_H_1

#define INVALID_DATA -1

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix {
    long double* elements;
    size_t rows;
    size_t cols;
} Matrix;

typedef struct ElementsWithIndexes {
    long double element_value;
    size_t index;
} ElemsWithIndexes;

Matrix* CreateMatrix(size_t rows, size_t cols);
Matrix* SortMatrix(const Matrix* matrix);
void PrintMatrix(const Matrix* matrix);
int FreeMatrix(Matrix* matrix);
int FillMatrix(Matrix* matrix);
int Comparator(const void* ls, const void* rs);

#endif  // TP_C_HOMEWORK_UTILS_H_1
