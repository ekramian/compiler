
%{

%}

%token NewLine
%token Remark
%token ID
%token String
%token Integer
%token Real

%token CLOSE
%token DATA
%token DIM
%token END
%token FOR
%token TO
%token STEP
%token GOTO
%token GOSUB
%token IF
%token THEN
%token INPUT
%token LET
%token NEXT
%token OPEN
%token AS
%token POKE
%token PRINT
%token READ
%token RETURN
%token RESTORE
%token RUN
%token STOP
%token SYS
%token WAIT
%token OUTPUT
%token OR
%token AND
%token NOT

%%

<Lines>       : Integer <Statements> NewLine <Lines>
              | Integer <Statements> NewLine
              ;

<Statements>  : <Statement> ':' <Statements>
              | <Statement>
              ;

<Statement>   : CLOSE '#' Integer
              | DATA <Constant_List>
              | DIM ID '(' <Integer_List> ')'
              | END
              | FOR ID '=' <Expression> TO <Expression>
              | FOR ID '=' <Expression> TO <Expression> STEP Integer
              | GOTO <Expression>
              | GOSUB <Expression>
              | IF <Expression> THEN <Statement>
              | INPUT <ID_List>
              | INPUT '#' Integer ',' <ID_List>
              | LET ID '=' <Expression>
              | NEXT <ID_List>
              | OPEN <Value> FOR <Access> AS '#' Integer
              | POKE <Value_List>
              | PRINT <Print_List>
              | PRINT '#' Integer ',' <Print_List>
              | READ <ID_List>
              | RETURN
              | RESTORE
              | RUN
              | STOP
              | SYS <Value>
              | WAIT <Value_List>
              | Remark
              ;

<Access>   : INPUT
           | OUTPUT
           ;
                   
<ID_List>  : ID ',' <ID_List>
           | ID
           ;

<Value_List>      : <Value> ',' <Value_List>
                  | <Value>
                  ;

<Constant_List>   : <Constant> ',' <Constant_List>
                  | <Constant>
                  ;

<Integer_List>    : Integer ',' <Integer_List>
                  | Integer
                  ;
                 
<Expression_List> : <Expression> ',' <Expression_List>
                  | <Expression>
                  ;

<Print_List>      : <Expression> ';' <Print_List>
                  | <Expression>
                  ;

<Expression>  : <And_Exp> OR <Expression>
              | <And_Exp>
              ;

<And_Exp>     : <Not_Exp> AND <And_Exp>
              | <Not_Exp>
              ;
 
<Not_Exp>     : NOT <Compare_Exp>
              | <Compare_Exp>
              ;

<Compare_Exp> : <Add_Exp> '='  <Compare_Exp>
              | <Add_Exp> '<>' <Compare_Exp>
              | <Add_Exp> '><' <Compare_Exp>
              | <Add_Exp> '>'  <Compare_Exp>
              | <Add_Exp> '>=' <Compare_Exp>
              | <Add_Exp> '<'  <Compare_Exp>
              | <Add_Exp> '<=' <Compare_Exp>
              | <Add_Exp>
              ;

<Add_Exp>     : <Mult_Exp> '+' <Add_Exp>
              | <Mult_Exp> '-' <Add_Exp>
              | <Mult_Exp>
              ;

<Mult_Exp>    : <Negate_Exp> '*' <Mult_Exp>
              | <Negate_Exp> '/' <Mult_Exp>
              | <Negate_Exp>
              ;

<Negate_Exp>  : '-' <Power_Exp>
              | <Power_Exp>
              ;

<Power_Exp>   : <Power_Exp> '^' <Value>
              | <Value>
              ;

<Value>       : '(' <Expression> ')'
              | ID
              | ID '(' <Expression_List> ')'
              | <Constant>
              ;

<Constant> : Integer
           | String
           | Real
           ;

%%

