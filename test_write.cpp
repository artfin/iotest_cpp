#include <iostream>
#include <chrono>
#include <fstream>
#include <random>

// for bind
#include <functional>

using namespace std;

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
auto real_rand = bind( uniform_real_distribution<double>(0, 1), mt19937( seed ));

int main( int argc, char* argv[] )
{
    if ( argc != 2 )
    {
        cout << "USAGE: ./... (int) number of random values to be streamed" << endl;
        exit( 1 );
    }

    int n = atoi( argv[1] );

    // ios::out -- open for output operations
    // ios::app -- all output operations are performed at the end of the file
    // ios::binary -- open in binary mode
    ofstream myfile( "example.bin", ios::out | ios::app | ios::binary );

    // checking if opening is successful
    if ( myfile.is_open() )
    {
        for ( int i = 0; i < n; i++ )
        {
            double d = real_rand();
            cout << d << endl;
            myfile.write( (char*) &d, sizeof(double) );
        }
    }

    myfile.close();

    return 0;
}

