#ifndef myExceptions__
#define myExceptions__

#include <exception>
#include <string>
#include "tokens.h"

static const char *tokenToStringy(Token tk)
{
    auto tuple = TokenToStringMap.find(tk);

    if (tuple == TokenToStringMap.end())
        return "Error, Token either does not exists or its string has not been added in the TokenToString map";

    return tuple->second;
}

class UnexpectedPointReachedException : public std::exception
{
public:
    UnexpectedPointReachedException(const char *functionName, const char *fileName, int lineNumber)
    {
        std::string wStringFuncName = functionName;
        std::string wStringFileName = fileName;

        message = "Program hit a point where it should not have reached exception, in file: " + wStringFileName + ", function: " + wStringFuncName + ", on line: " + std::to_string(lineNumber);
    }

    const char *getErrorMessage()
    {
        return message.c_str();
    }

private:
    std::string message;
};

class IllegalTokenException : public std::exception
{
public:
    IllegalTokenException(Token expectedToken, Token illegalToken, int lineNumber, int columnNumber)
    {
        const char *expectedTokenStr = tokenToStringy(expectedToken);
        const char *illegalTokenStr = tokenToStringy(illegalToken);

        message = "Syntax error. Expected token: " + std::string(expectedTokenStr) + ", Found: " + std::string(illegalTokenStr) + ", on line: " + std::to_string(lineNumber) + ", column: " + std::to_string(columnNumber);
    }

    const char *getErrorMessage()
    {
        return message.c_str();
    }

private:
    std::string message;
};

#endif
