

#include "Token.h"


const char *Token::genLexeme( const char *str ) const
{
	char * const s = new char [ strlen( str ) + 1 ];

	strcpy( s, str );
	return s;
}

Token::Token( const Terminal &tn, const char *lex,
              const int &Ln, const int &ch )
	: name( tn ), lexeme( genLexeme( lex ) ), line( Ln ), Ch( ch )
{ }

Token::~Token()
{
	delete [] lexeme;
}
