

#include <cstdlib>

#include "Parser.h"


Scanner *scan;

void error( const char * const msg, const int &line, const int &ch )
{
    printf( "Ln: %d - Ch: %d: %s\n", line, ch, msg );
}

int main( int argc, char **argv )
{
    scan = new Scanner( "basic1.bas" );
    //scan = new Scanner( "basic2.bas" );
    //scan = new Scanner( "basic3.bas" );
    //scan = new Scanner( "basic4.bas" );
    Parser::parse( scan );
	system( "pause" );

	return EXIT_SUCCESS;
}
