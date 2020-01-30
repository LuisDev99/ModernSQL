#ifndef myExceptions__
#define myExceptions__

#include <exception>
#include <string>
#include "tokens.h"

static const char *tokenToStringy(Token tk)
{
    auto tuple = TokenToStringMap.find(tk);

    if (tuple == TokenToStringMap.end())
        return "Error, Token either doesnt exists or hasnt been added its string";

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
    IllegalTokenException(Token expectedToken, Token illegalToken)
    {
        const char *expectedTokenStr = tokenToStringy(expectedToken);
        const char *illegalTokenStr = tokenToStringy(illegalToken);

        message = "Expected token: " + std::string(expectedTokenStr) + ", Found: " + std::string(illegalTokenStr);
    }

    const char *getErrorMessage()
    {
        return message.c_str();
    }

private:
    std::string message;
};

#endif
