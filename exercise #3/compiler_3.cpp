
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

#define CR 13
#define LF 10

enum TokenName {
	  TN_ID					//
	, TN_STRING				//
	, TN_INTEGER			//
	, TN_REAL				//
	, TN_COLON				//
	, TN_SHARP				//
	, TN_OPEN_PARENTHESIS	//
	, TN_CLOSE_PARENTHESIS
	, TN_ASSIGN
	, TN_COMMA
	, TN_SEMICOLON
	, TN_NOT_EQUAL
	, TN_GREATER
	, TN_GREATER_OR_EQUAL
	, TN_LESSER
	, TN_LESSER_OR_EQUAL
	, TN_PLUS
	, TN_MINUS
	, TN_SLASH
	, TN_ASTERISK
	, TN_CARET
	, TN_NEW_LINE			//
	, TN_END				//
};

class Token {
	private:
		TokenName token_name;
		int attribute_value;

	public:
		Token( const Token &tok )
		{
			token_name = tok.token_name;
			attribute_value = tok.attribute_value;
		}

		~Token() {}

		Token( TokenName tn, int av )
		{
			token_name = tn;
			attribute_value = av;
		}

		TokenName getTokenName() { return token_name; }

		int getAttributeValue() { return attribute_value; }
};

class SymbolTableEntry {
	private:
		char *lexeme;
	
	public:
		SymbolTableEntry( const SymbolTableEntry &ste )
		{
			lexeme = new char [ strlen( ste.lexeme ) + 1 ];
			strcpy( lexeme, ste.lexeme );
		}

		~SymbolTableEntry()
		{
			delete [] lexeme;
		}

		SymbolTableEntry( char *lxm )
		{
			lexeme = new char [ strlen( lxm ) + 1 ];
			strcpy( lexeme, lxm );
		}

		char *getLexeme()
		{
			char *lxm = new char [ strlen( lexeme ) + 1 ];
			strcpy( lxm, lexeme );

			return lxm;
		}

};

class SymbolTable {
	private:
		int idx;
		SymbolTableEntry **table;
		static const int size = 2048;

	public:
		SymbolTable( const SymbolTable &st )
		{
			idx = st.idx;
			table = new SymbolTableEntry *[ size ];

			for ( int i = 0; i < idx; ++i )
			{
				table[ i ] = new SymbolTableEntry( *st.table[ i ] );
			}

		}

		~SymbolTable()
		{

			for ( int i = 0; i < idx; ++i )
			{

				if ( table[ i ] ==  0 )
				{
					continue;
				}

				delete table[ i ];
			}

			delete [] table;
		}

		SymbolTable()
		{
			idx = 0;
			table = new SymbolTableEntry* [ size ];
		}

		int add( SymbolTableEntry *ste )
		{
			char *lxm = ste->getLexeme();
			int fdx;

			if ( fdx = find( lxm ) )
			{
				delete lxm;
				return fdx;
			}

			delete lxm;

			table[ idx ] = new SymbolTableEntry( *ste );
			++idx;
		}

		SymbolTableEntry *get( int index )
		{
			return new SymbolTableEntry( *table[ index ] );
		}

		int find( char *lexeme )
		{

			for ( int i = 0; i < idx; ++i )
			{
				char *lxm = table[ i ]->getLexeme();

				if ( strcmp( lxm, lexeme ) == 0 )
				{
					delete lxm;

					return i;
				}

				delete lxm;

				continue;
			}

			return -1;
		}

};

class LexicalAnalyser {
	private:
		FILE *file;
		SymbolTable *st;
		bool is_put_back;
		char put_back;

	public:
		LexicalAnalyser( char *f )
		{
			file = fopen( f, "rb" );
			st = new SymbolTable();
			is_put_back = false;
		}

		int getc()
		{
			char c;

			if ( is_put_back )
			{
				c = put_back;
				is_put_back = false;
			}
			else
			{
				c = fgetc( file );
				put_back = c;
			}

			return c;
		}

		int putc() { is_put_back = true; }

		bool isWhitespace( char c ) { return c == ' ' || c == '\t'; }

		bool isLetter( char c )	{ return ( 'a' <= c && c <= 'z' ) || ( 'A' <= c && c <= 'Z' ); }

		Token *nextToken()
		{
			char c;
			char lexeme[ 2048 ];
			int i;

			// {String Chars} = {Printable} - ["]
			// {WS}           = {Whitespace} - {CR} - {LF}
			// =----------------------------------------------

			// Whitespace     = {WS}+
			while ( isWhitespace( c = getc() ) );

			if ( c == EOF )
			{
				return new Token( TN_END, -1 );
			}

			// NewLine        = {CR}{LF}|{CR}
			if ( c == CR )
			{

				if ( getc() != LF )
				{
					putc();
				}

				return new Token( TN_NEW_LINE, -1 );
			}

			// String         = '"'{String Chars}*'"' 
			if ( c == '"' )
			{
				lexeme[ 0 ] = '"';
				i = 1;

				while ( ( c = getc() ) != '"' )
				{
					lexeme[ i++ ] = c;
				}

				lexeme[ i++ ] = '"';
				lexeme[ i ] = '\0';

				SymbolTableEntry *ste = new SymbolTableEntry( lexeme );
				Token *token = new Token( TN_STRING, st->add( ste ) );

				delete ste;

				return token;
			}

			// Integer        = {digit}+
			// Real           = {digit}+.{digit}+ 
			if ( '0' <= c && c <= '9' )
			{
				bool is_real = false;
				i = 0;

				while ( '0' <= c && c <= '9' )
				{
					lexeme[ i++ ] = c;
					c = getc();

					if ( c == '.' )
					{
						c = getc();
						is_real = true;
					}

				}

				putc();
				lexeme[ i ] = '\0';

				SymbolTableEntry *ste = new SymbolTableEntry( lexeme );
				Token *token = new Token( ( is_real ? TN_REAL : TN_INTEGER ), st->add( ste ) );

				delete ste;

				return token;
			}
			
			// ID             = {Letter}[$%]?
			if ( isLetter( c ) )
			{
				i = 0;

				while ( isLetter( c ) )
				{
					lexeme[ i++ ] = c;
					c = getc();
				}

				if ( c == '$' || c == '%' )
				{
					lexeme[ i++ ] = c;
				}
				else
				{
					putc();
				}

				lexeme[ i ] = '\0';

				SymbolTableEntry *ste = new SymbolTableEntry( lexeme );
				Token *token = new Token( TN_ID, st->add( ste ) );

				delete ste;

				return token;
			}

			switch ( c )
			{

				case ':': return new Token( TN_COLON, -1 );
				case '#': return new Token( TN_SHARP, -1 );
				case '(': return new Token( TN_OPEN_PARENTHESIS, -1 );
				case ')': return new Token( TN_CLOSE_PARENTHESIS, -1 );
				case '=': return new Token( TN_ASSIGN, -1 );
				case ',': return new Token( TN_COMMA, -1 );
				case ';': return new Token( TN_SEMICOLON, -1 );
				case '+': return new Token( TN_PLUS, -1 );
				case '-': return new Token( TN_MINUS, -1 );
				case '/': return new Token( TN_SLASH, -1 );
				case '*': return new Token( TN_ASTERISK, -1 );
				case '^': return new Token( TN_CARET, -1 );

				case '<':

					switch ( getc() )
					{

						case '=': return new Token( TN_LESSER_OR_EQUAL, -1 );
						case '>': return new Token( TN_NOT_EQUAL, -1 );

						default:
							putc();
							return new Token( TN_LESSER, -1 );

					}

					break;

				case '>':

					switch ( getc() )
					{

						case '=': return new Token( TN_GREATER_OR_EQUAL, -1 );
						case '<': return new Token( TN_NOT_EQUAL, -1 );

						default:
							putc();
							return new Token( TN_GREATER, -1 );

					}

					break;

			}
			
		}

};

int main()
{
	LexicalAnalyser *la = new LexicalAnalyser( "basic.bsc" );
	Token *t;

	while ( ( t = la->nextToken() )->getTokenName() != TN_END )
	{
	}

	return EXIT_SUCCESS;
}
