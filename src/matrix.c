//
// Created by arugaf on 26.02.2020.
//

#include "utils.h"

matrix* create_matrix(const size_t rows, const size_t cols) {
    if (rows <= 0 || cols <= 0) {
        printf("Number of cols or rows can't be 0\n");
        return NULL;
    }

    matrix* new_matrix = (matrix*) malloc(sizeof(matrix));
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

int free_matrix(matrix* source_matrix) {
    if (!source_matrix || !source_matrix->elements) {
        printf("No matrix to free\n");
        return INVALID_DATA;
    }

    free(source_matrix->elements);
    free(source_matrix);

    return 0;
}

int fill_matrix(matrix* source_matrix) {
    if (!source_matrix || !source_matrix->elements) {
        printf("No matrix to fill with data\n");
        return INVALID_DATA;
    }

    size_t matrix_size = source_matrix->rows * source_matrix->cols;

    //char* input = NULL;
    //char* end = NULL;
    for (size_t i = 0; i < matrix_size; ++i) {
        fscanf(stdin, "%Lf", &source_matrix->elements[i]);
        /*source_matrix->elements[i] = strtold(input, &end);

        if (!source_matrix->elements[i] && (input == end)) {
            printf("Incorrect input\n");
            return INVALID_DATA;
        }

        if (input) {
            free(input);
        }*/
    }

    return 0;
}

int comparator(const void* ls, const void* rs) {
    return (((elems_with_indexes*)ls)->element_value > ((elems_with_indexes*)rs)->element_value);
}

matrix* sort_matrix(const matrix* source_matrix) {
    if (!source_matrix || !source_matrix->elements) {
        printf("No matrix to sort\n");
        return NULL;
    }

    elems_with_indexes* elements_and_indexes = malloc((sizeof(elems_with_indexes) * source_matrix->cols));

    if (!elements_and_indexes) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    for (size_t i = 0; i < source_matrix->cols; ++i) {
        elements_and_indexes[i].element_value = source_matrix->elements[i];
        elements_and_indexes[i].index = i;
    }

    qsort(elements_and_indexes, source_matrix->cols, sizeof(elems_with_indexes), comparator);

    matrix * result = create_matrix(source_matrix->rows, source_matrix->cols);

    if (!result) {
        printf("Memory allocation failed\n");
        free(elements_and_indexes);
        return NULL;
    }

    for (size_t i = 0; i < result->cols; ++i) {
        for (size_t j = 0; j < result->rows; ++j) {
            result->elements[j * result->cols + i] = source_matrix->elements[j * source_matrix->cols + elements_and_indexes[i].index];
        }
    }

    free(elements_and_indexes);

    return result;
}

void print_matrix(const matrix* source_matrix) {
    if (!source_matrix || !source_matrix->elements) {
        printf("No matrix to print\n");
        return;
    }

    for (size_t i = 0; i < source_matrix->rows; ++i) {
        for (size_t j = 0; j < source_matrix->cols; ++j) {
            printf("%Lf ", source_matrix->elements[i * source_matrix->cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}
