#include <fstream>
#include <chrono>
#include <vector>
#include <cstdint>
#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

vector<uint64_t> GenerateData( size_t bytes )
{
	assert( bytes % sizeof(uint64_t) == 0 );

	vector<uint64_t> data( bytes / sizeof(uint64_t));
	iota( data.begin(), data.end(), 0 );
	shuffle( data.begin(), data.end(), mt19937{random_device{}() });
	
	return data;
}

long long option_1( size_t bytes )
{
	vector<uint64_t> data = GenerateData( bytes );

	auto startTime = chrono::high_resolution_clock::now();

	auto myfile = fstream("file.binary", ios::out | ios::binary);
	myfile.write( (char*)&data[0], bytes );
	myfile.close();

	auto endTime = chrono::high_resolution_clock::now();

	return chrono::duration_cast<chrono::milliseconds>( endTime - startTime ).count();
}

long long option_2( size_t bytes )
{
	vector<uint64_t> data = GenerateData( bytes );

	auto startTime = chrono::high_resolution_clock::now();
	
	FILE* file = fopen("file.binary", "wb");
	fwrite( &data[0], 1, bytes, file );
	fclose( file );

	auto endTime = chrono::high_resolution_clock::now();

	return chrono::duration_cast<chrono::milliseconds>( endTime - startTime ).count();
}

long long option_3( size_t bytes )
{
	vector<uint64_t> data = GenerateData( bytes );
	
	ios_base::sync_with_stdio( false );
	
	auto startTime = chrono::high_resolution_clock::now();

	auto myfile = fstream("file.binary", ios::out | ios::binary);
	myfile.write( (char*)&data[0], bytes );
	myfile.close();

	auto endTime = chrono::high_resolution_clock::now();

	return chrono::duration_cast<chrono::milliseconds>( endTime - startTime ).count();
}

int main()
{
	const size_t kB = 1024;
	const size_t MB = 1024 * kB;
	const size_t GB = 1024 * MB;
	
	for ( size_t size = 1 * MB; size <= 1 * GB; size *= 2)
	{
		cout << "option_1, " << size / MB << " MB: " << option_1( size ) << " ms" << endl;
	}

	for ( size_t size = 1 * MB; size <= 1 * GB; size *= 2 )
	{
		cout << "option_2, " << size / MB << " MB: " << option_2( size ) << "ms" << endl;
	}

	for ( size_t size = 1 * MB; size <= 1 * GB; size *= 2)
	{
		cout << "option_3, " << size / MB << " MB: " << option_3( size ) << " ms" << endl;
	}

	return 0;
}
