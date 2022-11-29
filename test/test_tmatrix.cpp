#include "tmatrix.h"

#include <gtest.h>
typedef TDynamicMatrix<int> M;
TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{

	M A(2);
	A[0][0] = 1;
	A[0][1] = 2;
	A[1][0] = 3;
	A[1][1] = 4;
	ASSERT_NO_THROW(M B(A));

}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	M A(2);
	A[0][0] = 1;
	A[0][1] = 2;
	A[1][0] = 3;
	A[1][1] = 4;
	M B(A);
	ASSERT_EQ(A, B);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	M* A = new M(2);
	M B(*A);
	delete A;
	ASSERT_NO_THROW(B[1][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
	M A(4);
	ASSERT_EQ(4, A.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	M A(2);
	A[1][1] = 100500;
	EXPECT_EQ(100500, A[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	M A(2);
	EXPECT_ANY_THROW(A[-10][-10] = 15);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	M A(2);
	EXPECT_ANY_THROW(A[10][10] = 10);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	M A(2);
	A[0][0] = 1;
	A[0][1] = 2;
	A[1][0] = 3;
	A[1][1] = 4;
	M B(A);
	A = A;
	EXPECT_EQ(A, B);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	M A(2);
	A[0][0] = 1;
	A[0][1] = 2;
	A[1][0] = 3;
	A[1][1] = 4;
	M B(2);
	B[0][0] = 0;
	B[0][1] = 2;
	B[1][0] = 3876;
	B[1][1] = 4;
	B = A;
	EXPECT_EQ(A, B);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	M A(2);
	M B(10);
	B = A;
	EXPECT_EQ(A.size(), B.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	M A(2);
	M B(16);
	A[0][0] = 1;
	A[0][1] = 2;
	A[1][0] = 3;
	A[1][1] = 4;
	B = A;
	EXPECT_EQ(A, B);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	M A(2);
	A[0][0] = 1;
	A[0][1] = 2;
	A[1][0] = 3;
	A[1][1] = 4;
	M B(A);
	EXPECT_TRUE(A == B);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	M A(2);
	EXPECT_TRUE(A == A);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	M A(2);
	M B(5);
	EXPECT_FALSE(A == B);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	M A(2);
	A[0][0] = 1;
	A[0][1] = 2;
	A[1][0] = 3;
	A[1][1] = 4;
	M B(2);
	B[0][0] = 0;
	B[0][1] = 2;
	B[1][0] = 3876;
	B[1][1] = 4;
	M C(2);
	C[0][0] = 1;
	C[0][1] = 4;
	C[1][0] = 3879;
	C[1][1] = 8;
	M R(2);
	R = A + B;
	EXPECT_EQ(R, C);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	M A(2);
	M B(19);
	EXPECT_ANY_THROW(A + B);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	M A(2);
	A[0][0] = 1;
	A[0][1] = 2;
	A[1][0] = 3;
	A[1][1] = 4;
	M B(2);
	B[0][0] = 0;
	B[0][1] = 2;
	B[1][0] = 3876;
	B[1][1] = 4;
	M C(2);
	C[0][0] = 1;
	C[0][1] = 4;
	C[1][0] = 3879;
	C[1][1] = 8;
	M R(2);
	R = C - B;
	EXPECT_EQ(R, A);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	M A(2);
	M B(8);
	EXPECT_ANY_THROW(A - B);
}

