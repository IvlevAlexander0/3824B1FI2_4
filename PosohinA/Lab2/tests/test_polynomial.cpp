#include <gtest/gtest.h>
#include "../lib_polynomial/polynomial.h"

TEST(Test_Polynomial, test_constructor1) {
	ASSERT_NO_THROW(Polynomial A);
}

TEST(Test_Polynomial, test_sum_numb) {
	EXPECT_EQ(sum_numb(123), 6);
	EXPECT_EQ(sum_numb(684), 18);
}

//TEST(Test_Polynomial, test_record) {
//	Polynomial A;
//	List B;
//	A.record(); // нужно вводить такие цифры 4 2 0 0	-9 2 3 7	 6 0 0 3	
//	B.push_back(std::pair<double, int>{-9, 237});
//	B.push_back(std::pair<double, int>{6, 003});
//	B.push_back(std::pair<double, int>{4, 200});
//	Polynomial C(B);
//	EXPECT_EQ(A, C);
//}

TEST(Test_Polynomial, test_summ) {
	Polynomial D;
	List B, A, C;
	A.push_back(std::pair<double, int>{-9, 237});
	A.push_back(std::pair<double, int>{6, 3});
	A.push_back(std::pair<double, int>{4, 200});


	C.push_back(std::pair<double, int>{5, 160});
	C.push_back(std::pair<double, int>{-6, 102}); 
	
	B.push_back(std::pair<double, int>{-9, 237});
	B.push_back(std::pair<double, int>{5, 160});
	B.push_back(std::pair<double, int>{-6, 102});
	B.push_back(std::pair<double, int>{6, 003});
	B.push_back(std::pair<double, int>{4, 200});

	Polynomial A1(A), C1(C);
	D = A1 + C1;
	Polynomial D1(B);
	EXPECT_EQ(D, D1);
}

TEST(Test_Polynomial, test_sub) {
	Polynomial D;
	List B, A, C;
	A.push_back(std::pair<double, int>{-9, 237});
	A.push_back(std::pair<double, int>{6, 3});
	A.push_back(std::pair<double, int>{4, 200});


	C.push_back(std::pair<double, int>{5, 160});
	C.push_back(std::pair<double, int>{-6, 102});

	B.push_back(std::pair<double, int>{-9, 237});
	B.push_back(std::pair<double, int>{-5, 160});
	B.push_back(std::pair<double, int>{+6, 102});
	B.push_back(std::pair<double, int>{6, 003});
	B.push_back(std::pair<double, int>{4, 200});

	Polynomial A1(A), C1(C);
	D = A1 - C1;
	Polynomial D1(B);
	EXPECT_EQ(D, D1);
}

TEST(Test_Polynomial, test_mul_const) {
	Polynomial D;
	List B, A;
	A.push_back(std::pair<double, int>{-9, 237});
	A.push_back(std::pair<double, int>{6, 3});
	A.push_back(std::pair<double, int>{4, 200});

	B.push_back(std::pair<double, int>{27, 237});
	B.push_back(std::pair<double, int>{-18, 003});
	B.push_back(std::pair<double, int>{-12, 200});
	Polynomial A1(A);

	D = (-3) * A1;
	Polynomial D1(B);
	EXPECT_EQ(D, D1);
}

TEST(Test_Polynomial, test_mul) {
	Polynomial D;
	List B, A, C;
	A.push_back(std::pair<double, int>{-9, 235});
	A.push_back(std::pair<double, int>{6, 3});
	A.push_back(std::pair<double, int>{4, 200});

	C.push_back(std::pair<double, int>{5, 140});
	C.push_back(std::pair<double, int>{-6, 102});

	B.push_back(std::pair<double, int>{-45, 375});
	B.push_back(std::pair<double, int>{54, 337});
	B.push_back(std::pair<double, int>{+30, 143});
	B.push_back(std::pair<double, int>{20, 340});
	B.push_back(std::pair<double, int>{-36, 105});
	B.push_back(std::pair<double, int>{-24, 302});

	Polynomial A1(A), C1(C);
	D = A1 * C1;
	Polynomial D1(B);
	EXPECT_EQ(D, D1);
}

TEST(Test_Polynomial, test_rav) {
	Polynomial C;
	List B, A;
	A.push_back(std::pair<double, int>{-9, 237});
	A.push_back(std::pair<double, int>{6, 3});
	A.push_back(std::pair<double, int>{4, 200});

	B.push_back(std::pair<double, int>{-9, 237});
	B.push_back(std::pair<double, int>{6, 003});
	B.push_back(std::pair<double, int>{4, 200});

	Polynomial A1(A);
	C = A;
	Polynomial D(B);
	EXPECT_EQ(D, C);
}

TEST(Test_Polynomial, test_overflou) {
	List A, C;
	A.push_back(std::pair<double, int>{-9, 235});
	C.push_back(std::pair<double, int>{-6, 107});
	Polynomial A1(A), C1(C);
	ASSERT_ANY_THROW(A1 * C1);
}