
/*
	<< Convert Infix to Postfix >>

	expr -> [term]A
	A -> +[term]A |
	     -[term]A |
	     e
	[term] -> 0|1|2|3|4|5|6|7|8|9|[term]
*/

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

template< class T >
class StackNode
{
	public:
		StackNode *back;
		T data;

	public:
		StackNode( StackNode< T > *bck, T dta )
		{
			back = bck;
			data = dta;
		}

		~StackNode()
		{
		}

};

template< class T >
class Stack
{
	private:
		StackNode< T > *top;

	public:
		Stack()
		{
			top = 0;
		}

		~Stack()
		{
			StackNode< T > *st;

			while ( top != 0 )
			{
				st = top->back;

				delete top;

				top = st;
			}

		}

		void push( T data )
		{
			StackNode< T > *st = new StackNode< T >( top, data );

			top = st;
		}

		T pop()
		{

			if ( empty() )
			{
				error( "Stack Underflow." );
			}

			T data = top->data;
			StackNode< T > *st = top;

			top = top->back;

			delete st;

			return data;
		}

		bool empty()
		{
			return top == 0 ? true : false;
		}

};

Stack< int > stack;

enum TokenType { TOKENTYPE_END, TOKENTYPE_NUM, TOKENTYPE_OP };

int head = 0;
char input[ 1024 ] = "167 +354- 42";

char nextCharacter();
void putCharacter();

void error( char * );

class Token
{
	private:
		TokenType token_type;
		char *token_value;

	public:
		Token( TokenType tt, char *val )
		{
			token_type = tt;
			token_value = new char[ strlen( val ) + 1 ];
			strcpy( token_value, val );
		}

		~Token()
		{
			delete [] token_value;
		}

		TokenType tokenType()
		{
			return token_type;
		}

		char *tokenValue()
		{
			char *dest = new char[ strlen( token_value ) + 1 ];

			strcpy( dest, token_value );

			return dest;
		}

		static Token *nextToken()
		{
			char c;

			while ( ( c = nextCharacter() ) == ' ' )
			{
				continue;
			}

			if ( c == '\0' )
			{
				return new Token( TOKENTYPE_END, "" );
			}

			if ( '0' <= c && c <= '9' )
			{
				int i = 0;
				char num[ 1024 ];

				while ( '0' <= c && c <= '9' )
				{
					num[ i++ ] = c;
					c = nextCharacter();
				}

				num[ i ] = '\0';
				putCharacter();

				return new Token( TOKENTYPE_NUM, num );
			}

			if ( c == '+' || c == '-' )
			{				
				char op_str[ 2 ];

				op_str[ 0 ] = c;
				op_str[ 1 ] = '\0';

				return new Token( TOKENTYPE_OP, op_str );
			}

			error( "ERROR." );
		}

};

Token *token = 0;

void match( TokenType );
void expr();
void A();
void term();

int main()
{
	//cin >> input;
	token = Token::nextToken();
	expr();

	if ( token->tokenType() != TOKENTYPE_END )
	{
		error( "ERROR." );
	}

	cout << "\nSuccess.\nResult: " << stack.pop() << endl;
	system( "PAUSE" );

	return EXIT_SUCCESS;
}

char nextCharacter()
{
	int h = head;

	++head;

	return input[ h ];
}

void putCharacter()
{
	head--;
}

void match( TokenType type )
{

	if ( token->tokenType() == type )
	{

		if ( token != 0 )
		{
			delete token;
		}

		token = Token::nextToken();
	}
	else
	{
		error( "syntax error." );
	}

}

void expr()
{

	switch ( token->tokenType() )
	{

		case TOKENTYPE_NUM:
			term();
			A();
			break;

		default:
			error( "ERROR." );

	}

}

void A()
{
	char *val;
	int num_1, num_2;

	switch ( token->tokenType() )
	{

		case TOKENTYPE_OP:
			val = token->tokenValue();
			match( TOKENTYPE_OP );
			term();

			// semantic action: ================
			cout << val << " ";

			num_2 = stack.pop();
			num_1 = stack.pop();

			if ( val[ 0 ] == '-' )
			{
				num_2 *= -1;
			}

			delete [] val;

			stack.push( num_1 + num_2 );
			// =================================

			A();
			break;

		default:
			break;

	}

}

void term()
{
	char *val;
	int num;

	switch ( token->tokenType() )
	{

		case TOKENTYPE_NUM:
			val = token->tokenValue();
			num = atoi( val );

			delete [] val;

			match( TOKENTYPE_NUM );

			// semantic action =================
			cout << num << " ";
			stack.push( num );
			// =================================

			break;

		default:
			error("ERROR.");

	}

}

void error( char *err )
{
	cerr << err << endl;
	system("pause");
	exit(EXIT_FAILURE);
}
