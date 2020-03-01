//
// Created by arugaf on 26.02.2020.
//

#include "utils.h"

Matrix* CreateMatrix(const size_t rows, const size_t cols) {
    if (rows <= 0 || cols <=0) {
        printf("Number of cols or rows can't be 0\n");
        return NULL;
    }

    Matrix* new_matrix = (Matrix*) malloc(sizeof(Matrix));
    if (!new_matrix) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_matrix->rows = rows;
    new_matrix->cols = cols;

    long double* new_elements = (long double*) calloc(rows * cols, sizeof(long double));
    if (!new_elements) {
        printf("Memory allocation failed\n");
        free(new_matrix);
        return NULL;
    }
    new_matrix->elements = new_elements;

    return new_matrix;
}

int FreeMatrix(Matrix* matrix) {
    if (!matrix || !matrix->elements) {
        printf("No matrix to free\n");
        return INVALID_DATA;
    }

    free(matrix->elements);
    free(matrix);

    return 0;
}

int FillMatrix(Matrix* matrix) {
    if (!matrix || !matrix->elements) {
        printf("No matrix to fill with data\n");
        return INVALID_DATA;
    }

    size_t matrix_size = matrix->rows * matrix->cols;

    char* input = NULL;
    char* end = NULL;
    for (size_t i = 0; i < matrix_size; ++i) {
        fscanf(stdin, "%ms", &input);
        matrix->elements[i] = strtold(input, &end);

        if (!matrix->elements[i] && (input == end)) {
            printf("Incorrect input\n");
            return INVALID_DATA;
        }

        if (input) {
            free(input);
        }
    }

    return 0;
}

int Comparator(const void* ls, const void* rs) {
    return (((ElemsWithIndexes*)ls)->element_value > ((ElemsWithIndexes*)rs)->element_value);
}

Matrix* SortMatrix(const Matrix* matrix) {
    if (!matrix || !matrix->elements) {
        printf("No matrix to sort\n");
        return NULL;
    }

    ElemsWithIndexes* elements_and_indexes = malloc((sizeof(ElemsWithIndexes) * matrix->cols));

    if (!elements_and_indexes) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    for (size_t i = 0; i < matrix->cols; ++i) {
        elements_and_indexes[i].element_value = matrix->elements[i];
        elements_and_indexes[i].index = i;
    }

    qsort(elements_and_indexes, matrix->cols, sizeof(ElemsWithIndexes), Comparator);

    Matrix* result = CreateMatrix(matrix->rows, matrix->cols);

    if (!result) {
        printf("Memory allocation failed\n");
        free(elements_and_indexes);
        return NULL;
    }

    for (size_t i = 0; i < result->cols; ++i) {
        for (size_t j = 0; j < result->rows; ++j) {
            result->elements[j * result->cols + i] = matrix->elements[j * matrix->cols + elements_and_indexes[i].index];
        }
    }

    free(elements_and_indexes);

    return result;
}

void PrintMatrix(const Matrix* matrix) {
    if (!matrix || !matrix->elements) {
        printf("No matrix to print\n");
        return;
    }

    for (size_t i = 0; i < matrix->rows; ++i) {
        for (size_t j = 0; j < matrix->cols; ++j) {
            printf("%Lf ", matrix->elements[i * matrix->cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}
