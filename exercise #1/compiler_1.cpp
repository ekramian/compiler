
/*
	expr -> [term]A
	A -> +[term]A |
	     -[term]A |
	     e
	[term] -> 0|1|2|3|4|5|6|7|8|9
	*/

#include <iostream>
#include <cstdlib>

using namespace std;

enum TokenType { NUL, TERM, SIGN };

TokenType nextToken();
void match(TokenType);
void expr();
void A();
void term();
void error(char *);

int i = 0;
char input[1024] = "1 +3- 4";
TokenType token;

int main()
{
	//cin >> input;
	token = nextToken();
	expr();
	cout << "Success" << endl;
	system("pause");

	return EXIT_SUCCESS;
}

TokenType nextToken()
{

	for (; input[i] != '\0'; ++i)
	{

		switch (input[i])
		{

		case '0': case '1':
		case '2': case '3':
		case '4': case '5':
		case '6': case '7':
		case '8': case '9':
			++i;
			return TERM;
			break;

		case '+': case '-':
			++i;
			return SIGN;
			break;

		case ' ':
			break;

		default:
			error("ERROR.");

		}

	}

	return NUL;
}

void match(TokenType token_t)
{

	if (token == token_t)
	{
		token = nextToken();
	}
	else
	{
		error("syntax error.");
	}

}

void expr()
{

	switch (token)
	{

	case TERM:
		match(TERM);
		A();
		break;

	default:
		error("ERROR.");

	}

}

void A()
{

	switch (token)
	{

	case SIGN:
		match(SIGN);
		term();
		A();
		break;

	case NUL:
		match(NUL);
		break;

	default:
		error("ERROR.");

	}

}

void term()
{

	switch (token)
	{

	case TERM:
		match(TERM);
		break;

	default:
		error("ERROR.");

	}

}

void error(char * err)
{
	cerr << err << endl;
	system("pause");
	exit(EXIT_FAILURE);
}
