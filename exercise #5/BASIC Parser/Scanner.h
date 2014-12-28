

#include <cstdio>
#include <cstring>
#include <cctype>

#include "Token.h"


using namespace std;


#define CR 13
#define LF 10

void error( const char * const, const int &, const int & );

class Scanner {
	private:
		FILE * const file;
		bool eof_reached;
		int line;
		int ch;

		FILE *openFile( const char * const path ) const;

	public:
		Scanner( const char * const path );
		~Scanner();

	private:
		int getC();
		void putC();

		// {Printable}
		bool isPrintable( int c ) const;

		// {String Chars} = {Printable} - ["]
		bool isStringChars( int c ) const;

		// {WS}           = {Whitespace} - {CR} - {LF}
		bool isWS( int c ) const;

		// {Letter}
		bool isLetter( int c ) const;

		// {digit}
		bool isDigit( int c ) const;

	public:
		const Token *nextToken();

};

