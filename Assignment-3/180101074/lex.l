/*Declarations section start here*/

/* Auxiliary declarations start here*/
%{
#include "token.h"
#include "symbol_table.h"


extern string install_id(char *id_input, bool upper_case);
extern void lex_error(string msg);
extern string install_num(char *num_input);

string yylval;
vector<string> symbol_table;
int lineno=1;
char token_name[100][20]={"EOF_token","PROGRAM_token", "VAR_token", "BEGIN_token", "END_token",
     "END_FINISH_token", "INT_token", "FOR_token", "READ_token", 
     "WRITE_token", "TO_token", "DO_token",
     "SEMICOLON_token", "COLON_token", "COMMA_token", 
     "ASSIGN_token", "PLUS_token", "MINUS_token", "TIMES_token",
     "DIV_token", "LPAREN_token", "RPAREN_token", 
     "ID_token", "INT_CONST_token", "DOT_token", "EQUAL_token"};

int table_index = 0;

%}

/*Auxiliary declarations end & Regular definitions start here*/

delim  	[ \t]
ws     	{delim}+
letter	[a-zA-Z]
digit 	[0-9]
id    	{letter}({letter}|{digit})*
int 	{digit}+

/*Declarations section ends here*/

/* Rules section starts here*/

%%
\n							{ lineno += 1; }
{ws}     					{ /* no action and no return */ }
(PROGRAM|program)			{ return PROGRAM_token;}
(VAR|var)					{ return VAR_token;}
(BEGIN|begin)				{ return BEGIN_token;}
(END|end)					{ return END_token;}
(END+"."|end+".")			{ return END_FINISH_token;}
(INTEGER|integer)			{ return INT_token;}
(FOR|for)					{ return FOR_token;}
(READ|read)					{ return READ_token;}
(WRITE|write)				{ return WRITE_token;}
(TO|to)						{ return TO_token;}
(DO|do)						{ return DO_token;}
(DIV|div)					{ return DIV_token;}
{id}						{ yylval = install_id(yytext, true);return ID_token;}
{int}						{ yylval = install_num(yytext);  return INT_CONST_token;}
";"							{ return SEMICOLON_token;}
":"							{ return COLON_token;}
","							{ return COMMA_token;}
"."							{ return DOT_token;}
"("							{ return LPAREN_token;}
")"							{ return RPAREN_token;}
"="							{ return EQUAL_token;}
"-"							{ return MINUS_token;}
"+"							{ return PLUS_token;}
"*"							{ return TIMES_token;}
":="						{ return ASSIGN_token;}
.							{string s(yytext); lex_error("improper character \'" + s + "\'");}


%%

/* Rules section ends here*/

/* Auxiliary functions starts here*/


int yywrap()
{  	if(feof(stdin))
	{ 
		return 1;
	}
   	else
	{
		return 0;
	}
}


string install_id(char *id_input, bool upper_case) 
{
  	string str(id_input);
  	if(upper_case) 
	{
		  boost::to_upper(str);
	}
	insert(str,"local","ID",lineno);
	  return str;
	 

}

string install_num(char *num_input) {
	string str(num_input);
	insert(str,"local","INTEGER_CONSTANT",lineno);
	return str;
}

void lex_error(string msg)
{
  cout << msg <<endl;
}
/* Auxiliary functions ends here*/


/* Main function to perform testing of Lexical Analyzer*/ 
int main()
{	
	int i;
	cout<<"---------------------------------------------------------------"<<endl;
	cout<< "|       TOKEN       |    TOKEN CODE    |   TOKEN SPECIFIER   |"<<endl;
	cout<<"---------------------------------------------------------------"<<endl;
	while((i=yylex()) != END_FINISH_token)
	{
		switch(i)
		{

			case ID_token:
			{
				cout << "| " << setw(17) << token_name[i] << " ";
				cout << "| " << setw(16) << i << " ";
				cout << "| " << setw(19)  << yylval << " |" << endl;
				break;
			}
			case INT_CONST_token:
			{
				cout << "| " << setw(17) << token_name[i] << " ";
				cout << "| " << setw(16) << i << " ";
				cout << "| " << setw(19)  << "#"+yylval << " |" << endl;
				break;
			}
			default:
			{
				cout << "| " << setw(17) << token_name[i] << " ";
				cout << "| " << setw(16) << i << " ";
				cout << "| " << setw(21) << " |" << endl;
				break;
			}
		}
	}
	cout << "| " << setw(17) << token_name[i] << " ";
	cout << "| " << setw(16) << i << " ";
	cout << "| " << setw(21) << " |" << endl;
	cout << "--------------------------------------------------------------\n\n" << endl;
	print_symtab();
}



