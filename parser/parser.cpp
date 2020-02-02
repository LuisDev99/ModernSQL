#include "parser.h"

#define GET_NEXT_TOKEN() \
    lookAhead = getNextToken();

#define GET_TOKEN_STRING_AND_GET_NEXT_TOKEN()     \
    std::string moveToken()                       \
    {                                             \
        std::string text = this->lexer->YYTEXT(); \
        GET_NEXT_TOKEN();                         \
        return text;                              \
    }

void Parser::statement()
{
    if (this->lookAhead == Token::Select)
        select();

    else if (this->lookAhead == Token::Update)
        update();

    else if (this->lookAhead == Token::Delete)
        Delete();

    else if (this->lookAhead == Token::Create || this->lookAhead == Token::Insert)
        insert();

    else
        throw UnexpectedPointReachedException(__func__, __FILE__, __LINE__);
}

void Parser::select()
{
    /* SELECT */
    moveIfLookAheadEqualsTo(Token::Select);

    /* OPEN_BRACE */
    moveIfLookAheadEqualsTo(Token::Open_Brace);

    /* obj-body-decl */
    obj_body_decl();

    /* (condition-body)? */
    if (lookAheadEqualsTo(Token::Where))
        condition_body();

    /* CLOSE_BRACE */
    moveIfLookAheadEqualsTo(Token::Close_Brace);
}
void Parser::update()
{
}
void Parser::Delete()
{
}
void Parser::insert()
{
}
void Parser::obj_body_decl()
{
    /* IDENTIFIER */
    moveIfLookAheadEqualsTo(Token::Identifier);

    /* (body)? */
    if (lookAheadEqualsTo(Token::Open_Brace))
        body();
}

void Parser::body()
{
    /* OPEN_BRACE */
    moveIfLookAheadEqualsTo(Token::Open_Brace);

    /* attribute */
    attribute();

    /* (attribute)* */
    while (lookAheadEqualsTo(Token::Identifier))
        attribute();

    /* CLOSE_BRACE */
    moveIfLookAheadEqualsTo(Token::Close_Brace);
}

void Parser::attribute()
{
    /* IDENTIFIER */
    moveIfLookAheadEqualsTo(Token::Identifier);

    /* attribute-prime */
    attribute_prime();
}

void Parser::attribute_prime()
{
    if (lookAheadEqualsTo(Token::Open_Par))
    {
        /* OPEN_PAR */
        GET_NEXT_TOKEN();

        /* IDENTIFIER */
        moveIfLookAheadEqualsTo(Token::Identifier);

        /* CLOSE_PAR */
        moveIfLookAheadEqualsTo(Token::Close_Par);

        return;
    }

    /* USIGN | ON */
    if (lookAheadEqualsTo(Token::Using) || lookAheadEqualsTo(Token::On))
    {
        GET_NEXT_TOKEN();

        /* foreign-key */
        foreign_key();
    }

    /* epsilon */
    return;
}

void Parser::foreign_key()
{
    /* IDENTIFIER */
    moveIfLookAheadEqualsTo(Token::Identifier);

    /* (body)? */
    if (lookAheadEqualsTo(Token::Open_Brace))
        body();
}

void Parser::condition_body()
{
    /* WHERE */
    moveIfLookAheadEqualsTo(Token::Where);

    /* OPEN_BRACE */
    moveIfLookAheadEqualsTo(Token::Open_Brace);

    /* conditional-obj-body-decl */
    conditional_obj_body_decl();

    /* CLOSE_BRACE */
    moveIfLookAheadEqualsTo(Token::Close_Brace);
}
void Parser::conditional_obj_body_decl()
{
    /* expression */
    expression();

    /* (expression)* */
    while (isExpr(this->lookAhead))
        expression();
}
void Parser::expression()
{
    /* foo */
    foo();

    while (isThirdLevelOp(this->lookAhead))
    {
        GET_NEXT_TOKEN();

        expression();
    }
}

void Parser::foo()
{
    /* bar */
    bar();

    while (isSecondLevelOp(this->lookAhead))
    {
        GET_NEXT_TOKEN();

        foo();
    }
}

void Parser::bar()
{

    /* OPEN_PAR */
    if (lookAheadEqualsTo(Token::Open_Par))
    {
        GET_NEXT_TOKEN();

        /* expression */
        expression();

        /* CLOSE_PAR */
        GET_NEXT_TOKEN();

        return;
    }

    /* IDENTIFIER */
    if (lookAheadEqualsTo(Token::Identifier))
    {
        GET_NEXT_TOKEN();

        /* bar-prime */
        bar_prime();

        return;
    }

    /* BOOL_LITERAL */
    if (lookAheadEqualsTo(Token::Bool_Literal))
    {
        GET_NEXT_TOKEN();

        return;
    }

    /* INT_LITERAL */
    if (lookAheadEqualsTo(Token::Int_Literal))
    {
        GET_NEXT_TOKEN();

        return;
    }

    /* STRING_LITERAL */
    if (lookAheadEqualsTo(Token::String_Literal))
    {
        GET_NEXT_TOKEN();

        return;
    }

    /* LOGICAL_NOT_OPERATOR */
    if (lookAheadEqualsTo(Token::Logical_Not_Operator))
    {
        GET_NEXT_TOKEN();

        /* expression */
        expression();

        return;
    }

    throw UnexpectedPointReachedException(__func__, __FILE__, __LINE__);
}

void Parser::bar_prime()
{
    /* epsilon */
    if (!lookAheadEqualsTo(Token::Open_Brace))
        return;

    /* --- Else --- */

    /* OPEN_BRACE */
    GET_NEXT_TOKEN();

    /* conditional-obj-body-decl */
    conditional_obj_body_decl();

    /* CLOSE_BRACE */
    moveIfLookAheadEqualsTo(Token::Close_Brace);
}