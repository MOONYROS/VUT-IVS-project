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
        throw out_of_range("Input number has to be in <0, 20>.");
    }

    // 1*a*(a-1)*...*2*1
    for (a; a > 0; a--)
    {
        result *= a;
    }

    return result;
}

double Matlib::power(double a, unsigned short exponent)
{
    double result = 1;

    if (exponent < 0)
    {
        // Value of exponent can not be negative
        throw out_of_range("The exponent must be equal or greater than 0.");
    }

    for (int i = 0; i < exponent; i++)
    {
        result *= a;
    }

    return result;
}

double Matlib::root(double a, unsigned degree)
{
    double result = 1;
    double tmp = 1;
    double epsilon = 0.00000001;
    
    if (degree <= 0)
    {
        // Value of exponent can not be negative
        throw out_of_range("The degree must be positive.");
    }
    else if (a == 0)
    {
        return 0;
    }
    else if (degree == 1)
    {
        return a;
    }
    else if (a < 0 && degree % 2 == 0)
    {
        throw invalid_argument("Root of negative number with even degree doesnt exist (in real numbers).");
    }

    while (tmp > epsilon || tmp < -epsilon)
    {
        tmp = (a / power(result, degree - 1) - result) / degree;
        result += tmp;
    }

    return result;
}

double Matlib::log(double a)
{
    double result = 1;
    double tmp = 1;
    double epsilon = 0.00000001;

    if (a <= 0)
    {
        throw out_of_range("The argument must be positive.");
    }

    int x = 2;

    if (a >= 1)
    {
        tmp = (a - 1) / a;
        result = tmp;

        while (tmp > epsilon || tmp < -epsilon)
        {
            tmp *=  (a - 1) * (x - 1) / (a * x);
            result += tmp;
            x++;
        }
    }
    else
    {
        a = 1 - a;
        tmp = -a;
        result = tmp;

        while (tmp > epsilon or tmp < -epsilon)
        {
            tmp *= (x - 1) * a / x;
            result += tmp;
            x++;
        }
    }

    return result;
}
