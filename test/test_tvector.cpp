#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int a[4] = { 1,2,3,4 };
	TDynamicVector <int> v(a, 4);
	TDynamicVector <int> b(v);
	ASSERT_EQ(b, v);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int* a = new int[4];
	for (int i = 0; i < 4; i++)
		a[i] = i;
	TDynamicVector <int>* a1 = new TDynamicVector<int>(a, 4);
	TDynamicVector<int> ca(*a1);
	delete a1;
	ASSERT_NO_THROW(ca[0]);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(-761) = 12);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v[761] = 12);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	int a[4] = { 1,2,3,4 };
	TDynamicVector <int> v(a, 4);
	TDynamicVector <int> v2(a, 4);
	v = v;
	EXPECT_EQ(v, v2);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	int a[4] = { 1,2,3,4 };
	int b[4] = { 4,3,2,1 };
	TDynamicVector <int> v(a, 4);
	TDynamicVector <int> v2(b, 4);
	v2 = v;
	EXPECT_EQ(v, v2);
}


TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	int a[4] = { 1,2,3,4 };
	int b[2] = { 4,3 };
	TDynamicVector <int> v(a, 4);
	TDynamicVector <int> v2(b, 2);
	v2 = v;
	EXPECT_EQ(v, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int a[4] = { 1,2,3,4 };
	int b[4] = { 1,2,3,4 };
	TDynamicVector <int> v(a, 4);
	TDynamicVector <int> v2(b, 4);
	ASSERT_TRUE(v2 == v);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int a[4] = { 1,2,3,4 };
	TDynamicVector <int> v(a, 4);
	ASSERT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	int a[4] = { 1,2,3,4 };
	int b[2] = { 4,3 };
	TDynamicVector <int> v(a, 4);
	TDynamicVector <int> v2(b, 2);
	ASSERT_FALSE(v2 == v);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int a[4] = { 1,2,3,4 };
	int n = 1;
	TDynamicVector <int> v(a, 4);
	int b[4] = { 2,3,4,5 };
	TDynamicVector <int> v2(b, 4);
	v = v + n;
	EXPECT_EQ(v, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{

	int a[4] = { 1,2,3,4 };
	int n = 1;
	TDynamicVector <int> v(a, 4);
	int b[4] = { 2,3,4,5 };
	TDynamicVector <int> v2(b, 4);
	v2 = v2 - n;
	EXPECT_EQ(v, v2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int a[4] = { 1,2,3,4 };
	int n = 2;
	TDynamicVector <int> v(a, 4);
	int b[4] = { 2,4,6,8 };
	TDynamicVector <int> v2(b, 4);
	v = v * n;
	EXPECT_EQ(v, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int a[4] = { 1,2,3,4 };
	int b[4] = { 4,3,2,1 };
	int c[4] = { 5,5,5,5 };
	TDynamicVector <int> v(a, 4);
	TDynamicVector <int> v2(b, 4);
	TDynamicVector <int> result(c, 4);
	TDynamicVector <int>v3(v + v2);
	EXPECT_EQ(v3, result);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	int a[4] = { 1,2,3,4 };
	int b[2] = { 4,3 };
	TDynamicVector <int> v(a, 4);
	TDynamicVector <int> v2(b, 2);
	ASSERT_ANY_THROW(v + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int a[4] = { 1,2,3,4 };
	int b[4] = { 4,3,2,1 };
	int c[4] = { 5,5,5,5 };
	TDynamicVector <int> v(a, 4);
	TDynamicVector <int> v2(b, 4);
	TDynamicVector <int> result(c, 4);
	TDynamicVector <int>v3(result - v2);
	EXPECT_EQ(v, v3);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	int a[4] = { 1,2,3,4 };
	int b[2] = { 4,3 };
	TDynamicVector <int> v(a, 4);
	TDynamicVector <int> v2(b, 2);
	ASSERT_ANY_THROW(v - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int a[4] = { 1,2,3,4 };
	int b[4] = { 4,3,2,1 };
	int ans = 20;
	TDynamicVector <int> v(a, 4);
	TDynamicVector <int> v2(b, 4);
	EXPECT_EQ(ans, v * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	int a[4] = { 1,2,3,4 };
	int b[2] = { 4,3 };
	TDynamicVector <int> v(a, 4);
	TDynamicVector <int> v2(b, 2);
	ASSERT_ANY_THROW(v * v2);
}

