
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "hw1.h"

/*
TEST(HW1Test, ZEROS) {
    Matrix matrix{algebra::zeros(5, 6)};

    // check the size of the matrix
    EXPECT_EQ(matrix.size(), 5);
    EXPECT_EQ(matrix[0].size(), 6);

    // check the value of the elements
    for (const auto& row : matrix)
        for (const auto& elem : row)
            EXPECT_DOUBLE_EQ(elem, 0);
}

TEST(HW1Test, ONES) {
    Matrix matrix{algebra::ones(7, 3)};

    // check the size of the matrix
    EXPECT_EQ(matrix.size(), 7);
    EXPECT_EQ(matrix[0].size(), 3);

    // check the value of the elements
    for (const auto& row : matrix)
        for (const auto& elem : row)
            EXPECT_DOUBLE_EQ(elem, 1);
}

TEST(HW1Test, RANDOM1) {
    using ::testing::AllOf;
    using ::testing::Ge;
    using ::testing::Lt;

    Matrix matrix{algebra::random(4, 4, -5, 7)};

    // check the size of the matrix
    EXPECT_EQ(matrix.size(), 4);
    EXPECT_EQ(matrix[0].size(), 4);

    // check the value of the elements
    for (const auto& row : matrix)
        for (const auto& elem : row)
            EXPECT_THAT(elem, AllOf(Ge(-5.0), Lt(7)));

    // show the matrix to test algebra::show function
    std::cout << "random matrix [-5, 7)" << std::endl;
    algebra::show(matrix);
    std::cout << std::endl;
}

TEST(HW1Test, RANDOM2) {
    // Caution: min cannot be greater than max
    EXPECT_THROW(algebra::random(3, 4, 4, 2), std::logic_error);
}

TEST(HW1Test, MULTIPLY1) {
    Matrix matrix{algebra::random(3, 4, -4, 2)};
    Matrix mult{algebra::multiply(matrix, 3.5)};

    // check the size of the matrix
    EXPECT_EQ(mult.size(), 3);
    EXPECT_EQ(mult[0].size(), 4);

    // check the value of the elements
    for (size_t i{}; i < mult.size(); i++)
        for (size_t j{}; j < mult[i].size(); j++)
            EXPECT_NEAR(mult[i][j], matrix[i][j]*3.5, 0.03);
}

TEST(HW1Test, MULTIPLY2) {
    // Caution: multiplication of 2 empty matrix
    Matrix matrix{algebra::multiply(Matrix{}, Matrix{})};
    EXPECT_TRUE(matrix.empty());

    // Caution: matrices with wrong dimensions cannot be multiplied
    EXPECT_THROW(algebra::multiply(Matrix{{1, 2, 3}, {4, 5, 6}}, Matrix{{1, 2, 3}, {4, 5, 6}}), std::logic_error);
}

TEST(HW1Test, MULTIPLY3) {
    Matrix matrix1{{-3, 3, 1.7}, {4, -4, 2.6}, {-5, 5, 3.5}};
    Matrix matrix2{{2.5}, {-2}, {-5.5}};
    Matrix matrix{algebra::multiply(matrix1, matrix2)};

    // check the size of the matrix
    EXPECT_EQ(matrix.size(), 3);
    EXPECT_EQ(matrix[0].size(), 1);

    // check the value of the elements
    EXPECT_NEAR(matrix[0][0], -22.85, 0.03);
    EXPECT_NEAR(matrix[1][0], 3.7, 0.03);
    EXPECT_NEAR(matrix[2][0], -41.75, 0.03);
}

TEST(HW1Test, MULTIPLY4) {
    Matrix matrix1{{-3, 2, 1.7}, {4, -5, 2.6}, {7.2, 5, 3.5}};
    Matrix matrix2{{6.5}, {-2}, {-5}};
    Matrix matrix{algebra::multiply(matrix1, matrix2)};

    // check the size of the matrix
    EXPECT_EQ(matrix.size(), 3);
    EXPECT_EQ(matrix[0].size(), 1);

    // check the value of the elements
    EXPECT_NEAR(matrix[0][0], -32, 0.03);
    EXPECT_NEAR(matrix[1][0], 23, 0.03);
    EXPECT_NEAR(matrix[2][0], 19.3, 0.03);
}

TEST(HW1Test, SUM1) {
    // Caution: sum of an empty matrix
    EXPECT_TRUE(algebra::sum(Matrix{}, 1.5).empty());

    Matrix matrix{algebra::random(2, 5, 0, 4)};
    Matrix sum{algebra::sum(matrix, 2.44)};

    // check the size of the matrix
    EXPECT_EQ(sum.size(), 2);
    EXPECT_EQ(sum[0].size(), 5);

    // check the value of the elements
    for (size_t i{}; i < sum.size(); i++)
        for (size_t j{}; j < sum[i].size(); j++)
            EXPECT_NEAR(sum[i][j], matrix[i][j]+2.44, 0.03);
}

TEST(HW1Test, SUM2) {
    // Caution: sum of 2 empty matrices
    EXPECT_TRUE(algebra::sum(Matrix{}, Matrix{}).empty());

    // Caution: matrices with wrong dimensions cannot be summed
    EXPECT_THROW(algebra::sum(Matrix{{1, 2, 3}}, Matrix{}), std::logic_error);

    Matrix matrix1{algebra::random(3, 2, -1, 4)};
    Matrix matrix2{algebra::random(3, 2, -8, -3)};
    Matrix sum{algebra::sum(matrix1, matrix2)};

    // check the size of the matrix
    EXPECT_EQ(sum.size(), 3);
    EXPECT_EQ(sum[0].size(), 2);

    // check the value of the elements
    for (size_t i{}; i < sum.size(); i++)
        for (size_t j{}; j < sum[i].size(); j++)
            EXPECT_NEAR(sum[i][j], matrix1[i][j]+matrix2[i][j], 0.03);
}

TEST(HW1Test, TRANSPOSE) {
    // Caution: transpose of an empty matrix is an empty matrix
    EXPECT_TRUE(algebra::transpose(Matrix{}).empty());

    Matrix matrix{algebra::random(3, 5, -2, 5)};
    Matrix transpose = algebra::transpose(matrix);

    // check the size of the matrix
    EXPECT_EQ(transpose.size(), 5);
    EXPECT_EQ(transpose[0].size(), 3);

    // check the value of the elements
    for (size_t i{}; i < transpose.size(); i++)
        for (size_t j{}; j < transpose[i].size(); j++)
            EXPECT_DOUBLE_EQ(transpose[i][j], matrix[j][i]);
}

TEST(HW1Test, MINOR1) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix minor = algebra::minor(matrix, 1, 2);

    // check the size of the matrix
    EXPECT_EQ(minor.size(), 2);
    EXPECT_EQ(minor[0].size(), 2);

    // check the value of the elements
    EXPECT_DOUBLE_EQ(minor[0][0], matrix[0][0]);
    EXPECT_DOUBLE_EQ(minor[0][1], matrix[0][1]);
    EXPECT_DOUBLE_EQ(minor[1][0], matrix[2][0]);
    EXPECT_DOUBLE_EQ(minor[1][1], matrix[2][1]);
}

TEST(HW1Test, MINOR2) {
    Matrix matrix{{7, 2.5, 3.1}, {4.2, 5, 10.4}, {70.7, 8, 0}};
    Matrix minor = algebra::minor(matrix, 1, 1);

    // check the size of the matrix
    EXPECT_EQ(minor.size(), 2);
    EXPECT_EQ(minor[0].size(), 2);

    // check the value of the elements
    EXPECT_DOUBLE_EQ(minor[0][0], matrix[0][0]);
    EXPECT_DOUBLE_EQ(minor[0][1], matrix[0][2]);
    EXPECT_DOUBLE_EQ(minor[1][0], matrix[2][0]);
    EXPECT_DOUBLE_EQ(minor[1][1], matrix[2][2]);
}

TEST(HW1Test, DETERMINANT1) {
    // Caution: determinant of an empty matrix
    EXPECT_EQ(algebra::determinant(Matrix{}), 1);

    // Caution: non-square matrices have no determinant
    EXPECT_THROW(algebra::determinant(Matrix{{1, 2, 3}, {4, 5, 6}}), std::logic_error);

    // test case
    Matrix matrix{{-1, 1.5, -1.75, -2}, {-2, 2.5, -2.75, -3}, {3, 3.5, -3.75, -4}, {4, 4.5, 4.75, -5}};
    EXPECT_NEAR(algebra::determinant(matrix), -28.5, 0.03);
}

TEST(HW1Test, DETERMINANT2) {
    // test case
    Matrix matrix{{1, 1.5, -1.75, 2}, {2, 2.5, -2.75, 3}, {3, 3.5, -3.75, 4}, {4, 4.5, 4.75, 5}};
    EXPECT_DOUBLE_EQ(algebra::determinant(matrix), 0);
}

TEST(HW1Test, INVERSE1) {
    // Caution: inverse of an empty matrix
    EXPECT_TRUE(algebra::inverse(Matrix{}).empty());

    // Caution: non-square matrices have no inverse
    EXPECT_THROW(algebra::inverse(Matrix{{1, 2, 3}, {40, 5, -6}}), std::logic_error);

    // Caution: singular matrices have no inverse
    Matrix non_singular_matrix{{1, 1.5, -1.75, 2}, {2, 2.5, -2.75, 3}, {3, 3.5, -3.75, 4}, {4, 4.5, 4.75, 5}};
    EXPECT_THROW(algebra::inverse(non_singular_matrix), std::logic_error);

    // test case
    Matrix matrix{{-1, 1.5, -1.75, -2}, {-2, 2.5, -2.75, -3}, {3, 3.5, -3.75, -4}, {4, 4.5, 4.75, -5}};
    Matrix inverse{algebra::inverse(matrix)};
    EXPECT_NEAR(inverse[0][0], 0.16, 0.03);
    EXPECT_NEAR(inverse[1][1], 3.31, 0.03);
    EXPECT_NEAR(inverse[3][1], 2.67, 0.03);
    EXPECT_NEAR(inverse[0][3], 0, 0.03);
}


TEST(HW1Test, INVERSE2) {
    // test case
    Matrix matrix{{-12, 1.5, -1.75, -2}, {-2, 2.5, -2.75, -3}, {25, 3.5, -3.75, -4}, {4, 4.5, 4.75, -51}};
    Matrix inverse{algebra::inverse(matrix)};
    EXPECT_NEAR(inverse[0][0], 0.05, 0.03);
    EXPECT_NEAR(inverse[1][1], 18.07, 0.03);
    EXPECT_NEAR(inverse[3][1], 2.80, 0.03);
    EXPECT_NEAR(inverse[0][3], 0, 0.03);
}

TEST(HW1Test, CONCATENATE1) {
    // Caution: matrices with wrong dimensions cannot be concatenated
    EXPECT_THROW(algebra::concatenate(Matrix{{1, 2}}, Matrix{{1, 2, 3}, {4, 5, 6}}, 0), std::logic_error);

    // test case
    Matrix matrix1{algebra::random(2, 3, 0, 1)};
    Matrix matrix2{algebra::random(4, 3, 0, 1)};
    Matrix matrix{algebra::concatenate(matrix1, matrix2, 0)};

    // check the size of the matrix
    EXPECT_EQ(matrix.size(), 6);
    EXPECT_EQ(matrix[0].size(), 3);

    // check the value of the elements
    EXPECT_DOUBLE_EQ(matrix[0][0], matrix1[0][0]);
    EXPECT_DOUBLE_EQ(matrix[1][2], matrix1[1][2]);
    EXPECT_DOUBLE_EQ(matrix[2][0], matrix2[0][0]);
    EXPECT_DOUBLE_EQ(matrix[5][2], matrix2[3][2]);

}

TEST(HW1Test, CONCATENATE2) {
    // Caution: matrices with wrong dimensions cannot be concatenated
    EXPECT_THROW(algebra::concatenate(Matrix{{1, 2}}, Matrix{{1, 2, 3}, {4, 5, 6}}, 1), std::logic_error);

    // test case
    Matrix matrix1{algebra::random(2, 3, 0, 1)};
    Matrix matrix2{algebra::random(2, 1, 0, 1)};
    Matrix matrix{algebra::concatenate(matrix1, matrix2, 1)};

    // check the size of the matrix
    EXPECT_EQ(matrix.size(), 2);
    EXPECT_EQ(matrix[0].size(), 4);

    // check the value of the elements
    EXPECT_DOUBLE_EQ(matrix[0][0], matrix1[0][0]);
    EXPECT_DOUBLE_EQ(matrix[1][2], matrix1[1][2]);
    EXPECT_DOUBLE_EQ(matrix[0][3], matrix2[0][0]);
    EXPECT_DOUBLE_EQ(matrix[1][3], matrix2[1][0]);
}

TEST(HW1Test, ERO_SWAP) {
    // Caution: r1 or r2 inputs are out of range
    EXPECT_THROW(algebra::ero_swap(Matrix{{1, 2}}, 0, 1), std::logic_error);

    // test case
    Matrix matrix{algebra::random(4, 3, 0, 4)};
    Matrix swap{algebra::ero_swap(matrix, 2, 3)};

    // check the swap
    EXPECT_TRUE(swap[0] == matrix[0]);
    EXPECT_TRUE(swap[1] == matrix[1]);
    EXPECT_TRUE(swap[2] == matrix[3]);
    EXPECT_TRUE(swap[3] == matrix[2]);
}

TEST(HW1Test, ERO_MULTIPLY) {
    Matrix matrix{algebra::random(4, 3, 0, 4)};
    Matrix ero{algebra::ero_multiply(matrix, 2, 1.5)};

    EXPECT_TRUE(ero[0] == matrix[0]);
    EXPECT_TRUE(ero[1] == matrix[1]);
    EXPECT_TRUE(ero[3] == matrix[3]);

    // check the value of the elements
    for (size_t i{}; i < ero[2].size(); i++)
        EXPECT_NEAR(ero[2][i], matrix[2][i]*1.5, 0.03);
}

TEST(HW1Test, ERO_SUM) {
    Matrix matrix{algebra::random(4, 3, 0, 4)};
    Matrix ero{algebra::ero_sum(matrix, 0, 2, 3)};

    EXPECT_TRUE(ero[0] == matrix[0]);
    EXPECT_TRUE(ero[1] == matrix[1]);
    EXPECT_TRUE(ero[2] == matrix[2]);

    // check the value of the elements
    for (size_t i{}; i < ero[3].size(); i++)
        EXPECT_NEAR(ero[3][i], matrix[0][i]*2+matrix[3][i], 0.03);
}

TEST(HW1Test, UPPER_TRIANGULAR1) {
    // Caution: empty matrix
    EXPECT_TRUE(algebra::upper_triangular(Matrix{}).empty());

    // Caution: non-square matrices have no upper triangular form
    EXPECT_THROW(algebra::upper_triangular(Matrix{{1, 2, 3}, {4, 5, 6}}), std::logic_error);

    // test case 1
    Matrix matrix1{{1, 2}, {5, 7}};
    Matrix res1{algebra::upper_triangular(matrix1)};
    EXPECT_NEAR(res1[0][0], 1, 0.03);
    EXPECT_NEAR(res1[1][0], 0, 0.03);
    EXPECT_NEAR(res1[1][1], -3, 0.03);

    // test case 2
    Matrix matrix2{{1, 2, 3}, {4, 7, 5}, {6, 1, 3}};
    Matrix res2{algebra::upper_triangular(matrix2)};
    EXPECT_NEAR(res2[0][0], 1, 0.03);
    EXPECT_NEAR(res2[1][0], 0, 0.03);
    EXPECT_NEAR(res2[2][0], 0, 0.03);
    EXPECT_NEAR(res2[2][1], 0, 0.03);
    EXPECT_NEAR(res2[2][2], 62, 0.03);
}

TEST(HW1Test, BONUS) {
    // test case
    Matrix matrix2{{0, 2, 3}, {4, 7, 5}, {6, 1, 3}};
    Matrix res2{algebra::upper_triangular(matrix2)};
    EXPECT_NEAR(res2[0][0], 4, 0.03);
    EXPECT_NEAR(res2[1][0], 0, 0.03);
    EXPECT_NEAR(res2[2][0], 0, 0.03);
    EXPECT_NEAR(res2[2][1], 0, 0.03);
    EXPECT_NEAR(res2[2][2], 39/4.0, 0.03);
}
*/



