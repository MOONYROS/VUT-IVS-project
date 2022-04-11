/**
 * @file matlib.h
 * @authors Ondrej Koumar (xkouma02), Marek Konecny (xkonec85)
 * @brief Header with declarations of Matlib class methods used for calculations in Calculandum Machina.
 */


class Matlib
{
    public:

        /**
         * @brief Adds two numbers, returns double.
         */
        double add(double a, double b);

        /**
         * @brief Subtracts two numbers, returns double.
         */
        double sub(double a, double b);

        /**
         * @brief Multiplies two numbers, returns double.
         */
        double mul(double a, double b);

        /**
         * @brief Divides two numbers, returns double.
         */
        double div(double a, double b);

        /**
         * @brief Calculates factorial of a given number, returns unsigned long long.
         */
        unsigned long long factorial(unsigned short a);

        /**
         * @brief Calculates Nth power of a given number, returns double.
         */
        double power(double a, unsigned short exponent);

        /**
         * @brief Calculates Nth root of a given number with preset precision, returns double.
         */
        double root(double a, unsigned degree);

        /**
         * @brief Calculates common logarithm of a given number with preset precision, returns double.
         */
        double log(double a);
};


