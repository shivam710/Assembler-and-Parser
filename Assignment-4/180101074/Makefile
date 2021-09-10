LEX=flex
YACC=bison
CC=g++ -std=c++11
OBJECT=main

$(OBJECT): lex.yy.o yacc.tab.o main.o
	$(CC) lex.yy.o yacc.tab.o main.o -o $(OBJECT)

main.o : main.cpp 
	$(CC) -c main.cpp

lex.yy.o: lex.yy.c yacc.tab.h
	$(CC) -c lex.yy.c

yacc.tab.o: yacc.tab.c
	$(CC) -c yacc.tab.c

yacc.tab.c yacc.tab.h: yacc.y
	$(YACC) -d yacc.y

lex.yy.c: lex.l
	$(LEX) lex.l

clean:
	@rm -f $(OBJECT)  *.o yacc.tab.c yacc.tab.h lex.yy.c