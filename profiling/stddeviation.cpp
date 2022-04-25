/**
 * @file stddeviation.cpp
 *
 * @author Marek Konecny, xkonec85
 * @author Ondrej Koumar, xkouma02
 * @author Ondrej Lukasek, xlukas15
 * @author Jonas Morkus, xmorku03
 *
 * @brief count of deviation using matlib.h
 */
#include "../src/matlib.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

/**
 * @brief aberrance used to calculate profiling.
 * @param file numbers is array of doubles
 * @param numSize is size of array 'numbericons'
 */

double aberrance( double numbers[], int numSize )
{
    Matlib math; //creating a instation of class
    long double sum = 0;
    double tmp = 0;

    for ( int i = 0; i < numSize; i++ )
    {
        //count average
        tmp = numbers[i];
        sum = math.add(sum, tmp);
    }
    double average = math.div(sum,numSize);

    long double sumOfNumbers = 0;

    for ( int j = 0; j < numSize; j++ )
    {
        // sumOfNumbers = sumOfNumbers + (( x - average)^2)
        sumOfNumbers =  math.add( ( math.power( math.sub( numbers[j], average ), 2) ), sumOfNumbers);
    }
    // total = 1 / (N-1) * sumOfNumbers
    double total = 0;
    total = math.mul( sumOfNumbers, math.div( 1, math.sub( numSize, 1 ) ));
    double result = math.root(total, 2);
    return result;
}

//main function - to read numbers from file

int main( int argc, char *argv[])
{
    ifstream file;


    if ( argc != 2 )
    {
        cerr << "there must be 1 argument - file with array of numbers" << endl ;
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
    double array[10000]; // load numbers to this array
    double numSize = 0;
    for ( int i = 0; file >> num ; i++ )
    {
        array[i] = num;
        numSize++;
    }

    double deviation = aberrance( array, numSize);
    cout << deviation << endl;
    return 0;
}
