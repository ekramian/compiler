

enum Terminal {
	// {String Chars} = {Printable} - ["]
	// {WS}           = {Whitespace} - {CR} - {LF}
	// Whitespace     = {WS}+

	TERMINAL_END_OF_FILE,
	TERMINAL_INTEGER,           // = {digit}+
	TERMINAL_NEWLINE,           // = {CR}{LF} | {CR}
	TERMINAL_COLON,             // :
	TERMINAL_CLOSE,
	TERMINAL_NUMBER_SIGN,       // #
	TERMINAL_DATA,
	TERMINAL_DIM,
	TERMINAL_ID,                // = {Letter}[$%]?
	TERMINAL_LEFT_PARENTHESIS,  // (
	TERMINAL_RIGHT_PARENTHESIS, // )
	TERMINAL_END,
	TERMINAL_FOR,
	TERMINAL_EQUAL,             // =
	TERMINAL_TO,
	TERMINAL_STEP,
	TERMINAL_GOTO,
	TERMINAL_GOSUB,
	TERMINAL_IF,
	TERMINAL_THEN,
	TERMINAL_INPUT,
	TERMINAL_COMMA,             // ,
	TERMINAL_LET,
	TERMINAL_NEXT,
	TERMINAL_OPEN,
	TERMINAL_AS,
	TERMINAL_POKE,
	TERMINAL_PRINT,
	TERMINAL_READ,
	TERMINAL_RETURN,
	TERMINAL_RESTORE,
	TERMINAL_RUN,
	TERMINAL_STOP,
	TERMINAL_SYS,
	TERMINAL_WAIT,
	TERMINAL_REMARK,            // = REM{Space}{Printable}*
    TERMINAL_OUTPUT,
	TERMINAL_SEMICOLON,         // ;
	TERMINAL_OR,
	TERMINAL_AND,
	TERMINAL_NOT,
	TERMINAL_LESS_NOT_EQUAL,    // <>
	TERMINAL_GREATER_NOT_EQUAL, // ><
	TERMINAL_GREATER,           // >
	TERMINAL_GREATER_EQUAL,		// >=
	TERMINAL_LESS,              // <
	TERMINAL_LESS_EQUAL,        // <=
	TERMINAL_PLUS,              // +
	TERMINAL_MINUS,             // -
	TERMINAL_MULTIPLICATION,    // *
	TERMINAL_DIVISION,          // /
	TERMINAL_POWER,             // ^
	TERMINAL_STRING,            // = '"'{String Chars}*'"'
	TERMINAL_REAL,              // = {digit}+.{digit}+

    TERMINAL_SIZE
};

enum NonTerminal
{
    NONTERMINAL_LINES,
    NONTERMINAL_STATEMENTS,
    NONTERMINAL_STATEMENT,
    NONTERMINAL_ACCESS,
    NONTERMINAL_ID_LIST,
    NONTERMINAL_VALUE_LIST,
    NONTERMINAL_CONSTANT_LIST,
    NONTERMINAL_INTEGER_LIST,
    NONTERMINAL_EXPRESSION_LIST,
    NONTERMINAL_PRINT_LIST,
    NONTERMINAL_EXPRESSION,
    NONTERMINAL_AND_EXP,
    NONTERMINAL_NOT_EXP,
    NONTERMINAL_COMPARE_EXP,
    NONTERMINAL_ADD_EXP,
    NONTERMINAL_MULT_EXP,
    NONTERMINAL_NEGATE_EXP,
    NONTERMINAL_POWER_EXP,
    NONTERMINAL_VALUE,
    NONTERMINAL_CONSTANT,

    NONTERMINAL_SIZE
};

const int n_1 = 1;
const int n_2 = 2;
const int n_3 = 3;
const int n_4 = 4;
const int n_5 = 5;
const int n_6 = 6;
const int n_7 = 7;
const int n_8 = 8;

const NonTerminal Lines           = NONTERMINAL_LINES;
const NonTerminal Statements      = NONTERMINAL_STATEMENTS;
const NonTerminal Statement       = NONTERMINAL_STATEMENT;
const NonTerminal Access          = NONTERMINAL_ACCESS;
const NonTerminal ID_List         = NONTERMINAL_ID_LIST;
const NonTerminal Value_List      = NONTERMINAL_VALUE_LIST;
const NonTerminal Constant_List   = NONTERMINAL_CONSTANT_LIST;
const NonTerminal Integer_List    = NONTERMINAL_INTEGER_LIST;
const NonTerminal Expression_List = NONTERMINAL_EXPRESSION_LIST;
const NonTerminal Print_List      = NONTERMINAL_PRINT_LIST;
const NonTerminal Expression      = NONTERMINAL_EXPRESSION;
const NonTerminal And_Exp         = NONTERMINAL_AND_EXP;
const NonTerminal Not_Exp         = NONTERMINAL_NOT_EXP;
const NonTerminal Compare_Exp     = NONTERMINAL_COMPARE_EXP;
const NonTerminal Add_Exp         = NONTERMINAL_ADD_EXP;
const NonTerminal Mult_Exp        = NONTERMINAL_MULT_EXP;
const NonTerminal Negate_Exp      = NONTERMINAL_NEGATE_EXP;
const NonTerminal Power_Exp       = NONTERMINAL_POWER_EXP;
const NonTerminal Value           = NONTERMINAL_VALUE;
const NonTerminal Constant        = NONTERMINAL_CONSTANT;

#define A_OF_PRODUCTION(i) *( (NonTerminal *) production[ i ][ 0 ] )
#define B_LEN_OF_PRODUCTION(i) *( (int *) production[ i ][ 1 ] )
#define PRODUCTION(i) (char *) production[ i ][ 2 ]

const void * const production[ 75 ][ 3 ] = {
    { 0               , &n_1, "$accept -> <Lines>"                                                },
    { &Lines          , &n_4, "<Lines> -> Integer <Statements> NewLine <Lines>"                   },
    { &Lines          , &n_3, "<Lines> -> Integer <Statements> NewLine"                           },
    { &Statements     , &n_3, "<Statements> -> <Statement> : <Statements>"                        },
    { &Statements     , &n_1, "<Statements> -> <Statement>"                                       },
    { &Statement      , &n_3, "<Statement> -> CLOSE # Integer"                                    },
    { &Statement      , &n_2, "<Statement> -> DATA <Constant_List>"                               },
    { &Statement      , &n_5, "<Statement> -> DIM ID ( <Integer_List> )"                          },
    { &Statement      , &n_1, "<Statement> -> END"                                                },
    { &Statement      , &n_6, "<Statement> -> FOR ID = <Expression> TO <Expression>"              },
    { &Statement      , &n_2, "<Statement> -> GOSUB <Expression>"                                 },
    { &Statement      , &n_8, "<Statement> -> FOR ID = <Expression> TO <Expression> STEP Integer" },
    { &Statement      , &n_2, "<Statement> -> GOTO <Expression>"                                  },
    { &Statement      , &n_4, "<Statement> -> IF <Expression> THEN <Statement>"                   },
    { &Statement      , &n_2, "<Statement> -> INPUT <ID_List>"                                    },
    { &Statement      , &n_5, "<Statement> -> INPUT # Integer , <ID_List>"                        },
    { &Statement      , &n_4, "<Statement> -> LET ID = <Expression>"                              },
    { &Statement      , &n_2, "<Statement> -> NEXT <ID_List>"                                     },
    { &Statement      , &n_7, "<Statement> -> OPEN <Value> FOR <Access> AS # Integer"             },
    { &Statement      , &n_2, "<Statement> -> POKE <Value_List>"                                  },
    { &Statement      , &n_2, "<Statement> -> PRINT <Print_List>"                                 },
    { &Statement      , &n_5, "<Statement> -> PRINT # Integer , <Print_List>"                     },
    { &Statement      , &n_2, "<Statement> -> READ <ID_List>"                                     },
    { &Statement      , &n_1, "<Statement> -> RETURN"                                             },
    { &Statement      , &n_1, "<Statement> -> RESTORE"                                            },
    { &Statement      , &n_1, "<Statement> -> RUN"                                                },
    { &Statement      , &n_1, "<Statement> -> STOP"                                               },
    { &Statement      , &n_2, "<Statement> -> SYS <Value>"                                        },
    { &Statement      , &n_2, "<Statement> -> WAIT <Value_List>"                                  },
    { &Statement      , &n_1, "<Statement> -> Remark"                                             },
    { &Access         , &n_1, "<Access> -> INPUT"                                                 },
    { &Access         , &n_1, "<Access> -> OUTPUT"                                                },
    { &ID_List        , &n_3, "<ID_List> -> ID , <ID_List>"                                       },
    { &ID_List        , &n_1, "<ID_List> -> ID"                                                   },
    { &Value_List     , &n_3, "<Value_List> -> <Value> , <Value_List>"                            },
    { &Value_List     , &n_1, "<Value_List> -> <Value>"                                           },
    { &Constant_List  , &n_3, "<Constant_List> -> <Constant> , <Constant_List>"                   },
    { &Constant_List  , &n_1, "<Constant_List> -> <Constant>"                                     },
    { &Integer_List   , &n_3, "<Integer_List> -> Integer , <Integer_List>"                        },
    { &Integer_List   , &n_1, "<Integer_List> -> Integer"                                         },
    { &Expression_List, &n_3, "<Expression_List> -> <Expression> , <Expression_List>"             },
    { &Expression_List, &n_1, "<Expression_List> -> <Expression>"                                 },
    { &Print_List     , &n_3, "<Print_List> -> <Expression> ; <Print_List>"                       },
    { &Print_List     , &n_1, "<Print_List> -> <Expression>"                                      },
    { &Expression     , &n_3, "<Expression> -> <And_Exp> OR <Expression>"                         },
    { &Expression     , &n_1, "<Expression> -> <And_Exp>"                                         },
    { &And_Exp        , &n_3, "<And_Exp> -> <Not_Exp> AND <And_Exp>"                              },
    { &And_Exp        , &n_1, "<And_Exp> -> <Not_Exp>"                                            },
    { &Not_Exp        , &n_2, "<Not_Exp> -> NOT <Compare_Exp>"                                    },
    { &Not_Exp        , &n_1, "<Not_Exp> -> <Compare_Exp>"                                        },
    { &Compare_Exp    , &n_3, "<Compare_Exp> -> <Add_Exp> = <Compare_Exp>"                        },
    { &Compare_Exp    , &n_3, "<Compare_Exp> -> <Add_Exp> <> <Compare_Exp>"                       },
    { &Compare_Exp    , &n_3, "<Compare_Exp> -> <Add_Exp> >< <Compare_Exp>"                       },
    { &Compare_Exp    , &n_3, "<Compare_Exp> -> <Add_Exp> > <Compare_Exp>"                        },
    { &Compare_Exp    , &n_3, "<Compare_Exp> -> <Add_Exp> >= <Compare_Exp>"                       },
    { &Compare_Exp    , &n_3, "<Compare_Exp> -> <Add_Exp> < <Compare_Exp>"                        },
    { &Compare_Exp    , &n_3, "<Compare_Exp> -> <Add_Exp> <= <Compare_Exp>"                       },
    { &Compare_Exp    , &n_1, "<Compare_Exp> -> <Add_Exp>"                                        },
    { &Add_Exp        , &n_3, "<Add_Exp> -> <Mult_Exp> + <Add_Exp>"                               },
    { &Add_Exp        , &n_3, "<Add_Exp> -> <Mult_Exp> - <Add_Exp>"                               },
    { &Add_Exp        , &n_1, "<Add_Exp> -> <Mult_Exp>"                                           },
    { &Mult_Exp       , &n_3, "<Mult_Exp> -> <Negate_Exp> * <Mult_Exp>"                           },
    { &Mult_Exp       , &n_3, "<Mult_Exp> -> <Negate_Exp> / <Mult_Exp>"                           },
    { &Mult_Exp       , &n_1, "<Mult_Exp> -> <Negate_Exp>"                                        },
    { &Negate_Exp     , &n_2, "<Negate_Exp> -> - <Power_Exp>"                                     },
    { &Negate_Exp     , &n_1, "<Negate_Exp> -> <Power_Exp>"                                       },
    { &Power_Exp      , &n_3, "<Power_Exp> -> <Power_Exp> ^ <Value>"                              },
    { &Power_Exp      , &n_1, "<Power_Exp> -> <Value>"                                            },
    { &Value          , &n_3, "<Value> -> ( <Expression> )"                                       },
    { &Value          , &n_1, "<Value> -> ID"                                                     },
    { &Value          , &n_4, "<Value> -> ID ( <Expression_List> )"                               },
    { &Value          , &n_1, "<Value> -> <Constant>"                                             },
    { &Constant       , &n_1, "<Constant> -> Integer"                                             },
    { &Constant       , &n_1, "<Constant> -> String"                                              },
    { &Constant       , &n_1, "<Constant> -> Real"                                                }
};

