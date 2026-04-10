#include <random>
#include "pch.h"
#include "..\Polynomials\Polynomial.h"
#include "..\Polynomials\Polynomial.cpp"

using namespace std;

TEST(Polynomial_constructor, default_constructor_no_throw) {
  EXPECT_NO_THROW(Polynomial());
}

TEST(Polynomial_constructor, double_constructor_no_throw) {
	EXPECT_NO_THROW(Polynomial(213));
}

TEST(Polynomial_constructor, double_constructor) {
	const Polynomial t1(213.);
	Polynomial::const_iterator it1 = t1.begin();
	EXPECT_DOUBLE_EQ(213., it1->coef);
	EXPECT_EQ(0, it1->degs);

	const Polynomial t2(-213.);
	Polynomial::const_iterator it2 = t2.begin();
	EXPECT_DOUBLE_EQ(-213., it2->coef);
	EXPECT_EQ(0, it2->degs);
}

TEST(Polynomial_constructor, string_constructor_no_throw) {
	EXPECT_NO_THROW(Polynomial("-123 + 0.1154 +145 - -874 + 123"));
}

TEST(Polynomial_constructor, string_constructor) {
	Polynomial t1("-123 + 0.1154 +145 - -874 + 123 - 0.15111");
	EXPECT_EQ("-0.150000*x^1y^1z^1 + 1.000000*x^1y^4z^5 + 0.100000*x^1y^5z^4 + 1.000000*x^8y^7z^4", t1.get(1));
	
	Polynomial t2("0123 - 0547");
	EXPECT_EQ("0", t2.get());
}

TEST(Polynomial_constructor, string_constructor_exceptions) {
	EXPECT_THROW(Polynomial("1"), length_error);
	EXPECT_THROW(Polynomial("a123"), invalid_argument);
	EXPECT_THROW(Polynomial("1a3"), invalid_argument);

}

TEST(Polynomial_constructor, copy_constructor) {
	Polynomial t1("1111 - 2222");
	Polynomial t2(t1);
	EXPECT_EQ("1.000000*111 - 2.000000*222", t2.get());
}

TEST(Polynomial_operators, unar_minus) {
	Polynomial t("111");
	EXPECT_EQ("-1.000000*111", (-t).get());
}


TEST(Polynomial_operators, plus) {
	Polynomial t1("111 + 345 - 2444");
	Polynomial t2("2444 + 345 + 544");
	EXPECT_EQ("1.000000*111 + 2.000000*345 + 1.000000*544", (t1 + t2).get());

	EXPECT_EQ("1.000000*111 + 1.000000*345 + 2.000000*444 + 1.000000*544", (t2 + Polynomial("111")).get());
}

TEST(Polynomial_operators, plus_empty) {
	Polynomial t1;
	Polynomial t2;
	EXPECT_EQ("0", (t1 + t2).get());
}


TEST(Polynomial_operators, minus) {
	Polynomial t1("111 + 345 - 2444");
	Polynomial t2("-2444 - 345 - 544");

	EXPECT_EQ("1.000000*111 + 2.000000*345 + 1.000000*544", (t1 - t2).get());

	EXPECT_EQ("-1.000000*111 - 1.000000*345 - 2.000000*444 - 1.000000*544", (t2 - Polynomial("111")).get());

	EXPECT_EQ("0", (t1 - t1).get());
}

TEST(Polynomial_operators, multiply_by_scalar) {
	Polynomial t1("30111 - 4367");
	EXPECT_EQ("15.000000*111 - 2.000000*367", (t1 * 0.5).get());
	
	t1 += (Polynomial)"123";
	EXPECT_EQ("0", (t1 * 0).get());
}

TEST(Polynomial_operators, multiply_between_polynomials) {
	Polynomial t1("1001 - 1000"); // z - 1
	Polynomial t2("1001 + 1000"); // z + 1
	EXPECT_EQ("-1.000000 + 1.000000*2", (t1 * t2).get()); // z^2 - 1
}

TEST(Polynomial_operators, multiply_between_empty_polynomials) {
	Polynomial t1;
	Polynomial t2;
	EXPECT_EQ("0", (t1 * t2).get());
}

TEST(Polynomial_operators, multiply_between_polynomials_overflow) {
	Polynomial t1("1555 - 1000");
	Polynomial t2("1555 + 1000");
	EXPECT_THROW(t1 * t2, overflow_error);
}

TEST(Polynomial_operators, assign_operator) {
	Polynomial t1("1555 - 1000");
	Polynomial t2;
	EXPECT_EQ("-1.000000 + 1.000000*555", (t2 = t1).get());
}

TEST(Polynomial_operators, self_assign_no_throw) {
	Polynomial t("1555 - 1000");
	EXPECT_NO_THROW(t = t);
	EXPECT_EQ("-1.000000 + 1.000000*555", t.get());
}


TEST(Polynomial_methods, clear) {
	Polynomial t("123 + 321");
	EXPECT_NO_THROW(t.clear());
	
	t.clear();
	EXPECT_EQ("0", t.get());
	
	auto beg_it = static_cast<const Polynomial&>(t).begin();
	auto end_it = static_cast<const Polynomial&>(t).end();
	EXPECT_EQ(beg_it, end_it);
	
	EXPECT_NO_THROW(t += (Polynomial)"111"); //Проверка того, что объект всё ещё можно использовать
	EXPECT_EQ("1.000000*111", t.get()); 
}

TEST(Polynomial_methods, swap) {
	{
		Polynomial t1("1444 - 1000");
		Polynomial t2("1555 + 1000");
		EXPECT_NO_THROW(swap(t1, t2));
	}
	Polynomial t1("1444 - 1000");
	Polynomial t2("1555 + 1000");
	t1.swap(t2);
	EXPECT_EQ("1.000000 + 1.000000*555", t1.get());
	EXPECT_EQ("-1.000000 + 1.000000*444", t2.get());
}

TEST(In_and_Out, in_and_out) {
	Polynomial t1;
	string s("-123 + 0.1154 +145 - -874 + 123 - 0.15111");
	istringstream in(s);
	in >> t1;
	EXPECT_EQ("-0.150000*x^1y^1z^1 + 1.000000*x^1y^4z^5 + 0.100000*x^1y^5z^4 + 1.000000*x^8y^7z^4", t1.get(1));
	ostringstream out;
	out << t1;
	EXPECT_EQ("-0.150000*x^1y^1z^1 + 1.000000*x^1y^4z^5 + 0.100000*x^1y^5z^4 + 1.000000*x^8y^7z^4", out.str());
}