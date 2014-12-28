

#include <cstring>

#include "Grammar.h"


using namespace std;


class Token {
	private:
		const char *genLexeme( const char *str ) const;

	public:
		const Terminal name;
		const char * const lexeme;
		const int line;
		const int Ch;

		Token( const Terminal &token_name, const char *lexeme,
			   const int &line, const int &character );

		~Token();
};

