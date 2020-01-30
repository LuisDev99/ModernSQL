#include <iostream>
#include <fstream>
#include "./parser/parser.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello World ModernQL " << std::endl;

    if (argc != 2)
    {
        std::cout << "Usage: <filename> " << std::endl;
        return 1;
    }

    std::fstream in(argv[1]);

    if (!in.is_open())
    {
        std::cout << "Could not open input file! " << std::endl;
        return 1;
    }

    Parser parser(in);

    try
    {
        parser.beginParsing();
    }
    catch (UnexpectedPointReachedException e)
    {
        std::cout << e.getErrorMessage() << std::endl;
        return 1;
    }
    catch (IllegalTokenException e)
    {
        std::cout << e.getErrorMessage() << std::endl;
        return 1;
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    //parser.beginParsing();

    return 0;
}