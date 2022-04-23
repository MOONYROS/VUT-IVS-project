/**
 * @file aberrance.cpp
 *
 * @author Marek Konecny, xkonec85
 * @author Ondrej Koumar, xkouma02
 * @author Ondrej Lukasek, xlukas15
 * @author Jonas Morkus, xmorku03
 *
 * @brief Profiling - aberrance.
 */
#include "../Matlib/matlib.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

/**
 * @brief aberrance used to calculate profiling. 
 * @param file numbericons is array of doubles
 * @param numSize is size of array 'numbericons'
 */

double aberrance( double numbericons[], int numSize )
{
    long double sum = 0;

    for ( int i = 0; i < numSize; i++ )
    {
        //average
        double tmpSum = 0;
        tmpSum = numbericons[i];
        sum = Matlib::add(sum, tmpSum);
    }
    double average = Matlib::div(sum,numSize);

    long double sumOfNumbers = 0;

    for ( int j = 0; j < numSize; j++ )
    {
        // sumOfNumbers = sumOfNumbers + (( x - average)^2)
        sumOfNumbers =  Matlib::add( ( Matlib::power( Matlib::sub( numbericons[j], average ), 2) ), sumOfNumbers);
    }
    // total = 1 / (N-1) * sumOfNumbers
    double total = 0;
    total = Matlib::mul( sumOfNumbers, Matlib::div( 1, Matlib::sub( numSize, 1 ) ));
    return Matlib::root(total, 2);
}

//main function - to read numbers from file

int main( int argc, char *argv[])
{
    ifstream file;


    if ( argc != 2 )
    {
        cerr << "Program expected only ONE argument!" << endl ;
        return 0;
    }
    else
    {
        char *fileNum = argv[1];
        file.open( fileNum, ifstream::in );
        if ( !file.is_open() ) //for case program can not open a file
        {
            throw new std::runtime_error("Failed to open file");
            return 0;
        }
    }
    double num;
    double array[10000];

    for ( int i = 0; file >> num ; i++ )
    {
        array[i] = num;
    }

    double aberrance = aberrance( array, i);
    cout << aberrance << endl;
    return 0;
}
