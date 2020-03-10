//
// Created by arugaf on 26.02.2020.
//

#include "utils.h"

int create_matrix(matrix** dest, const size_t rows, const size_t cols) {
    if (rows <= 0 || cols <= 0) {
        return INVALID_DATA;
    }

    *dest = (matrix*) malloc(sizeof(matrix));
    if (!(*dest)) {
        return ALLOCATION_FAILED;
    }
    (*dest)->rows = rows;
    (*dest)->cols = cols;

    double* new_elements = (double*) calloc(rows * cols, sizeof(double));
    if (!new_elements) {
        free(dest);
        return ALLOCATION_FAILED;
    }
    (*dest)->elements = new_elements;

    return 0;
}

int free_matrix(matrix* source_matrix) {
    if (!source_matrix || !source_matrix->elements) {
        return INVALID_DATA;
    }

    free(source_matrix->elements);
    free(source_matrix);

    return 0;
}

int fill_matrix(matrix* source_matrix, FILE* input) {
    if (!input) {
        return INVALID_STREAM;
    }

    if (!source_matrix || !source_matrix->elements) {
        return INVALID_DATA;
    }

    size_t matrix_size = source_matrix->rows * source_matrix->cols;

    short invalid_data_flag = 0;
    for (size_t i = 0; i < matrix_size; ++i) {
        if (!fscanf(input, "%lf", &source_matrix->elements[i])) {
            invalid_data_flag = 1;
        }
    }

    if (invalid_data_flag) {
        return INVALID_DATA;
    }

    return 0;
}

int comparator(const void* ls, const void* rs) {
    return (((elems_with_indexes*)ls)->element_value > ((elems_with_indexes*)rs)->element_value);
}

static void calculate_indexes(elems_with_indexes** array_to_fill, const matrix* source_matrix) {
    for (size_t i = 0; i < source_matrix->cols; ++i) {
        (*array_to_fill)[i].element_value = source_matrix->elements[i];
        (*array_to_fill)[i].index = i;
    }
}

static void mix_values(elems_with_indexes* array_with_indexes, const matrix* source_matrix, matrix** dest) {
    for (size_t i = 0; i < (*dest)->cols; ++i) {
        for (size_t j = 0; j < (*dest)->rows; ++j) {
            (*dest)->elements[j * (*dest)->cols + i] = source_matrix->elements[j * source_matrix->cols + array_with_indexes[i].index];
        }
    }
}

int sort_matrix(const matrix* source_matrix, matrix** dest) {
    if (!source_matrix || !source_matrix->elements) {
        return INVALID_DATA;
    }

    elems_with_indexes* elements_and_indexes = malloc((sizeof(elems_with_indexes) * source_matrix->cols));

    if (!elements_and_indexes) {
        return ALLOCATION_FAILED;
    }

    calculate_indexes(&elements_and_indexes, source_matrix);

    qsort(elements_and_indexes, source_matrix->cols, sizeof(elems_with_indexes), comparator);

    if (create_matrix(dest, source_matrix->rows, source_matrix->cols)) {
        free(elements_and_indexes);
        return ALLOCATION_FAILED;
    }

    mix_values(elements_and_indexes, source_matrix, dest);

    free(elements_and_indexes);

    return 0;
}

void print_matrix(const matrix* source_matrix, FILE* output) {
    if (!output) {
        return;
    }

    if (!source_matrix || !source_matrix->elements) {
        return;
    }

    for (size_t i = 0; i < source_matrix->rows; ++i) {
        for (size_t j = 0; j < source_matrix->cols; ++j) {
            fprintf(output, "%lf ", source_matrix->elements[i * source_matrix->cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}
