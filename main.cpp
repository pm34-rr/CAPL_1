#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string uWord;
size_t l;
int N;
vector<string> vs;

int delta( string & s )
{
	size_t count = 0;
	for ( int i = 0, n = min( l, s.size() ); i < n; ++i ) {
		if ( uWord[i] == s[i] )
			++count;
	}
	return s.size() - count;
}


void nearWords()
{
	sort( vs.begin(), vs.end(), []( string & s1, string & s2 ) {
		return delta( s1 ) - delta( s2 );
	} );
}

void readText( const string & path )
{
	ifstream input( path.c_str() );
	string word;
	while ( input >> word )
		vs.push_back( word );
	input.close();
}

void readParamenters()
{
	cout << "Write unique word" << endl;
	cin >> uWord;
	l = uWord.length();
	
	cout << "Write count of words" << endl;
	cin >> N;
}

void makeUnique()
{
	sort( vs.begin(), vs.end() );
	vs.resize( unique( vs.begin(), vs.end() ) - vs.begin() );
}

void writeAnswer()
{
	for ( int i = 0, n = min( vs.size(), N ); i < n; ++i )
		cout << vs.at( i ) << endl;
}

int main()
{
	readParamenters();
	int count = 1;

	ofstream timeOut( "time.txt" );
	for( int i = 0; i < 4; ++i ) {
		string path = "strings" + to_string( count ) + "000000.txt";
		readText( path );
		clock_t beginTime = clock();
		makeUnique();
		nearWords();
		clock_t endTime = clock() - beginTime;
		// writeAnswer();

		output << count << "000000" << ' ' << endTime << endl;
		count *= 2;
		vs.clear();
	}
	timeOut.close();
	return 0;
}
