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

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}