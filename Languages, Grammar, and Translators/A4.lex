import java_cup.runtime.*;
%%

%implements java_cup.runtime.Scanner
%type Symbol
%function next_token
%class A4Scanner
%eofval{ return null;
%eofval}

IDENTIFIER = [a-zA-Z][a-zA-Z0-9]*
NUMBER = [0-9]+
QUOTES = \"[^\"]*\"
%%
"+" { return new Symbol(A4Symbol.PLUS); }
"-" { return new Symbol(A4Symbol.MINUS); }
"*" { return new Symbol(A4Symbol.TIMES); }
"/" { return new Symbol(A4Symbol.DIVIDE); }
{NUMBER} { return new Symbol(A4Symbol.NUMBER, new Integer(yytext()));}  
\r|\n {}
. {}
