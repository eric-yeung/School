import java.io.*;

%%
%{
  static int[] counters = {0,0,0,0,0}; //counter for each output
  public static void main(String[] args) throws IOException {
    A2 lexer = new A2(new FileReader(new File("A2.input")));
    while (lexer.yylex() != null);
    FileWriter writer = new FileWriter("A2.output");
    writer.write(String.format("identifiers: %d\nkeywords: %d\nnumbers: %d\ncomments: %d\nquotedString: %d", counters[0], counters[1], counters[2], counters[3], counters[4]));
    writer.close();
  }

%}a
%type String
%class A2
%state COMMENT

KEYWORDS = WRITE|READ|IF|ELSE|RETURN|BEGIN|END|MAIN|STRING|INT|REAL
IDENTIFIERS = [a-zA-Z][a-zA-Z0-9]*
NUMBERS = [0-9]*\.?[0-9]+
QUOTES = \"[^\"]*\"

%%

<YYINITIAL> \/\*\* {counters[3]++; yybegin(COMMENT);}
<YYINITIAL> {QUOTES} {counters[4]++;} 
<YYINITIAL> {KEYWORDS} {counters[1]++;}
<YYINITIAL> {IDENTIFIERS} {counters[0]++;}
<YYINITIAL> {NUMBERS} {counters[2]++;}
<COMMENT> \*\*\/ {yybegin(YYINITIAL);}
\r|\n|. {}