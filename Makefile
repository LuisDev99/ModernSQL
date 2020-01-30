CC=g++
DEPS = main.cpp ./parser/parser.h ./lexer/lexer.l

flex: ./lexer/lexer.l
	flex ./lexer/lexer.l
	g++ -g -std=c++17 parser/parser.h parser/parser.cpp *.h *.cpp
	make clean
	

clean: 
	rm *.gch

run:
	./a.out tests/select_tests/select_with_join_with_condition.txt
