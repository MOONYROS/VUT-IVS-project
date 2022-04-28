/**
 * @file matlib_tests.cpp
 * 
 * @author Ondrej Koumar, xkouma02
 * @author Marek Konecny, xkonec85
 * @author Ondrej Lukasek, xlukas15
 * @author Jonas Morkus, xmorku03
 * 
 * @brief Testing program (based on GTest) for mathematical library of Calculandum Machina.
 * 
 * Not many information about the tests are provided;
 * the code itself is pretty self-explanatory.
 * All the EQ statements are double, which means that
 * it checks the equality of finite number of decimal places.
 */

#include <cmath>
#include "matlib.h"
#include "gtest/gtest.h"

Matlib matlib;

/**
 * @brief Test cases for addiction.
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
 * @brief Test cases for subtraction.
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
 * @brief Test cases for multiplication.
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
 * @brief Test cases for division.
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
    EXPECT_ANY_THROW(matlib.div(20, 0));
}

/**
 * @brief Test cases for factorial.
 */
TEST(factorialTest, legalNumbers)
{
    EXPECT_EQ(matlib.factorial(10), 3628800);
    EXPECT_EQ(matlib.factorial(0), 1);
    EXPECT_EQ(matlib.factorial(1), 1);
}

TEST(factorialTest, illegalNumbers)
{
    EXPECT_ANY_THROW(matlib.factorial(-1));
    EXPECT_ANY_THROW(matlib.factorial(21));
}

/**
 * @brief Test cases for nth power.
 */
TEST(powerTest, positiveNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.power(1.2, 2), pow(1.2, 2));
    EXPECT_DOUBLE_EQ(matlib.power(1.05, 42), pow(1.05, 42));
    EXPECT_DOUBLE_EQ(matlib.power(2, 10), pow(2, 10));
}

TEST(powerTest, negativeNumbers)
{
    EXPECT_DOUBLE_EQ(matlib.power(-5.6, 3), pow(-5.6, 3));
    EXPECT_DOUBLE_EQ(matlib.power(-1, 8), pow(-1, 8));
}

TEST(powerTest, zero)
{
    EXPECT_DOUBLE_EQ(matlib.power(234234, 0), pow(234234, 0)); // Exponent is zero
    EXPECT_DOUBLE_EQ(matlib.power(0, 2342), pow(0, 2342)); // Base is zero
}

TEST(powerTest, negativeExponent)
{
    EXPECT_ANY_THROW(matlib.power(234, -4));
}

/**
 * @brief Test cases for nth root.
 */
TEST(rootTest, validCases)
{
    EXPECT_NEAR(matlib.root(-5, 3), -1.70997594667, 10e-8);
    EXPECT_NEAR(matlib.root(-27, 3), -3, 10e-8);
    EXPECT_NEAR(matlib.root(-81, 3), -4.326748711, 10e-8);
    EXPECT_NEAR(matlib.root(-7, 7), -1.320469248, 10e-8);
    EXPECT_NEAR(matlib.root(16, 4), pow(16, 1.0/4), 10e-8);
    EXPECT_NEAR(matlib.root(7, 8), pow(7, 1.0/8), 10e-8);
}

TEST(rootTest, invalidCases)
{
    EXPECT_ANY_THROW(matlib.root(200, -4));
    EXPECT_ANY_THROW(matlib.root(4, -3));
}

/**
 * @brief Test cases for natural logarithm.
 */
TEST(lnTest, validCases)
{
    EXPECT_NEAR(matlib.ln(10), log(10), 10e-8);
    EXPECT_DOUBLE_EQ(matlib.ln(1), log(1));
    EXPECT_NEAR(matlib.ln(123.0), log(123.0), 10e-8);
}

TEST(lnTest, invalidCases)
{
    EXPECT_ANY_THROW(matlib.ln(0));
    EXPECT_ANY_THROW(matlib.ln(-10));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}