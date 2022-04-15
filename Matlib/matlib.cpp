/**
 * @file matlib.cpp
 * 
 * @author Ondrej Koumar, xkouma02
 * @author Marek Konecny, xkonec85
 * @author Ondrej Lukasek, xlukas15
 * @author Jonas Morkus, xmorku03
 * 
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
        throw invalid_argument("https://www.youtube.com/watch?v=dQw4w9WgXcQ\n");
    }
    return (a / b);
}

unsigned long long Matlib::factorial(unsigned short a)
{
    unsigned long long result = 1;

    if (a > 20)
    {
        // The max val can be 20 because 21! cannot fit to 64 bits
        throw out_of_range("Input number has to be in <0, 20>.\n");
    }

    // 1*a*(a-1)*...*2*1
    while (a > 0)
    {
        result *= a; 
        a--;
    }
    return result;
}

double Matlib::power(double a, unsigned short exponent)
{
    double result = 1;

    if (exponent < 0)
    {
        // Value of exponent can not be negative
        throw out_of_range("The exponent must be equal or greater than 0.\n");
    }
    
    // a*a*...*a
    for (int i = 0; i < exponent; i++)
    {
        result *= a;
    }

    return result;
}

double Matlib::root(double a, unsigned short degree)
{
    // checking for valid values of the given number and degree 
    if (a == 0)
    {
        throw invalid_argument("The degree has to be > 1.\n");
    }
    else if (degree == 1)
    {
        return a;
    }
    else if (a < 0 && degree % 2 == 0)
    {
        throw invalid_argument("There is no solution (in R) for negative numbers and even degree.");
    }

    double epsilon = 0.00000001;
    double iteration_result = a;
    double result = iteration_result + 1; // the value doesnt matter, we just need to begin the while loop

    // newthons method of approximating result by solving differential equation
    while (result - iteration_result > epsilon)
    {
        result = iteration_result;
        // In our case nth root can be written as a^(1/degree),
        // the derivative is (1/degree)*a^(1/degree - 1)
        // and Xk+1 = Xk - f(Xk)/f'(Xk). After the difference between
        // the old and new result is <= epsilon, we can return the result.
        // The simplified equivalent of this particular formula is
        // Xk+1 = Xk - ((Xk^degree) - a)/(degree*(Xk^degree-1))S
        iteration_result = iteration_result - (power(iteration_result, degree) - a) / (degree * power(iteration_result, degree - 1));
    }
    return result;
}

double Matlib::ln(double a)
{   
    // checking for valid value of a given number
    if (a <= 0)
    {
        throw out_of_range("The argument must be positive.\n");
    }

    double result = 0;
    double epsilon = 0.00000001;
    double iteration_result = 1; // the value doesnt matter, we just need to begin the while loop
    unsigned short n = 1; // iterator in infinite series described below

    while (iteration_result > epsilon)
    {
        // An infinite series of approximating natural log,
        // where one iteration is equal to ((x-1)/(x+1)^(2n-1))/(2n-1)
        // and the sum is multiplied by two.
        iteration_result = (power((a-1)/(a+1), 2*n-1) / (2*n - 1));
        result += 2*iteration_result;
        n++;
    }
    return result;
}
