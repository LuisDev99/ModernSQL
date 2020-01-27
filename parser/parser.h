#ifndef PARSERY__
#define PARSERY__

#include <iostream>
#include <fstream>
#include <FlexLexer.h>
#include "./../tokens.h"

class Parser
{

public:
    Parser(std::istream &input) : in(input)
    {
        lexer = new yyFlexLexer(&in);

        lookAhead = (Token)lexer->yylex();

        do
        {
            std::cout << "Token: " << lexer->YYText() << " token value: " << (int)lookAhead << '\n';

        } while (lookAhead = (Token)lexer->yylex());
    }

    ~Parser()
    {
        delete lexer;
    }

private:
    /* Grammar productions in order */
    void action();
    void select();
    void update();
    void Delete();
    void create();
    void obj_body_decl();
    void attribute();
    void condition_body();
    void conditional_obj_body_decl();
    void expression();
    void foo();
    void bar();

private:
    std::istream &in;
    yyFlexLexer *lexer;
    Token lookAhead;
};

#endif // PARSERY__