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
    Matrix* matrix = CreateMatrix(rows, cols);
    EXPECT_EQ(matrix, nullptr);
}

TEST(MatrixCreation, IncorrectCols) {
    const size_t rows = 5;
    const size_t cols = 0;
    Matrix* matrix = CreateMatrix(rows, cols);
    EXPECT_EQ(matrix, nullptr);
}

TEST(MatrixCreation, NoMemory) {
    const size_t rows = 1024;
    const size_t cols = 1024;

    rlimit rlimit_prev = {};
    getrlimit(RLIMIT_DATA, &rlimit_prev);

    const rlimit rlimit = {1, rlimit_prev.rlim_max};

    setrlimit(RLIMIT_DATA, &rlimit);

    Matrix* matrix = CreateMatrix(rows, cols);
    EXPECT_EQ(matrix, nullptr);

    setrlimit(RLIMIT_DATA, &rlimit_prev);
    getrlimit(RLIMIT_DATA, &rlimit_prev);
}

TEST(MatrixCreation, CorrectData) {
    const size_t rows = 10;
    const size_t cols = 5;
    const size_t size = rows * cols;
    Matrix* matrix = CreateMatrix(rows, cols);

    ASSERT_TRUE(matrix);
    EXPECT_EQ(matrix->cols, 5);
    EXPECT_EQ(matrix->rows, 10);

    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(matrix->elements[i], 0);
    }

    FreeMatrix(matrix);
}

TEST(MatrixFreeing, NoMatrix) {
    EXPECT_EQ(FreeMatrix(nullptr), INVALID_DATA);
}

TEST(MatrixFreeing, NoData) {
    auto matrix = (Matrix*) malloc(sizeof(Matrix));
    matrix->elements = nullptr;
    matrix->rows = 5;
    matrix->cols = 5;

    EXPECT_EQ(FreeMatrix(matrix), INVALID_DATA);

    free(matrix);
}

TEST(MatrixFreeing, CorrectData) {
    const size_t rows = 10;
    const size_t cols = 5;
    Matrix* matrix = CreateMatrix(rows, cols);

    EXPECT_EQ(FreeMatrix(matrix), 0);
}

TEST(MatrixFilling, NoMatrix) {
    EXPECT_EQ(FillMatrix(nullptr), INVALID_DATA);
}

TEST(MatrixFilling, NoData) {
    auto matrix = (Matrix*) malloc(sizeof(Matrix));
    matrix->elements = nullptr;
    matrix->rows = 5;
    matrix->cols = 5;

    EXPECT_EQ(FillMatrix(matrix), INVALID_DATA);

    free(matrix);
}

TEST(MatrixFilling, IncorrectData) {
    const size_t rows = 2;
    const size_t cols = 1;

    const char values[2] = {'a', 'b'};

    Matrix* matrix = CreateMatrix(rows, cols);

    FILE* file = fopen("test_input.txt", "w+");
    for (char value : values) {
        fprintf(file, "%c ", value);
    }

    fclose(file);

    freopen("test_input.txt", "r+", stdin);
    EXPECT_EQ(FillMatrix(matrix), INVALID_DATA);

    FreeMatrix(matrix);
}

TEST(MatrixFilling, CorrectData) {
    const size_t rows = 4;
    const size_t cols = 4;

    const long double values[16] = {5, 17, 18.2, 4.12, 9, 0, 0, 80, 9, -15.6, 13, 8, 98, 500, 700, 900.001};

    Matrix* matrix = CreateMatrix(rows, cols);

    FILE* file = fopen("test_input.txt", "w+");
    for (long double value : values) {
        fprintf(file, "%Lf ", value);
    }

    fclose(file);

    freopen("test_input.txt", "r+", stdin);
    ASSERT_EQ(FillMatrix(matrix), 0);

    for (size_t i = 0; i < 16; ++i) {
        EXPECT_LE(matrix->elements[i] - values[i], 1e-12);
    }

    FreeMatrix(matrix);
}

TEST(MatrixSorting, NoMatrix) {
    EXPECT_EQ(SortMatrix(nullptr), nullptr);
}

TEST(MatrixSorting, NoData) {
    auto matrix = (Matrix*) malloc(sizeof(Matrix));
    matrix->elements = nullptr;
    matrix->rows = 5;
    matrix->cols = 5;

    EXPECT_EQ(SortMatrix(nullptr), nullptr);

    free(matrix);
}

TEST(MatrixSorting, NoMemoryFirstString) {
    const size_t rows = 1;
    const size_t cols = 1024;
    Matrix* matrix = CreateMatrix(rows, cols);

    rlimit rlimit_prev = {};
    getrlimit(RLIMIT_DATA, &rlimit_prev);

    const rlimit rlimit = {512, rlimit_prev.rlim_max};

    setrlimit(RLIMIT_DATA, &rlimit);

    EXPECT_EQ(SortMatrix(matrix), nullptr);

    setrlimit(RLIMIT_DATA, &rlimit_prev);

    FreeMatrix(matrix);
}

TEST(MatrixSorting, NoMemoryMatrix) {
    const size_t rows = 2048;
    const size_t cols = 1;
    Matrix* matrix = CreateMatrix(rows, cols);

    rlimit rlimit_prev = {};
    getrlimit(RLIMIT_DATA, &rlimit_prev);

    const rlimit rlimit = {512, rlimit_prev.rlim_max};

    setrlimit(RLIMIT_DATA, &rlimit);

    EXPECT_EQ(SortMatrix(matrix), nullptr);

    setrlimit(RLIMIT_DATA, &rlimit_prev);

    FreeMatrix(matrix);
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

    Matrix* matrix = CreateMatrix(rows, cols);

    FILE* file = fopen("test_input.txt", "w+");
    for (long double value : values) {
        fprintf(file, "%Lf ", value);
    }

    fclose(file);

    freopen("test_input.txt", "r+", stdin);

    FillMatrix(matrix);
    Matrix* sorted_matrix = SortMatrix(matrix);

    for (size_t i = 0; i < 16; ++i) {
        EXPECT_LE(sorted_matrix->elements[i] - sorted_values[i], 1e-12);
    }

    FreeMatrix(matrix);
    FreeMatrix(sorted_matrix);
}