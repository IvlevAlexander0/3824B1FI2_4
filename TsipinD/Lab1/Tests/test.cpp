#include "pch.h"


#include "../Lab1/polynomial.h"


// ------------------------- NODE TESTS --------------------------------------
TEST(NodeTest, MoreLessEqual) {
    Node n1(33, 1); // 033
    Node n2(202, 1.0);
    EXPECT_TRUE(n1 > n2); // в первую очередь порядок по степеням
    EXPECT_FALSE(n1 < n2);
    EXPECT_FALSE(n1 == n2);
    EXPECT_FALSE(n2 > n1);

    Node n3(513, 1);
    Node n4(522, 1);
    EXPECT_TRUE(n3 > n4);

    Node n5(120, 1);
    Node n6(210, 1);
    EXPECT_TRUE(n6 > n5); // если одинаковые степени, порядок лексический (X > Y > Z)
}

// -------------------------- LIST TESTS -----------------------------------------------

TEST(ListTest, SimplePushBackOrder) {
    List l;
    l.simple_push_back(1, 101);
    l.simple_push_back(2, 202);
    l.simple_push_back(3, 303); //  101 <> 202 <> 303

    Node* curr = l.head;
    EXPECT_NE(curr, nullptr);
    EXPECT_EQ(curr->power, 101);
    curr = curr->next;
    EXPECT_NE(curr, nullptr);
    EXPECT_EQ(curr->power, 202);
    curr = curr->next;
    EXPECT_EQ(curr->power, 303);
}

TEST(ListTest, PushBackSortedInsertion) { 
    List l;

    l.push_back(1, 101); // макс ст. 1
    l.push_back(3, 303); // макс ст. 3
    l.push_back(2, 202); // макс ст. 2

    // Ожидаемый порядок: 303, 202, 101
    Node* curr = l.head;
    EXPECT_EQ(curr->power, 303);
    curr = curr->next;
    EXPECT_EQ(curr->power, 202);
    curr = curr->next;
    EXPECT_EQ(curr->power, 101);
}

TEST(ListTest, PushBackSameCoefficients) {
    List l;
    l.push_back(10.0, 555);
    l.push_back(5.5, 555);
    l.push_back(-2.0, 555);

    EXPECT_NE(l.head, nullptr);
    EXPECT_EQ(l.head->coeff, 13.5);
    EXPECT_EQ(l.head->next, nullptr); // нод всего 1
}

TEST(ListTest, DeleteNode) {
    List l;
    l.simple_push_back(1, 111);
    l.simple_push_back(2, 222);
    l.simple_push_back(3, 333);

    l.deleteNode(l.head->next); // удаляем 222 из середины
    EXPECT_EQ(l.head->next->power, 333);
    EXPECT_EQ(l.tail->power, 333);

    l.deleteNode(l.head);       // удалить голову
    EXPECT_EQ(l.head->power, 333);
    EXPECT_EQ(l.head, l.tail);

    l.deleteNode(l.head);        // удалить хвост
    EXPECT_EQ(l.head, nullptr);
    EXPECT_EQ(l.tail, nullptr);
}

TEST(ListTest, CopyConstructor) {
    List l1;
    l1.simple_push_back(1, 100);
    l1.simple_push_back(2, 200);

    List l2 = l1;

    EXPECT_EQ(l2.head->power, 100);
    EXPECT_EQ(l2.tail->power, 200);


    l2.head->coeff = 99.9;
    EXPECT_NE(l1.head->coeff, l2.head->coeff);


    EXPECT_EQ(l2.tail->prev, l2.head);
    EXPECT_EQ(l2.head->next, l2.tail);
}

TEST(ListTest, Assignment) {
    List l1, l2;
    l1.simple_push_back(1, 100);
    l2.simple_push_back(5.5, 500);

    l2 = l1;

    EXPECT_EQ(l2.head->power, 100);
    EXPECT_EQ(l2.head->next, nullptr);

    l2 = l2;                              // самоприсваивание
    EXPECT_EQ(l2.head->power, 100);
}

//--------------------------------- POLYNOM TESTS --------------------------------

TEST(PolynomTest, AdditionSimple) {
    Polynom p1, p2;
    p1.push_back(2, 101); // 2 xz
    p2.push_back(3, 202); // 3 x2z2

    Polynom res = p1 + p2;

    EXPECT_NE(res.poly.head, nullptr);  // (202 > 101)
    EXPECT_EQ(res.poly.head->power, 202);
    EXPECT_DOUBLE_EQ(res.poly.head->coeff, 3.0);

    EXPECT_NE(res.poly.head->next, nullptr);
    EXPECT_EQ(res.poly.head->next->power, 101);
    EXPECT_DOUBLE_EQ(res.poly.head->next->coeff, 2.0);
}

TEST(PolynomTest, AdditionMerging) {
    Polynom p1, p2;
    p1.push_back(5, 303);
    p1.push_back(1, 101);

    p2.push_back(2, 303); // степень как у монома p1

    Polynom res = p1 + p2;

    // 7 303 , 1 101
    EXPECT_DOUBLE_EQ(res.poly.head->coeff, 7);
    EXPECT_EQ(res.poly.head->power, 303);
    EXPECT_EQ(res.poly.head->next->power, 101);
}

TEST(PolynomTest, SubtractionToZero) {
    Polynom p1, p2;
    p1.poly.push_back(10, 555);
    p2.poly.push_back(10, 555);

    Polynom res = p1 - p2;

    EXPECT_EQ(res.poly.head, nullptr);
}

TEST(PolynomTest, ScalarMultiplication) {
    Polynom p1;
    p1.poly.push_back(2, 111);
    p1.poly.push_back(-3, 222);

    Polynom res = p1 * (-2);

    // p1: -3 222, 2 111, после умножения: 6 222, -4 111
    EXPECT_DOUBLE_EQ(res.poly.head->coeff, 6);
    EXPECT_DOUBLE_EQ(res.poly.head->next->coeff, -4);
}

TEST(PolynomTest, PolynomialMultiplication) {
    // (x + 1) * (x - 1) = x^2 - 1
    Polynom p1, p2;
    p1.poly.push_back(1.0, 100); // x
    p1.poly.push_back(1.0, 000); // 1

    p2.poly.push_back(1.0, 100); // x
    p2.poly.push_back(-1.0, 000); // -1

    Polynom res = p1 * p2;

    // 1 200, -1 000
    ASSERT_NE(res.poly.head, nullptr);
    EXPECT_EQ(res.poly.head->power, 200);
    EXPECT_DOUBLE_EQ(res.poly.head->coeff, 1.0);

    ASSERT_NE(res.poly.head->next, nullptr);
    EXPECT_EQ(res.poly.head->next->power, 000);
    EXPECT_DOUBLE_EQ(res.poly.head->next->coeff, -1.0);
    EXPECT_EQ(res.poly.head->next->next, nullptr);
}

TEST(PolynomTest, MultiplicationDegreeOverflow) {
    Polynom p1, p2;
    p1.push_back(1.0, 900); // x^9
    p2.push_back(1.0, 100); // x^1

    // x^9 * x^1 = x^10 (px > 9)
    EXPECT_THROW(p1 * p2, std::runtime_error);
}

TEST(PolynomTest, MathematicalOrderSorting) {
    Polynom p;

    p.push_back(1.0, 101); // max deg 1
    p.push_back(2.0, 202); // max deg 2
    p.push_back(3.0, 33); // max deg 3

    // 33, 202, 101
    Node* curr = p.poly.head;
    EXPECT_NE(curr, nullptr);
    EXPECT_EQ(curr->power, 33);

    curr = curr->next;
    EXPECT_NE(curr, nullptr);
    EXPECT_EQ(curr->power, 202);

    curr = curr->next;
    EXPECT_NE(curr, nullptr);
    EXPECT_EQ(curr->power, 101);
}