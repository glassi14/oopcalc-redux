#include "mathhandler.h"

#include <iostream>

static void helpMenu() {
    std::cout << "\nThis calculator can take in any positive number and perform powers (^), multiplication (*), division (/), modulo (%), addition (+) and subtraction (-).\n" << std::endl; 
    std::cout << "It is compatible with parenthesis but does not understand that two parenthesis together is multiplication.\n\n" << std::endl;
    std::cout << "An example problem: (8+8)*8*8/8^8\n\n" << std::endl;
    std::cout << "The program will ignore any input that isn't a number or valid operation.\n\n" << std::endl;
}

int main(int argc, char** argv)
{
    bool printInfix{ false };
    bool printPostfix{ false };
    std::string infixString{ "" };

    if (argc < 2)
    {
        std::cout << "Not enough arguments found!" << std::endl;
        return 1;
    }

    for (int i{ 1 }; i < argc; ++i)
    {
        if (strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "--help") == 0)
        {
            helpMenu();
            return 0;
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            printInfix = true;
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            printPostfix = true;
        }
        else
        {
            infixString = argv[i];
        }
    }

    try
    {
        std::deque<std::string> infixDeque{ makeInfixDeque(infixString, printInfix) };
        std::deque<std::string> postfixDeque{ makePostfixDeque(infixDeque, printPostfix) };
        int finalResult{ makeFinalResult(postfixDeque) };
        std::cout << "Result: " << finalResult << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}