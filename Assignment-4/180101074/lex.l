%{ 

#include <bits/stdc++.h>
#include "yacc.tab.h" /* Token definitions */

using namespace std;

extern char* errorString; 				/* A temporary variable to store new error */
extern vector<string> errorMessages; 	/* To record the error messages, defined in main.cpp */
int line_no_count=1; 			/* Count Line number*/
int token_count=0;
int errorCount=0;
void handleError(void); 				/* function to handle errors */

%}

%option noyywrap

%%

PROGRAM 			{token_count+=1;return MYTOKEN_PROGRAM;}
VAR 				{token_count+=1;return MYTOKEN_VAR;}
BEGIN  				{token_count+=1;return MYTOKEN_BEGIN;}
END 				{token_count+=1;return MYTOKEN_END;}
"END."          	{token_count+=1;return MYTOKEN_END_DOT;}
INTEGER         	{token_count+=1;return MYTOKEN_INT_TYPE;}
REAL				{token_count+=1;return MYTOKEN_REAL_TYPE;}
FOR 				{token_count+=1;return MYTOKEN_FOR;}	
READ 				{token_count+=1;return MYTOKEN_READ;}
WRITE 				{token_count+=1;return MYTOKEN_WRITE;}
TO  				{token_count+=1;return MYTOKEN_TO;}
DO 					{token_count+=1;return MYTOKEN_DO;}
";" 				{token_count+=1;return MYTOKEN_SEMICOLON;}
":" 				{token_count+=1;return MYTOKEN_COLON;}
"," 				{token_count+=1;return MYTOKEN_COMMA;}
":="  				{token_count+=1;return MYTOKEN_ASSIGN;}
"+" 				{token_count+=1;return MYTOKEN_PLUS;}
"-" 				{token_count+=1;return MYTOKEN_MINUS;}
"*" 				{token_count+=1;return MYTOKEN_MULT;}
DIV 				{token_count+=1;return MYTOKEN_DIV;}
"(" 				{token_count+=1;return MYTOKEN_OPEN_BRACKET;}
")"					{token_count+=1;return MYTOKEN_CLOSE_BRACKET;}

[A-Z]([A-Z0-9])* 	{
						token_count+=1;
						char* temp= (char *)malloc(strlen(yytext) + 1);
						yylval.string_val = temp;
						strcpy(yylval.string_val, yytext);
						return MYTOKEN_ID;
					}

[0-9]+				{
						token_count+=1;
						int temp= atoi(yytext);
						yylval.integer_val = temp;
						return MYTOKEN_INT;
					}

[0-9]+"."[0-9]+		{
						token_count+=1;
						float temp = atof(yytext);
						yylval.real_val = temp;
						return MYTOKEN_REAL;
					}

[\t]				{}
"\n"				{line_no_count++;}
" "					{}
.					{handleError();}

%%

void handleError()					/* function to handle errors */
{
	errorString[0]='\0'; 
	errorCount++;
	sprintf(errorString,"'%c' (0%o) : illegal character at line %d\n",yytext[0],yytext[0],line_no_count);
	errorCount++;
	string my_errstr(errorString);
	errorMessages.push_back(my_errstr); 
}
