/**
 * @file matlib.h
 * @authors Ondrej Koumar (xkouma02), Marek Konecny (xkonec85)
 * @brief Header with declarations of Matlib class methods used for calculations in Calculandum Machina.
 */


class Matlib
{
    public:

        /**
         * @brief Secte dve cisla, vraci double.
         */
        double add(double a, double b);

        /**
         * @brief Odecte dve cisla, vraci double.
         */
        double sub(double a, double b);

        /**
         * @brief Vynasobi dve cisla, vraci double. 
         */
        double mul(double a, double b);

        /**
         * @brief Vydeli dve cisla, vraci double.
         */
        double div(double a, double b);

        /**
         * @brief Vypocita faktorial, vraci unsigned long long.
         */
        unsigned long long factorial(unsigned short a);

        /**
         * @brief Umocni prvni operand druhym, vraci double.
         */
        double power(double a, unsigned exponent);

        /**
         * @brief Vypocita obecnou odmocninu cisla, vraci double.
         */
        double root(double a, unsigned root);

        /**
         * @brief Vypocita logaritmus o zvolenem zakladu, vraci double.
         */
        double log(unsigned short base, double a);

};


