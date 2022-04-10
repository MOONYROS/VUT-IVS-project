/**
 * @file matlib_tests.cpp
 * @author Ondrej Koumar (xkouma02), Marek Konecny (xkonec85)
 * @brief Testing program (based on GTest) for mathematical library of Calculandum Machina.
 */

#include "matlib.cpp"
#include "gtest/gtest.h"

Matlib matlib;

/**
 * @brief Add tests
 */
TEST(addTest, positiveNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.add(10, 20), 30);
}

TEST(addTest, negativeNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.add(-10, -20), -30);
}

TEST(addTest, mixedNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.add(-10, 20), 10);
}

/**
 * @brief Sub tests 
 */
TEST(subTest, positiveNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.sub(20, 10), 10);
}

TEST(subTest, negativeNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.sub(-10, -20), 10);
}

TEST(subTest, mixedNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.sub(-20, 10), -30);
}

/**
 * @brief Mul tests 
 */
TEST(mulTest, positiveNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.mul(10, 20), 200);
}

TEST(mulTest, negativeNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.mul(-10, -20), 200);
}

TEST(mulTest, mixedNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.mul(-10, 20), -200);
}

/**
 * @brief Div tests 
 */
TEST(divTest, positiveNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.div(20, 10), 2);
}

TEST(divTest, negativeNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.div(-20, -10), 2);
}

TEST(divTest, mixedNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.div(-20, 10), -2);
}

TEST(divTest, divisionByZero)
{
    EXPECT_THROW(matlib.div(20, 0), invalid_argument);
}

/**
 * @brief Factorial tests
 */
TEST(factorialTest, legalNumbers)
{
    EXPECT_EQ(matlib.factorial(10), 3628800);
    EXPECT_EQ(matlib.factorial(0), 1);
    EXPECT_EQ(matlib.factorial(1), 1);
}

TEST(factorialTest, illegalNumbers)
{
    EXPECT_THROW(matlib.factorial(-1), out_of_range);
    EXPECT_THROW(matlib.factorial(21), out_of_range);
}

/**
 * @brief Power tests 
 */
TEST(powerTest, positiveNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.power(1.2, 2), 1.44);
    EXPECT_DOUBLE_EQ(matlib.power(1.05, 42), 7.761587555);
    EXPECT_DOUBLE_EQ(matlib.power(2, 10), 1024);
}

TEST(powerTest, negativeNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.power(-5.6, 3), -167.854412445);
    EXPECT_DOUBLE_EQ(matlib.power(-1, 8), 1);
}

TEST(powerTest, zero)
{
    EXPECT_DOUBLE_EQ(matlib.power(234234, 0), 1); // Exponent is zero
    EXPECT_DOUBLE_EQ(matlib.power(0, 2342), 0); // Base is zero
}

TEST(powerTest, negativeExponent)
{
    EXPECT_THROW(matlib.power(234, -4), out_of_range);
}

/**
 * @brief Root tests
 */
TEST(rootTest, validCases)
{
    EXPECT_DOUBLE_EQ(matlib.root(-5, 3), -1.709975946);
    EXPECT_DOUBLE_EQ(matlib.root(16, 4), 2);
    EXPECT_DOUBLE_EQ(matlib.root(7, 8), 1.345900192);
}

TEST(rootTest, invalidCases)
{
    EXPECT_THROW(matlib.root(200, -4), out_of_range);
    EXPECT_THROW(matlib.root(4, -3), invalid_argument);
}

/**
 * @brief Log tests 
 */
TEST(logTest, validCases)
{
    EXPECT_DOUBLE_EQ(matlib.log(10), 1);
    EXPECT_DOUBLE_EQ(matlib.log(1), 0);
    EXPECT_DOUBLE_EQ(matlib.log(123), 2.089905111);
}

TEST(logTest, invalidCases)
{
    EXPECT_THROW(matlib.log(0), out_of_range);
    EXPECT_THROW(matlib.log(-10), out_of_range);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}