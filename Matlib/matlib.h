/**
 * @file matlib.h
 * @authors Ondrej Koumar (xkouma02), Marek Konecny (xkonec85)
 * @brief 
 */

/**
 * @brief Secte dve cisla, vraci double.
 */
double plus(double a, double b);

/**
 * @brief Odecte dve cisla, vraci double.
 */
double minus(double a, double b);

/**
 * @brief Vynasobi dve cisla, vraci double. 
 */
double mul(double a, double b);

/**
 * @brief Vydeli dve cisla, vraci double.
 */
double div(double a, double b);

/**
 * @brief Vypocita faktorial, vraci unsigned long.
 */
unsigned long factorial(unsigned a);

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
double log(unsigned short base, double num);

