//
// Created by arugaf on 01.03.2020.
//

#include <iostream>
#include "gtest/gtest.h"

#include <sys/resource.h>

extern "C" {
    #include "utils.h"
}

TEST(MatrixCreation, IncorrectRows) {
    const size_t rows = 0;
    const size_t cols = 5;
    matrix* test_matrix = nullptr;
    create_matrix(&test_matrix, rows, cols);
    EXPECT_EQ(test_matrix, nullptr);
}

TEST(MatrixCreation, IncorrectCols) {
    const size_t rows = 5;
    const size_t cols = 0;
    matrix* test_matrix = nullptr;
    create_matrix(&test_matrix, rows, cols);
    EXPECT_EQ(test_matrix, nullptr);
}

TEST(MatrixCreation, CorrectData) {
    const size_t rows = 10;
    const size_t cols = 5;
    const size_t size = rows * cols;
    matrix* test_matrix = nullptr;
    create_matrix(&test_matrix, rows, cols);

    ASSERT_TRUE(test_matrix);
    EXPECT_EQ(test_matrix->cols, 5);
    EXPECT_EQ(test_matrix->rows, 10);

    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(test_matrix->elements[i], 0);
    }

    free_matrix(test_matrix);
}

TEST(MatrixFreeing, NoMatrix) {
    EXPECT_EQ(free_matrix(nullptr), INVALID_DATA);
}

TEST(MatrixFreeing, NoData) {
    auto test_matrix = (matrix*) malloc(sizeof(matrix));
    test_matrix->elements = nullptr;
    test_matrix->rows = 5;
    test_matrix->cols = 5;

    EXPECT_EQ(free_matrix(test_matrix), INVALID_DATA);

    free(test_matrix);
}

TEST(MatrixFreeing, CorrectData) {
    const size_t rows = 10;
    const size_t cols = 5;
    matrix* test_matrix = nullptr;
    create_matrix(&test_matrix, rows, cols);

    EXPECT_EQ(free_matrix(test_matrix), 0);
}

TEST(MatrixFilling, NoMatrix) {
    EXPECT_EQ(fill_matrix(nullptr, stdin), INVALID_DATA);
}

TEST(MatrixFilling, NoData) {
    auto test_matrix = (matrix*) malloc(sizeof(matrix));
    test_matrix->elements = nullptr;
    test_matrix->rows = 5;
    test_matrix->cols = 5;

    EXPECT_EQ(fill_matrix(test_matrix, stdin), INVALID_DATA);

    free(test_matrix);
}

TEST(MatrixFilling, IncorrectData) {
    const size_t rows = 2;
    const size_t cols = 1;

    const char values[2] = {'a', 'b'};

    matrix* test_matrix = nullptr;
    create_matrix(&test_matrix, rows, cols);

    FILE* file = fopen("test_input_incorrect.txt", "w+");
    for (char value : values) {
        fprintf(file, "%c ", value);
    }
    fclose(file);
    file = fopen("test_input_incorrect.txt", "r");

    EXPECT_EQ(fill_matrix(test_matrix, file), INVALID_DATA);

    free_matrix(test_matrix);
    fclose(file);
}

TEST(MatrixFilling, CorrectData) {
    const size_t rows = 4;
    const size_t cols = 4;

    const long double values[16] = {5, 17, 18.2, 4.12,
                                    9, 0, 0, 80,
                                    9, -15.6, 13, 8,
                                    98, 500, 700, 900.001};

    matrix* test_matrix = nullptr;
    create_matrix(&test_matrix, rows, cols);

    FILE* file = fopen("test_input_correct.txt", "w+");
    for (long double value : values) {
        fprintf(file, "%Lf ", value);
    }
    fclose(file);
    file = fopen("test_input_correct.txt", "r");

    ASSERT_EQ(fill_matrix(test_matrix, file), 0);

    for (size_t i = 0; i < 16; ++i) {
        EXPECT_LE(test_matrix->elements[i] - values[i], 1e-12);
    }

    free_matrix(test_matrix);
    fclose(file);
}

TEST(MatrixSorting, NoMatrix) {
    EXPECT_EQ(sort_matrix(nullptr, nullptr), INVALID_DATA);
}

TEST(MatrixSorting, NoData) {
    auto test_matrix = (matrix*) malloc(sizeof(matrix));
    test_matrix->elements = nullptr;
    test_matrix->rows = 5;
    test_matrix->cols = 5;

    EXPECT_EQ(sort_matrix(nullptr, nullptr), INVALID_DATA);

    free(test_matrix);
}

TEST(MatrixSorting, CorrectData) {
    const size_t rows = 4;
    const size_t cols = 4;

    const long double values[16] = {5, 17, 18.2, 4.12,
                                    9, 0, 0, 80,
                                    9, -15.6, 13, 8,
                                    98, 500, 700, 900.001};
    const long double sorted_values[16] = {4.12, 5, 17, 18.2,
                                           80, 9, 0, 0,
                                           8, 9, -15.6, 13,
                                           900.001, 98, 500, 700};

    matrix* test_matrix = nullptr;
    create_matrix(&test_matrix, rows, cols);

    FILE* file = fopen("test_input_sorted.txt", "w+");
    for (long double value : values) {
        fprintf(file, "%Lf ", value);
    }
    fclose(file);
    file = fopen("test_input_sorted.txt", "r");

    fill_matrix(test_matrix, file);
    matrix* sorted_matrix = nullptr;
    sort_matrix(test_matrix, &sorted_matrix);

    for (size_t i = 0; i < 16; ++i) {
        EXPECT_LE(sorted_matrix->elements[i] - sorted_values[i], 1e-12);
    }

    free_matrix(test_matrix);
    free_matrix(sorted_matrix);
    fclose(file);
}
