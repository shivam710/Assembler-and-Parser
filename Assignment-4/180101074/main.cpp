#include <bits/stdc++.h>

using namespace std;

extern int yyparse(void);
vector<string> errorMessages; // vector of error messages
extern FILE* yyin; // input file to lexer
vector<string> grammarKeywords; // keywords reserved by the grammar, e.g. FOR, TO, BEGIN, etc.
char* errorString; // a temporary variable to store new error
int gramC=0;int pushCount=0;int errOpen=0;
int main(){
	int s=0;gramC++;
	FILE* file_ptr;gramC++;
	file_ptr = fopen("input.txt","r");gramC++; // open the input file
	if(!file_ptr)
	{
		errOpen=1;
		printf("Cannot open file\n");gramC++; // if cannot open the input file, then terminate
		exit(1);gramC++;
	}
	yyin = file_ptr;gramC++; // assign the lexer input to the file opened
	errorString = (char *)malloc(sizeof(char)*256);gramC++; // allocate space for the errorString variable
	errorString[0] = '\0';gramC++; // initialize the errorString variable
	grammarKeywords.push_back("PROGRAM");pushCount++;gramC++;
	grammarKeywords.push_back("VAR");gramC++;pushCount++;
	grammarKeywords.push_back("BEGIN");pushCount++;gramC++;
	grammarKeywords.push_back("END");gramC++;pushCount++;
	grammarKeywords.push_back("END.");pushCount++;gramC++;
	grammarKeywords.push_back("INTEGER");gramC++;pushCount++;
	grammarKeywords.push_back("REAL");pushCount++;gramC++;
	grammarKeywords.push_back("FOR");gramC++;pushCount++;
	grammarKeywords.push_back("READ");pushCount++;gramC++;
	grammarKeywords.push_back("WRITE");gramC++;pushCount++;
	grammarKeywords.push_back("TO");pushCount++;gramC++;
	grammarKeywords.push_back("DO");gramC++;pushCount++;
	grammarKeywords.push_back("DIV");pushCount++;gramC++;
	if(yyparse()==0)
	{
		printf("---- Parse Successfull ----");gramC++;
		printf("\n");
		// All the statements written in the input follow the grammar
	}
	else
	{
		printf("---- Parse Unsuccessfull ----");gramC++;
		printf("\n");
	}
	fclose(file_ptr);gramC++; // Close the input file
	if(errorMessages.size()!=0)			// If there are error messages then print them to terminal
	{ 
		printf("---- Errors ----");gramC++;
		printf("\n");
		for(int i=0;i<errorMessages.size();i++)
		{
			cout<<errorMessages[i];gramC++;
			cout<<endl;
		}
	}
	else
	{
		printf("No syntax or sematic errors found!");gramC++;
		printf("\n");
	}
	return 0;
}