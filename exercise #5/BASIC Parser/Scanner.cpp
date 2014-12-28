

#include "Scanner.h"


FILE *Scanner::openFile( const char * const path ) const
{
	return fopen( path, "rb" );
}

Scanner::Scanner( const char * const path )
	: file( openFile( path ) )
{
	eof_reached = false;
	line = 1;
	ch = 0;
}

Scanner::~Scanner()
{
	fclose( file );
}

int Scanner::getC()
{

	if ( eof_reached )
	{
		return EOF;
	}

	++ch;

	int c = fgetc( file );

	if ( c == EOF )
	{
		eof_reached = true;
	}

	return c;
}

void Scanner::putC()
{
	fseek( file, ftell( file ) - 1, SEEK_SET );
	ch--;
}

// {Printable}
bool Scanner::isPrintable( int c ) const
{
	return !( c <= 31 || c == 127 );
}

// {String Chars} = {Printable} - ["]
bool Scanner::isStringChars( int c ) const
{
	return isPrintable( c ) && c != '"';
}

// {WS}           = {Whitespace} - {CR} - {LF}
bool Scanner::isWS( int c ) const
{
	return c == ' ' || c == '\t';
}

// {Letter}
bool Scanner::isLetter( int c ) const
{
	return ( 'a' <= c && c <= 'z' ) || ( 'A' <= c && c <= 'Z' );
}

// {digit}
bool Scanner::isDigit( int c ) const
{
	return '0' <= c && c <= '9';
}

const Token *Scanner::nextToken()
{
	char lexeme[ 2048 ];
	int c;
	int i;
	int t_line;
	int t_ch;

	// {String Chars} = {Printable} - ["]
	// {WS}           = {Whitespace} - {CR} - {LF}
	// -----------------------------------------------

	// Whitespace     = {WS}+
	while ( isWS( c = getC() ) );

	if ( c == EOF )
	{
		return new Token( TERMINAL_END_OF_FILE, "$", line, ch );
	}

	// NewLine        = {CR}{LF} | {CR}
	if ( c == CR )
	{
		t_line = line;
		t_ch = ch;
		strcpy( lexeme, "NewLine [CR]" );

		if ( getC() != LF )
		{
			putC();
		}
		else
		{
			strcpy( lexeme, "NewLine [CR][LF]" );
		}

		++line;
		ch = 0;

		return new Token( TERMINAL_NEWLINE, lexeme, t_line, t_ch );
	}

	// String         = '"'{String Chars}*'"' 
	if ( c == '"' )
	{
		t_line = line;
		t_ch = ch;
		lexeme[ 0 ] = '"';
		i = 1;

		while ( isStringChars( c = getC() ) )
		{
			lexeme[ i++ ] = c;
		}

		if ( c != '"' )
		{
			error( "non-printable character in string.", line, ch );

            return NULL;
		}

		lexeme[ i++ ] = '"';
		lexeme[ i ] = '\0';

		return new Token( TERMINAL_STRING, lexeme, t_line, t_ch );
	}

	// Integer        = {digit}+
	// Real           = {digit}+.{digit}+ 
	if ( isDigit( c ) )
	{
		t_line = line;
		t_ch = ch;
		i = 0;

		bool is_real = false;

		while ( isDigit( c ) )
		{
			lexeme[ i++ ] = c;
			c = getC();

			if ( c == '.' && !is_real )
			{
				lexeme[ i++ ] = c;
				c = getC();
				is_real = true;
			}

		}

		putC();
		lexeme[ i ] = '\0';

		return new Token( ( is_real ? TERMINAL_REAL : TERMINAL_INTEGER ), lexeme, t_line, t_ch );
	}
			
	// ID             = {Letter}[$%]?
	if ( isLetter( c ) )
	{
		t_line = line;
		t_ch = ch;
		i = 0;

		while ( isLetter( c ) )
		{
			// "Case Sensitive" = False
			lexeme[ i++ ] = toupper( c );
			c = getC();
		}

		if ( c == '$' || c == '%' )
		{
			lexeme[ i++ ] = c;
		}
		else
		{
			putC();
		}

		lexeme[ i ] = '\0';

		if ( strcmp( lexeme, "REM" ) == 0 )
		{

			if ( !isWS( c = getC() ) )
			{
				error( "REM syntax error.", line, ch );

                return NULL;
			}

			lexeme[ i++ ] = c;

			while ( isPrintable( c = getC() ) )
			{
				lexeme[ i++ ] = c;
			}

			lexeme[ i ] = '\0';
			putC();

			return new Token( TERMINAL_REMARK, lexeme, t_line, t_ch );
		}

		Terminal tn;

             if ( strcmp( lexeme, "CLOSE" )   == 0 ) { tn = TERMINAL_CLOSE;   }
		else if ( strcmp( lexeme, "DATA" )    == 0 ) { tn = TERMINAL_DATA;    }
		else if ( strcmp( lexeme, "DIM" )     == 0 ) { tn = TERMINAL_DIM;     }
		else if ( strcmp( lexeme, "END" )     == 0 ) { tn = TERMINAL_END;     }
		else if ( strcmp( lexeme, "FOR" )     == 0 ) { tn = TERMINAL_FOR;     }
		else if ( strcmp( lexeme, "TO" )      == 0 ) { tn = TERMINAL_TO;      }
		else if ( strcmp( lexeme, "STEP" )    == 0 ) { tn = TERMINAL_STEP;    }
		else if ( strcmp( lexeme, "GOTO" )    == 0 ) { tn = TERMINAL_GOTO;    }
		else if ( strcmp( lexeme, "GOSUB" )   == 0 ) { tn = TERMINAL_GOSUB;   }
		else if ( strcmp( lexeme, "IF" )      == 0 ) { tn = TERMINAL_IF;      }
		else if ( strcmp( lexeme, "THEN" )    == 0 ) { tn = TERMINAL_THEN;    }
		else if ( strcmp( lexeme, "INPUT" )   == 0 ) { tn = TERMINAL_INPUT;   }
		else if ( strcmp( lexeme, "LET" )     == 0 ) { tn = TERMINAL_LET;     }
		else if ( strcmp( lexeme, "NEXT" )    == 0 ) { tn = TERMINAL_NEXT;    }
		else if ( strcmp( lexeme, "OPEN" )    == 0 ) { tn = TERMINAL_OPEN;    }
		else if ( strcmp( lexeme, "AS" )      == 0 ) { tn = TERMINAL_AS;      }
		else if ( strcmp( lexeme, "POKE" )    == 0 ) { tn = TERMINAL_POKE;    }
		else if ( strcmp( lexeme, "PRINT" )   == 0 ) { tn = TERMINAL_PRINT;   }
		else if ( strcmp( lexeme, "READ" )    == 0 ) { tn = TERMINAL_READ;    }
		else if ( strcmp( lexeme, "RETURN" )  == 0 ) { tn = TERMINAL_RETURN;  }
		else if ( strcmp( lexeme, "RESTORE" ) == 0 ) { tn = TERMINAL_RESTORE; }
		else if ( strcmp( lexeme, "RUN" )     == 0 ) { tn = TERMINAL_RUN;     }
		else if ( strcmp( lexeme, "STOP" )    == 0 ) { tn = TERMINAL_STOP;    }
		else if ( strcmp( lexeme, "SYS" )     == 0 ) { tn = TERMINAL_SYS;     }
		else if ( strcmp( lexeme, "WAIT" )    == 0 ) { tn = TERMINAL_WAIT;    }
		else if ( strcmp( lexeme, "OR" )      == 0 ) { tn = TERMINAL_OR;      }
		else if ( strcmp( lexeme, "AND" )     == 0 ) { tn = TERMINAL_AND;     }
		else if ( strcmp( lexeme, "NOT" )     == 0 ) { tn = TERMINAL_NOT;     }
		else                                         { tn = TERMINAL_ID; }
				
		return new Token( tn, lexeme, t_line, t_ch );
	}

	t_line = line;
	t_ch = ch;

	switch ( c )
	{

		case ':': return new Token( TERMINAL_COLON,             ":", t_line, t_ch );
		case '#': return new Token( TERMINAL_NUMBER_SIGN,       "#", t_line, t_ch );
		case '(': return new Token( TERMINAL_LEFT_PARENTHESIS,  "(", t_line, t_ch );
		case ')': return new Token( TERMINAL_RIGHT_PARENTHESIS, ")", t_line, t_ch );
		case '=': return new Token( TERMINAL_EQUAL,             "=", t_line, t_ch );
		case '+': return new Token( TERMINAL_PLUS,              "+", t_line, t_ch );
		case '-': return new Token( TERMINAL_MINUS,             "-", t_line, t_ch );
		case '*': return new Token( TERMINAL_MULTIPLICATION,    "*", t_line, t_ch );
		case '/': return new Token( TERMINAL_DIVISION,          "/", t_line, t_ch );
		case '^': return new Token( TERMINAL_POWER,             "^", t_line, t_ch );
		case ',': return new Token( TERMINAL_COMMA,             ",", t_line, t_ch );
		case ';': return new Token( TERMINAL_SEMICOLON,         ";", t_line, t_ch );

		case '<':
					
			switch ( getC() )
			{

				case '=': return new Token( TERMINAL_LESS_EQUAL, "<=", t_line, t_ch );
				case '>': return new Token( TERMINAL_LESS_NOT_EQUAL, "<>", t_line, t_ch );
				default:
					putC();
					return new Token( TERMINAL_LESS, "<", t_line, t_ch );

			}

		case '>':

			switch ( getC() )
			{

				case '=': return new Token( TERMINAL_GREATER_EQUAL, ">=", t_line, t_ch );
				case '<': return new Token( TERMINAL_GREATER_NOT_EQUAL, "><", t_line, t_ch );
				default:
					putC();
					return new Token( TERMINAL_GREATER, "<", t_line, t_ch );

			}

		default:
			error( "unknown keyword.", t_line, t_ch );
            return NULL;

	}
			
}
