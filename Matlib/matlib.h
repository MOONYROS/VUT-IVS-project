/**
 * @file matlib.h
 * 
 * @author Ondrej Koumar, xkouma02
 * @author Marek Konecny, xkonec85
 * @author Ondrej Lukasek, xlukas15
 * @author Jonas Morkus, xmorku03
 * 
 * @brief Header with declarations of Matlib class methods 
 * used for calculations in Calculandum Machina.
 * The functions are addiction, subtraction, multiplication,
 * division, factorial, nth power, nth root and natural logarithm.
 */

#ifndef matlib.h

class Matlib
{
    public:

        /**
         * @brief Adds two numbers.
         * @return Sum, double precision float.
         */
        double add(double a, double b);

        /**
         * @brief Subtracts two numbers.
         * @return Difference, double precision float.
         */
        double sub(double a, double b);

        /**
         * @brief Multiplies two numbers.
         * @return Product, double precision float.
         */
        double mul(double a, double b);

        /**
         * @brief Divides two numbers.
         * @return Quotient, double precision float.
         */
        double div(double a, double b);

        /**
         * @brief Calculates factorial of a given number.
         * @return Factorial, unsigned long long integer.
         */
        unsigned long long factorial(unsigned short a);

        /**
         * @brief Calculates Nth power of a given number.
         * @return Power, double precision float.
         */
        double power(double a, unsigned short exponent);

        /**
         * @brief Calculates Nth root of a given number.
         * @return Root, double precision float (preset with epsilon = 10e-8).
         */
        double root(double a, unsigned short degree);

        /**
         * @brief Calculates natural logarithm of a given number.
         * @return Logarithm, double precision float (preset with epsilon = 10e-8).
         */
        double ln(double a);
};

#endif
