#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <boost/algorithm/string.hpp>

using namespace std;

#define EOF_token 0
#define PROGRAM_token 1 
#define VAR_token 2
#define BEGIN_token 3
#define END_token 4
#define END_FINISH_token 5 
#define INT_token 6 
#define FOR_token 7 
#define READ_token 8 
#define WRITE_token 9 
#define TO_token 10 
#define DO_token 11 
#define SEMICOLON_token 12 
#define COLON_token 13
#define COMMA_token 14 
#define ASSIGN_token 15
#define PLUS_token 16  
#define MINUS_token 17 
#define TIMES_token 18 
#define DIV_token 19 
#define LPAREN_token 20 
#define RPAREN_token 21 
#define ID_token 22 
#define INT_CONST_token 23 



#define DOT_token 24 
#define EQUAL_token 25 

 
extern int yylex();
