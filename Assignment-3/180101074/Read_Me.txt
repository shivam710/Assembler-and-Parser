*** token.h     ->    Header file to store Token coding scheme

*** symbol_table.h ->  Header File for Hashed Symbol Table Organization.

*** lex.l   ->    LEX specification of the tokens of PASCAL

##### Generation of lexical analyzer:->  lex -i lex.l




*** lex.yy.c ->   Lexical analyzer for PASCAL

*** main()  ->  Main function in LEX specification file is used for testing Lexical Analyzer
               (By printing Tokens and Symbol Table );


#####   Create executable file for tester:->   g++ lex.yy.c -lfl




*** a.out       ->     Executable file for tester

*** input.pas   ->     PASCAL input file

#####   Testing for Lexical Analyzer:-> ./a.out < input.pas

|--------------------------------------------------------------------|
| TO PERFORM ALL TASK:-                                              |
|                        run "make" command in terminal              |
|--------------------------------------------------------------------|