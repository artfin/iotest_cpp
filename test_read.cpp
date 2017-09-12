#include <iostream>
#include <fstream>

using namespace std;

int main( int argc, char* argv[] )
{
    if ( argc != 2 )
    {
        cout << "USAGE: ./... (int) number of parsed values to be displayed" << endl;
        exit( 1 );
    }

    int n = atoi( argv[1] );

    ifstream file( "example.bin", ios::in | ios::binary | ios::ate );

    streampos size = file.tellg();

    cout << "size = " << size << endl;

    char* memblock = new char [size];
    file.seekg( 0, ios::beg );
    file.read( memblock, size );
    file.close();

    cout << "The entire file content is in memory" << endl;
    double* double_values = (double*) memblock;

    for ( int i = 0; i < n; i++ )
    {
        cout << double_values[i] << endl;
    }

    return 0;
}
