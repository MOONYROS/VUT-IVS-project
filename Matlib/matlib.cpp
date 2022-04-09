/**
 * @file matlib.cpp
 * @author Ondrej Koumar (xkouma02), Marek Konecny (xkonec85)
 * @brief Implementation of Matlib class methods declared in matlib.h.
 */

#include <stdexcept>
#include "matlib.h"

using namespace std;

double Matlib::add(double a, double b)
{
    return (a + b);
}

double Matlib::sub(double a, double b)
{
    return (a - b);
}

double Matlib::mul(double a, double b)
{
    return (a * b);
}

double Matlib::div(double a, double b)
{
    if (b == 0)
    {
        throw invalid_argument("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    }

    return (a / b);
}

unsigned long long Matlib::factorial(unsigned short a)
{
    unsigned long long result = 1;

    if (a < 0 || a > 20)
    {
        // The max val can be 20 because 21! cannot fit to 64 bits
        throw out_of_range("The number that factorial is calculated from has to be in interval <0, 20>.");
    }

    for (a; a > 0; a--)
    {
        result *= a;
    }

    return result;
}

double Matlib::power(double a, unsigned exponent)
{

}

double Matlib::root(double a, unsigned root)
{

}

double Matlib::log(unsigned short base, double a)
{

}

