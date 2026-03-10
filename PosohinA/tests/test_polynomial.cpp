#include <gtest/gtest.h>
#include "../lib_polynomial/polynomial.h"

TEST(Test_Polynomial, test_constructor1) {
	ASSERT_NO_THROW(Polynomial A);
}

TEST(Test_Polynomial, test_sum_numb) {
	EXPECT_EQ(sum_numb(123), 6);
	EXPECT_EQ(sum_numb(684), 18);
}

TEST(Test_Polynomial, test_record) {
	Polynomial A;
	List B;
	A.record(); // нужно вводить такие цифры 4 2 0 0	-9 2 3 7	 6 0 0 3	
	B.push_back(std::pair<double, int>{-9, 237});
	B.push_back(std::pair<double, int>{6, 003});
	B.push_back(std::pair<double, int>{4, 200});
	Polynomial C(B);
	EXPECT_EQ(A, C);
}

TEST(Test_Polynomial, test_summ) {
	Polynomial A, C, D;
	List B;
	A.record(); // нужно вводить такие цифры 4 2 0 0	-9 2 3 7	 6 0 0 3	
	C.record(); // нужно вводить такие цифры 3 2 0 0	-3 2 0 0	 5 1 6 0		-6 1 0 2
	B.push_back(std::pair<double, int>{-9, 237});
	B.push_back(std::pair<double, int>{5, 160});
	B.push_back(std::pair<double, int>{-6, 102});
	B.push_back(std::pair<double, int>{6, 003});
	B.push_back(std::pair<double, int>{4, 200});
	D = A + C;
	Polynomial D1(B);
	EXPECT_EQ(D, D1);
}

TEST(Test_Polynomial, test_sub) {
	Polynomial A, C, D;
	List B;
	A.record(); // нужно вводить такие цифры 4 2 0 0	-9 2 3 7	 6 0 0 3	
	C.record(); // нужно вводить такие цифры 3 2 0 0	-3 2 0 0	 5 1 6 0		-6 1 0 2
	B.push_back(std::pair<double, int>{-9, 237});
	B.push_back(std::pair<double, int>{-5, 160});
	B.push_back(std::pair<double, int>{+6, 102});
	B.push_back(std::pair<double, int>{6, 003});
	B.push_back(std::pair<double, int>{4, 200});
	D = A - C;
	Polynomial D1(B);
	EXPECT_EQ(D, D1);
}

TEST(Test_Polynomial, test_mul_const) {
	Polynomial A, D;
	List B;
	A.record(); // нужно вводить такие цифры 4 2 0 0	-9 2 3 7	 6 0 0 3	
	B.push_back(std::pair<double, int>{27, 237});
	B.push_back(std::pair<double, int>{-18, 003});
	B.push_back(std::pair<double, int>{-12, 200});
	D = (-3) * A;
	Polynomial D1(B);
	EXPECT_EQ(D, D1);
}

TEST(Test_Polynomial, test_mul) {
	Polynomial A, C, D;
	List B;
	A.record(); // нужно вводить такие цифры 4 2 0 0	-9 2 3 5	 6 0 0 3	
	C.record(); // нужно вводить такие цифры 3 2 0 0	-3 2 0 0	 5 1 4 0		-6 1 0 2
	B.push_back(std::pair<double, int>{-45, 375});
	B.push_back(std::pair<double, int>{54, 337});
	B.push_back(std::pair<double, int>{+30, 143});
	B.push_back(std::pair<double, int>{20, 340});
	B.push_back(std::pair<double, int>{-36, 105});
	B.push_back(std::pair<double, int>{-24, 302});
	D = A * C;
	Polynomial D1(B);
	EXPECT_EQ(D, D1);
}

TEST(Test_Polynomial, test_rav) {
	Polynomial A, C;
	List B;
	A.record(); // нужно вводить такие цифры 4 2 0 0	-9 2 3 7	 6 0 0 3	
	B.push_back(std::pair<double, int>{-9, 237});
	B.push_back(std::pair<double, int>{6, 003});
	B.push_back(std::pair<double, int>{4, 200});
	C = A;
	Polynomial D(B);
	EXPECT_EQ(D, C);
}