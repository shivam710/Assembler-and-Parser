%{
	#include <bits/stdc++.h> 
	using namespace std;
	extern int yylex(void);
	extern int line_no_count;
	extern char* errorString;
	extern vector<string> errorMessages;
	void yyerror(const char* errS);
	struct symbolInfo										// Structure to store a symbol
	{ 
		string symbol_name; 
		int symbol_type; 									// INT TYPE, REAL TYPE
		int line_num; 
	};
	vector<string> id_list; 								// List of all the variables in current declaration statement
	int varable_activeFlag=0; 								// A flag used to find the variable declaration
	int errCount=0;	
	int typeErr=0;										// Error Count
	void addErrorMessage(char* errMsg); 					// function to add error into errorMessages
	unordered_map<string, struct symbolInfo> SymbolTable; 	// Symbol Table
	extern vector<string> grammarKeywords; 					// keywords reserved by the grammar, e.g. FOR, TO, BEGIN, etc.
	void handleTypeMismatch(int type1, int type2); 			// function to handle the case of type mismatch
	int gCount=0,progC=0;
	
%}

%union
{
	double real_val; 										// to record real type
	int integer_val; 										// to record integer type
	char *string_val; 										// to record identifiers
}

%token MYTOKEN_PROGRAM 1
%token MYTOKEN_BEGIN 3
%token MYTOKEN_VAR 2
%token MYTOKEN_END 4
%token <integer_val> MYTOKEN_INT_TYPE 6
%token MYTOKEN_END_DOT 5
%token <integer_val> MYTOKEN_REAL_TYPE 7
%token MYTOKEN_READ 9
%token MYTOKEN_FOR 8
%token MYTOKEN_WRITE 10
%token MYTOKEN_DO 12
%token MYTOKEN_TO 11
%token MYTOKEN_SEMICOLON 13
%token MYTOKEN_COMMA 15
%token MYTOKEN_COLON 14
%token MYTOKEN_ASSIGN 16
%token MYTOKEN_MINUS 18
%token MYTOKEN_PLUS 17
%token MYTOKEN_MULT 19
%token MYTOKEN_OPEN_BRACKET 21
%token MYTOKEN_DIV 20
%token MYTOKEN_CLOSE_BRACKET 22
%token <integer_val> MYTOKEN_INT 24
%token <string_val> MYTOKEN_ID 23
%token <real_val> MYTOKEN_REAL 25

// Return type of the rules
%type <integer_val> type exp term factor
%type <string_val> ID

%%

prog 			: 	MYTOKEN_PROGRAM prog_name MYTOKEN_VAR {varable_activeFlag =1;gCount++;} 
					dec_list {varable_activeFlag =0;gCount++;} 
					MYTOKEN_BEGIN stmt_list MYTOKEN_END_DOT	{progC++;}
				;


prog_name 		: 	ID {gCount++;progC++;}
				;


dec_list 		: 	dec dec_list {progC++;gCount++;}
				| 	dec			 {progC++;gCount++;}
				;


dec 			: 	id_list MYTOKEN_COLON type 
					{
						gCount++;
						int len=id_list.size();
						for(int i=0;i<len;i++)										// traverse the declaration list
						{ 
							progC++;
							auto itr = SymbolTable.find(id_list[i]);progC++; 				// find whether the symbol was defined before or not
							if(itr == SymbolTable.end())							// If not defined
							{ 
								gCount++;
								struct symbolInfo tempVar;progC++;
								tempVar.symbol_name = id_list[i];progC++; 					// set symbol_name
								tempVar.symbol_type = $3;progC++;gCount++; 							// set symbol_type, MYTOKEN_INT_TYPE or MYTOKEN_REAL_TYPE
								tempVar.line_num = line_no_count;progC++; 					// set line number at which the variable is defined
								SymbolTable.insert(make_pair(id_list[i],tempVar));progC++; 	// Insert new symbol in Symbol Table
							}
							else													// If found
							{ 
								errorString[0]='\0';progC++;
								sprintf(errorString,"Duplicate Variable definition at line %d, %s is already defined at line %d",line_no_count,id_list[i].c_str(),itr->second.line_num);progC++;
								addErrorMessage(errorString);progC++; 						// Add error to the list of errors
							}
						}
						id_list.clear();progC++; 
						gCount++;											// clear the list of symbols in the current declarative statement
					}
				;


type 			: 	MYTOKEN_INT_TYPE 				{$$ = MYTOKEN_INT_TYPE;gCount++;progC++;}
				|	MYTOKEN_REAL_TYPE 				{$$ = MYTOKEN_REAL_TYPE;progC++;gCount++;}
				  	/* return the type of the variable or constant */ 
				;
id_list 		: 	ID 
					{
						progC++;
						if(varable_activeFlag)				// if VAR statement is being processed
						{ 
							string temp($1);gCount++;
							id_list.push_back(temp);gCount++; 		// push the variable into id_list
						}
					}
				| 	id_list MYTOKEN_COMMA ID 				// if VAR statement is being processed
					{ 
						progC++;
						if(varable_activeFlag)
						{
							string temp($3);gCount++;
							id_list.push_back(temp);gCount++; 		// push the variable into id_list
						}
					} 
				;


stmt_list 		: 	stmt 								{progC++;gCount++;}
				| 	stmt_list MYTOKEN_SEMICOLON stmt	{gCount++;progC++;}
				;


stmt 			: 	assign 	{gCount++;progC++;}
				| 	read 	{progC++;gCount++;}
				| 	write 	{gCount++;progC++;}
				| 	for		{progC++;gCount++;}
				;


assign 			: 	ID MYTOKEN_ASSIGN exp 
					{
						progC++;
						string temp($1);gCount++;
						auto itr = SymbolTable.find(temp);gCount++; 
						progC++;								
						if(itr == SymbolTable.end())									
						{ 
							progC++;
							errorString[0]='\0';gCount++;
							sprintf(errorString,"Error at line %d, %s variable is not declared in the scope",line_no_count,$1);gCount++;
							addErrorMessage(errorString);gCount++;
						}
						else if(itr->second.symbol_type != $3)
						{
							progC++;
							// If symbol_type is not matched between ariable and the expression
							handleTypeMismatch(itr->second.symbol_type,$3);gCount++; 		// handle the symbol_type error using handleTypeMismatch function
						}
					
					}
				;


exp 			: 	term {$$ = $1;gCount++;progC++;} 							/* If single term then the type is same as that of term */
				| 	exp MYTOKEN_PLUS term 
					{
						gCount++;
						if($1 == $3)	// If same type
						{ 
							$$ = $1;progC++;
						}
						else			// otherwise handle different types
						{ 
							handleTypeMismatch($1,$3);progC++;
						}
					}
				| 	exp MYTOKEN_MINUS term 
					{
						gCount++;
						if($1 == $3)
						{
							$$ = $1;progC++;
						}
						else
						{
							handleTypeMismatch($1,$3);progC++;
						}
					}
				;


term 			: 	factor {$$ = $1;progC++;gCount++;}
				| 	term MYTOKEN_MULT factor 
					{
						gCount++;
						if($1 == $3)
						{
							$$ = $1;progC++;
						}
						else
						{
							handleTypeMismatch($1,$3);progC++;
						}
					}
				| 	term MYTOKEN_DIV factor 
					{
						gCount++;
						if($1 == $3)
						{
							$$ = $1;progC++;
						}
						else
						{
							handleTypeMismatch($1,$3);progC++;
						}
					}
				;


factor 			: 	ID 
					{
						progC++;
						string temp($1);gCount++;
						auto itr = SymbolTable.find(temp); gCount++;		// find the symbol in SymbolTable
						if(itr == SymbolTable.end())			// If not found
						{ 	
							progC++;		
							errorString[0]='\0';gCount++;
							sprintf(errorString,"Error at line %d, %s variable is not declared in the scope",line_no_count,$1);gCount++;
							addErrorMessage(errorString);gCount++;
						}
						else
						{
							progC++;
							$$ = itr->second.symbol_type; gCount++;		// If found then return the symbol_type of the variable
						}
					}
				| 	MYTOKEN_INT {$$ = MYTOKEN_INT_TYPE;gCount++;progC++;} 
				| 	MYTOKEN_REAL {$$ = MYTOKEN_REAL_TYPE;progC++;gCount++;}
				| 	MYTOKEN_OPEN_BRACKET exp MYTOKEN_CLOSE_BRACKET {$$ = $2;gCount++;progC++;} // return the type of the exp
				;


read 			: 	MYTOKEN_READ MYTOKEN_OPEN_BRACKET id_list MYTOKEN_CLOSE_BRACKET {progC++;gCount++;}
				;


write 			: 	MYTOKEN_WRITE MYTOKEN_OPEN_BRACKET id_list MYTOKEN_CLOSE_BRACKET {gCount++;progC++;}
				;


for 			: 	MYTOKEN_FOR index_exp MYTOKEN_DO body	{gCount++;progC+=1;}
				;


index_exp 		: 	ID MYTOKEN_ASSIGN exp MYTOKEN_TO exp	{progC+=1;gCount++;}
				;


body 			: 	stmt 									{gCount++;progC+=1;}
				| 	MYTOKEN_BEGIN stmt_list MYTOKEN_END		{progC+=1;gCount++;}
				;


ID 				: 	MYTOKEN_ID
					{
						progC++;
						int p_count=0;gCount++;
						string temp_name(yylval.string_val);p_count++;
						progC++;
						int len=grammarKeywords.size();
						for(int i=0;i<len;i++)		// check for reserved keywords
						{ 
							progC++;
							if(temp_name == grammarKeywords[i])			// if found then error
							{ 
								progC++;
								errorString[0]='\0';gCount++;
								sprintf(errorString,"Error at line %d, variable %s cannot be a reserved keyword",line_no_count,yylval.string_val);gCount++;
								addErrorMessage(errorString);gCount++;
							}
						}
						$$ = yylval.string_val;gCount++;progC++; 						// otherwise return the variable name
				  	}
				;

%%
// Handle the syntax errors
void yyerror(const char* errS)
{ 
	errCount++;
	errorString[0]='\0';errCount++;
	sprintf(errorString,"Error at line: %d, %s\n",line_no_count,errS);
	errCount++;
	string my_errstr(errorString);errCount++;
	errorMessages.push_back(my_errstr);
}


// Add error in errorMessages 
void addErrorMessage(char* errMsg)
{
	int addCount=0;
	string temp=errMsg;addCount++;
	string my_errstr(temp);
	addCount++;
	string temp1=my_errstr;addCount++;
	errorMessages.push_back(my_errstr);
}


// Handle Type error
void handleTypeMismatch(int type1, int type2)
{ 
	typeErr++;
	int tempcount1=0,tempcount2=0;
	string t1; 
	string t2;
	errorString[0] = '\0'; 
	int temp1= (int)MYTOKEN_INT_TYPE;
	if(type1 == temp1 )
	{
		tempcount1++;t1 = "INTEGER";
	}
	else
	{
		tempcount1++;t1 = "REAL";
	}
	int temp2=  (int)MYTOKEN_INT_TYPE;
	if(type2 == temp2)
	{
		tempcount2++;t2 = "INTEGER";
	}
	else
	{
		tempcount2++;t2 = "REAL";
	}
	int typeErr1=0;
	sprintf(errorString,"Error at line %d, Incompatible types %s and %s",line_no_count,t1.c_str(),t2.c_str());typeErr--;
	string my_errstr(errorString);typeErr1++;
	errorMessages.push_back(my_errstr);
}