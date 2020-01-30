#ifndef PARSERY__
#define PARSERY__

#include <iostream>
#include <fstream>
#include <string>
#include <FlexLexer.h>
#include "./../tokens.h"
#include "./../exceptions.cpp"

class Parser
{

public:
    /* Grammar productions in order */
    void statement();
    void select();
    void update();
    void Delete();
    void insert();
    void obj_body_decl();
    void body();
    void attribute();
    void attribute_prime();
    void foreign_key();
    void condition_body();
    void conditional_obj_body_decl();
    void expression();
    void foo();
    void bar();
    void bar_prime();

public:
    Parser() = default;

    Parser(std::istream &input) : in(input)
    {
        lexer = new yyFlexLexer(&in);

        lookAhead = getNextToken();
    }

    void beginParsing()
    {
        statement();
    }

    ~Parser()
    {
        delete lexer;
    }

    Token getNextToken()
    {
        return (Token)lexer->yylex();
    }

    bool lookAheadEqualsTo(Token tk)
    {
        return tk == this->lookAhead;
    }

    /**
     * Function that checks if lookahead is equal to the @param tk 
     * If they are not equal, throws an exception
     * If equal, gets the next token and assigns it to lookahead */
    void moveIfLookAheadEqualsTo(Token tk)
    {
        if (tk != this->lookAhead)
            throw IllegalTokenException(tk, this->lookAhead);

        lookAhead = getNextToken();
    }

    bool isExpr(Token tk)
    {
        switch (tk)
        {
        case Token::Identifier:
        case Token::Bool_Literal:
        case Token::Int_Literal:
        case Token::String_Literal:
        case Token::Logical_Not_Operator:
            return true;
        }

        return false;
    }

    bool isThirdLevelOp(Token tk)
    {
        switch (tk)
        {
        case Token::Logical_LessEqual_Operator:
        case Token::Logical_GreaterEqual_Operator:
        case Token::Logical_LessThan_Operator:
        case Token::Logical_GreaterThan_Operator:
        case Token::Logical_Equal_Operator:
        case Token::Logical_NotEqual_Operator:
            return true;
        }

        return false;
    }

    bool isSecondLevelOp(Token tk)
    {
        switch (tk)
        {
        case Token::Logical_And_Operator:
        case Token::Logical_Or_Operator:
            return true;
        }

        return false;
    }

private:
    std::istream &in;
    yyFlexLexer *lexer;
    Token lookAhead;
};

#endif // PARSERY__