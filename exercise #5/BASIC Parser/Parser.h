

#include "Scanner.h"


#define Byte unsigned char
#define BytePtr const Byte *


class Parser
{
    private:
        static BytePtr const parsing_table[ 145 ][ 74 ];

        static BytePtr ACTION( int s, Terminal a );
        static int GOTO( int s, NonTerminal a );

    public:
        Parser();
        ~Parser();

        static void parse( Scanner * const scan );
};

