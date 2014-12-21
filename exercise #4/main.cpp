
/*
Grammar:
	1) E -> E+T
	2) E -> E-T
	3) E -> T
	4) T -> T*F
	5) T -> T/F
	6) T -> F
	7) F -> {NUM}
	8) F -> (E)

Augmented Grammar:
	0) S -> E
	1) E -> E+T
	2) E -> E-T
	3) E -> T
	4) T -> T*F
	5) T -> T/F
	6) T -> F
	7) F -> {NUM}
	8) F -> (E)

FIRST and FOLLOW:
	FIRST(S) = FIRST(E) = {{NUM}, (}
	FIRST(E) = FIRST(T) = {{NUM}, (}
	FIRST(T) = FIRST(F) = {{NUM}, (}
	FIRST(F)            = {{NUM}, (}

	FOLLOW(S) = {$}
	FOLLOW(E) = FOLLOW(S) U FIRST(+) U FIRST(-) U FIRST()) = {$, +, -, )}
	FOLLOW(T) = FOLLOW(E) U FIRST(*) U FIRST(/)            = {$, +, -, ), *, /}
	FOLLOW(F) = FOLLOW(T)                                  = {$, +, -, ), *, /}

LR(0) automaton:

	*-------------*
	|    (I0)     |
	| S -> .E     |--<E>--> (I1)
	|-------------|
	| E -> .E+T   |
	| E -> .E-T   |
	| E -> .T     |--<T>--> (I2)
	| T -> .T*F   |
	| T -> .T/F   |
	| T -> .F     |--<F>--> (I3)
	| F -> .{NUM} |--<{NUM}>--> (I4)
	| F -> .(E)   |--<(>--> (I5)
	*-------------*

	*-------------*
	|    (I1)     |
	| S -> E.     |--<FOLLOW(S) = {$}>--> (r0 = ACCEPT)
	| E -> E.+T   |--<+>--> (I6)
	| E -> E.-T   |--<->--> (I7)
	*-------------*

	*-------------*
	|    (I2)     |
	| E -> T.     |--<FOLLOW(E) = {$, +, -, )}>--> (r3)
	| T -> T.*F   |--<*>--> (I8)
	| T -> T./F   |--</>--> (I9)
	*-------------*

	*-------------*
	|    (I3)     |
	| T -> F.     |--<FOLLOW(T) = {$, +, -, ), *, /}>--> (r6)
	*-------------*

	*-------------*
	|    (I4)     |
	| F -> {NUM}. |--<FOLLOW(F) = {$, +, -, ), *, /}>--> (r7)
	*-------------*

	*-------------*
	|    (I5)     |
	| F -> (.E)   |--<E>--> (I10)
	|-------------|
	| E -> .E+T   |
	| E -> .E-T   |
	| E -> .T     |--<T>--> (I2)
	| T -> .T*F   |
	| T -> .T/F   |
	| T -> .F     |--<F>--> (I3)
	| F -> .{NUM} |--<{NUM}>--> (I4)
	| F -> .(E)   |--<(>--> (I5)
	*-------------*

	*-------------*
	|    (I6)     |
	| E -> E+.T   |--<T>--> (I11)
	|-------------|
	| T -> .T*F   |
	| T -> .T/F   |
	| T -> .F     |--<F>--> (I3)
	| F -> .{NUM} |--<{NUM}>--> (I4)
	| F -> .(E)   |--<(>--> (I5)
	*-------------*

	*-------------*
	|    (I7)     |
	| E -> E-.T   |--<T>--> (I12)
	|-------------|
	| T -> .T*F   |
	| T -> .T/F   |
	| T -> .F     |--<F>--> (I3)
	| F -> .{NUM} |--<{NUM}>--> (I4)
	| F -> .(E)   |--<(>--> (I5)
	*-------------*

	*-------------*
	|    (I8)     |
	| T -> T*.F   |--<F>--> (I13)
	|-------------|
	| F -> .{NUM} |--<{NUM}>--> (I4)
	| F -> .(E)   |--<(>--> (I5)
	*-------------*

	*-------------*
	|    (I9)     |
	| T -> T/.F   |--<F>--> (I14)
	|-------------|
	| F -> .{NUM} |--<{NUM}>--> (I4)
	| F -> .(E)   |--<(>--> (I5)
	*-------------*

	*-------------*
	|    (I10)    |
	| F -> (E.)   |--<)>--> (I15)
	| E -> E.+T   |--<+>--> (I6)
	| E -> E.-T   |--<->--> (I7)
	*-------------*

	*-------------*
	|    (I11)    |
	| E -> E+T.   |--<FOLLOW(E) = {$, +, -, )}>--> (r1)
	| T -> T.*F   |--<*>--> (I8)
	| T -> T./F   |--</>--> (I9)
	*-------------*

	*-------------*
	|    (I12)    |
	| E -> E-T.   |--<FOLLOW(E) = {$, +, -, )}>--> (r2)
	| T -> T.*F   |--<*>--> (I8)
	| T -> T./F   |--</>--> (I9)
	*-------------*

	*-------------*
	|    (I13)    |
	| T -> T*F.   |--<FOLLOW(T) = {$, +, -, ), *, /}>--> (r4)
	*-------------*

	*-------------*
	|    (I14)    |
	| T -> T/F.   |--<FOLLOW(T) = {$, +, -, ), *, /}>--> (r5)
	*-------------*

	*-------------*
	|    (I15)    |
	| F -> (E).   |--<FOLLOW(F) = {$, +, -, ), *, /}>--> (r8)
	*-------------*

SLR-parsing table:

	================================================================================================
	       |                            ACTION                             ||         GOTO          
	 STATE |---------------------------------------------------------------||-----------------------
	       | {NUM} |   +   |   -   |   *   |   /   |   (   |   )   |   $   ||   E   |   T   |   F   
	=======|=======|=======|=======|=======|=======|=======|=======|=======||=======|=======|=======
	   0   |  s4   |  e1   |  e1   |  e1   |  e1   |  s5   |  e2   |  e1   ||   1   |   2   |   3   
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	   1   |  e3   |  s6   |  s7   |       |       |  e3   |  e2   |  acc  ||       |       |       
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	   2   |  r3   |  r3   |  r3   |  s8   |  s9   |  r3   |  r3   |  r3   ||       |       |       
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	   3   |  r6   |  r6   |  r6   |  r6   |  r6   |  r6   |  r6   |  r6   ||       |       |       
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	   4   |  r7   |  r7   |  r7   |  r7   |  r7   |  r7   |  r7   |  r7   ||       |       |       
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	   5   |  s4   |  e1   |  e1   |  e1   |  e1   |  s5   |  e2   |  e1   ||  10   |   2   |   3   
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	   6   |  s4   |  e1   |  e1   |  e1   |  e1   |  s5   |  e2   |  e1   ||       |  11   |   3   
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	   7   |  s4   |  e1   |  e1   |  e1   |  e1   |  s5   |  e2   |  e1   ||       |  12   |   3   
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	   8   |  s4   |  e1   |  e1   |  e1   |  e1   |  s5   |  e2   |  e1   ||       |       |  13   
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	   9   |  s4   |  e1   |  e1   |  e1   |  e1   |  s5   |  e2   |  e1   ||       |       |  14   
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	  10   |  e3   |  s6   |  s7   |       |       |  e3   |  s15  |  e4   ||       |       |       
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	  11   |  r1   |  r1   |  r1   |  s8   |  s9   |  r1   |  r1   |  r1   ||       |       |       
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	  12   |  r2   |  r2   |  r2   |  s8   |  s9   |  r2   |  r2   |  r2   ||       |       |       
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	  13   |  r4   |  r4   |  r4   |  r4   |  r4   |  r4   |  r4   |  r4   ||       |       |       
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	  14   |  r5   |  r5   |  r5   |  r5   |  r5   |  r5   |  r5   |  r5   ||       |       |       
	-------|-------|-------|-------|-------|-------|-------|-------|-------||-------|-------|-------
	  15   |  r8   |  r8   |  r8   |  r8   |  r8   |  r8   |  r8   |  r8   ||       |       |       
	------------------------------------------------------------------------------------------------

	e1: expected operand ({num} or '(') but found operator (or end input)
	    assume that an operand was missed in input.

	e2: expected operand ({num} or '(') but found unbalanced right parenthesis ')'
	    assume that this parenthesis was redundant and remove from input

	e3: expected operator (+, -, *, or /) but found an operand ({NUM} or '(')
	    assume that an operator was missed in input.

	e2: expected right parenthesis ')' but end of input reached
	    assume that a right parenthesis was missed.

*/

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <stack>

#define Byte char
#define BytePtr const char * const

using namespace std;

const char *head;// = "24  +\t56   *\n63";
int line = 1;
int col = 1;

enum Terminal
{
	TERMINAL_NUM = 0,
	TERMINAL_ADD,
	TERMINAL_SUB,
	TERMINAL_MUL,
	TERMINAL_DIV,
	TERMINAL_OPEN_PARENTHESIS,
	TERMINAL_CLOSE_PARENTHESIS,
	TERMINAL_END
};

enum NonTerminal
{
	NONTERMINAL_E = 0,
	NONTERMINAL_T,
	NONTERMINAL_F
};

BytePtr ac = new Byte[] { 'a' };

BytePtr s4 = new Byte[] { 's', 4 };
BytePtr s6 = new Byte[] { 's', 6 };
BytePtr s5 = new Byte[] { 's', 5 };
BytePtr s7 = new Byte[] { 's', 7 };
BytePtr s8 = new Byte[] { 's', 8 };
BytePtr s9 = new Byte[] { 's', 9 };
BytePtr sf = new Byte[] { 's', 15 };

BytePtr r1 = new Byte[] { 'r', 1 };
BytePtr r2 = new Byte[] { 'r', 2 };
BytePtr r3 = new Byte[] { 'r', 3 };
BytePtr r4 = new Byte[] { 'r', 4 };
BytePtr r5 = new Byte[] { 'r', 5 };
BytePtr r6 = new Byte[] { 'r', 6 };
BytePtr r7 = new Byte[] { 'r', 7 };
BytePtr r8 = new Byte[] { 'r', 8 };

BytePtr e1 = new Byte[] { 'e', 1 };
BytePtr e2 = new Byte[] { 'e', 2 };
BytePtr e3 = new Byte[] { 'e', 3 };
BytePtr e4 = new Byte[] { 'e', 4 };

BytePtr ACTION[ 16 ][ 8 ]
//	      NU  +   -   *   /   (   )   $
	= { { s4, e1, e1, e1, e1, s5, e2, e1 },	// 0
		{ e3, s6, s7,  0,  0, e3, e2, ac },	// 1
		{ e3, r3, r3, s8, s9, e3, r3, r3 },	// 2
		{ e3, r6, r6, r6, r6, e3, r6, r6 },	// 3
		{ e3, r7, r7, r7, r7, e3, r7, r7 },	// 4
		{ s4, e1, e1, e1, e1, s5, e2, e1 },	// 5
		{ s4, e1, e1, e1, e1, s5, e2, e1 },	// 6
		{ s4, e1, e1, e1, e1, s5, e2, e1 },	// 7
		{ s4, e1, e1, e1, e1, s5, e2, e1 },	// 8
		{ s4, e1, e1, e1, e1, s5, e2, e1 },	// 9
		{ e3, s6, s7,  0,  0, e3, sf, e4 },	// 10
		{ e3, r1, r1, s8, s9, e3, r1, r1 },	// 11
		{ e3, r2, r2, s8, s9, e3, r2, r2 },	// 12
		{ e3, r4, r4, r4, r4, e3, r4, r4 },	// 13
		{ e3, r5, r5, r5, r5, e3, r5, r5 },	// 14
		{ e3, r8, r8, r8, r8, e3, r8, r8 } };	// 15

Byte GOTO[ 16 ][ 3 ]
//	       E   T   F
	= { {  1,  2,  3 },		// 0
		{  0,  0,  0 },		// 1
		{  0,  0,  0 },		// 2
		{  0,  0,  0 },		// 3
		{  0,  0,  0 },		// 4
		{ 10,  2,  3 },		// 5
		{  0, 11,  3 },		// 6
		{  0, 12,  3 },		// 7
		{  0,  0, 13 },		// 8
		{  0,  0, 14 },		// 9
		{  0,  0,  0 },		// 10
		{  0,  0,  0 },		// 11
		{  0,  0,  0 },		// 12
		{  0,  0,  0 },		// 13
		{  0,  0,  0 },		// 14
		{  0,  0,  0 } };	// 15

void error( char *message, int line, int col )
{
	printf( "ERROR L %d - C %d: %s\n", line, col, message );
}

class Token
{
	public:
		Terminal t_name;
		char *t_val;
		int t_line;
		int t_col;

		Token( Terminal name, const char *val, int len, int line, int col )
		{
			t_name = name;
			t_val = new char [ len + 1 ];
			strncpy( t_val, val, len );
			t_val[ len ] = '\0';
			t_line = line;
			t_col = col;
		}

		~Token() { delete [] t_val; }

};

Token *nextToken()
{

	while ( *head == ' ' || *head == '\r' || *head == '\n' || *head == '\t' )
	{

		if ( *head == ' ' || *head == '\t' )
		{
			++col;
		}
		else if ( *head == '\n' )
		{
			++line;
			col = 1;
		}

		++head;
	}

	const char *s_i = head;
	int next_col = col;

	while ( '0' <= *head && *head <= '9' )
	{
		++head;
		++next_col;
	}

	if ( s_i != head )
	{
		Token *t = new Token( TERMINAL_NUM, s_i, head - s_i, line, col );

		col = next_col;

		return t;
	}

	Terminal tn;

	switch ( *head )
	{

		case '+':
			tn = TERMINAL_ADD;
			break;

		case '-':
			tn = TERMINAL_SUB;
			break;

		case '*':
			tn = TERMINAL_MUL;
			break;

		case '/':
			tn = TERMINAL_DIV;
			break;

		case '(':
			tn = TERMINAL_OPEN_PARENTHESIS;
			break;

		case ')':
			tn = TERMINAL_CLOSE_PARENTHESIS;
			break;

		case '\0':
		case '$':
			tn = TERMINAL_END;
			break;

		default:
			error( "unknown symbol.", line, col );
			++head;
			++col;
			return nextToken();

	}

	++head;
	++col;

	return new Token( tn, head - 1, 1, line, col );
}

void parse()
{
	stack< int > stk;
	const Byte *ACTION_s_a;
	Terminal a;
	int s;
	int t;

	NonTerminal A;
	int len_B;

	stk.push( 0 );

	Token *token = nextToken();

	while ( true )
	{
		a = token->t_name;
		s = stk.top();
		ACTION_s_a = ACTION[ s ][ a ];

		if ( ACTION_s_a[ 0 ] == 0 )
		{
			error( "syntax error.", token->t_line, token->t_col );
			break;
		}
		else if ( ACTION_s_a[ 0 ] == 's' )
		{
			t = ACTION_s_a[ 1 ];
			stk.push( t );
			delete token;
			token = nextToken();
		}
		else if ( ACTION_s_a[ 0 ] == 'r' )
		{

			switch ( ACTION_s_a[ 1 ] )
			{

				case 1:
					A = NONTERMINAL_E;
					len_B = 3;
					printf( "E -> E+T\n" );
					break;

				case 2:
					A = NONTERMINAL_E;
					len_B = 3;
					printf( "E -> E-T\n" );
					break;

				case 3:
					A = NONTERMINAL_E;
					len_B = 1;
					printf( "E -> T\n" );
					break;

				case 4:
					A = NONTERMINAL_T;
					len_B = 3;
					printf( "T -> T*F\n" );
					break;

				case 5:
					A = NONTERMINAL_T;
					len_B = 3;
					printf( "T -> T/F\n" );
					break;

				case 6:
					A = NONTERMINAL_T;
					len_B = 1;
					printf( "T -> F\n" );
					break;

				case 7:
					A = NONTERMINAL_F;
					len_B = 1;
					printf( "F -> {NUM}\n" );
					break;

				case 8:
					A = NONTERMINAL_F;
					len_B = 1;
					printf( "F -> (E)\n" );
					break;

			}

			for ( int i = 1; i <= len_B; ++i )
			{
				stk.pop();
			}

			t = stk.top();
			stk.push( GOTO[ t ][ A ] );
		}
		else if ( ACTION_s_a[ 0 ] == 'e' )
		{

			switch ( ACTION_s_a[ 1 ] )
			{

				case 1:
					error( "missing operand.", token->t_line, token->t_col );
					stk.push( 4 );
					break;

				case 2:
					error( "unbalanced right parenthesis.", token->t_line, token->t_col );
					delete token;
					token = nextToken();
					break;

				case 3:
					error( "missing operator.", token->t_line, token->t_col );
					stk.push( 6 );
					break;

				case 4:
					error( "missing right parenthesis.", token->t_line, token->t_col );
					stk.push( 15 );
					break;

			}

		}
		else if ( ACTION_s_a[ 0 ] == 'a' )
		{
			printf( "success...\n" );
			break;
		}
		else
		{
			error( "syntax error.", token->t_line, token->t_col );
			break;
		}

	}

}

int main( int argc, char **argv )
{
	argv[ 1 ] = "input.txt";

	// read from file =================
	FILE *f = fopen( argv[ 1 ], "rb" );
	char *content;
	long count;

	fseek( f, 0, SEEK_END );
	count = ftell( f );
	fseek( f, 0, SEEK_SET );
	content = new char [ count + 1 ];
	fread( content, sizeof( char ), count, f );
	content[ count ] = '\0';
	fclose( f );
	// ================================

	head = content;
	parse();
	system( "pause" );

	return EXIT_SUCCESS;
}
