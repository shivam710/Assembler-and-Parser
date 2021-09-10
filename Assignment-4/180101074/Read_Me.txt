To PERFORM ALL TASK:-(run these commands on terminal)

	make clean
	make
    ./main


Error handling:
1. Syntax errors 	:->  	Foreign character,
					  		Statements not following the grammar,
					  		Reserved keywords redeclaration(e.g. FOR, TO, BEGIN, etc.)

2. Semantic errors	:->  	Using undeclared Variable,
							Duplicate declarations,
					  		Mismatch in the type of Variables



Files Details:
1. lex.l 			:-> 	Lexical analyser
2. main.cpp			:->  	Driving function
3. input.txt		:->  	PASCAL input file
4. yacc.y			:->  	BNF rules definition
				  	  		And handles syntax and semantic errors
5. Makefile			:->  	To perform all task