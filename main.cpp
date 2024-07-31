#include "mathhandler.h"

#include <iostream>

static int welcomeMenu() 
{
    int selected{};
    int option{};
    bool activeMenu{ true };
    bool printInfix{ false };
    bool printPostfix{ false };

    while (activeMenu) 
    {
        std::cout << "1) Enter Calculator\n" << "2) Help\n" << "3) Exit" << std::endl;
        std::cin >> selected;

        while (std::cin.fail()) 
        {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cerr << "Invalid choice. Please try again." << std::endl;
            std::cout << "1) Enter Calculator\n" << "2) Help\n" << "3) Exit" << std::endl;
            std::cin >> selected;
        }

        switch (selected) 
        {
        case 1:
            option = 1;
            activeMenu = false;
            break;

        case 2:
            option = 2;
            activeMenu = false;
            break;

        case 3:
            option = 3;
            activeMenu = false;
            break;

        default:
            selected = 0;
            std::cerr << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
    activeMenu = true;
    return option;
}

static void helpMenu() {
    std::cout << "\nThis calculator can take in any positive number and perform powers (^), multiplication (*), division (/), modulo (%), addition (+) and subtraction (-).\n" << std::endl; 
    std::cout << "It is compatible with parenthesis but does not understand that two parenthesis together is multiplication.\n\n" << std::endl;
    std::cout << "An example problem: (8+8)*8*8/8^8\n\n" << std::endl;
    std::cout << "The program will ignore any input that isn't a number or valid operation.\n\n" << std::endl;
}

/*int main()
{
    bool appOpen{ true };

    while (appOpen) 
    {
        int choice{ welcomeMenu() };

        switch (choice) 
        {
        case 1:
        {
            std::string infixString{};
            std::cout << "Input your problem: " << std::endl;
            getline(std::cin >> std::ws, infixString);

            if (infixString.empty())
            {
                std::cerr << "Input cannot be empty. Please try again." << std::endl;
                break;
            }

            try
            {
                std::deque<std::string> infixDeque{ makeInfixDeque(infixString, true) };
                std::deque<std::string> postfixDeque{ makePostfixDeque(infixDeque, true) };
                int finalResult{ makeFinalResult(postfixDeque) };
                std::cout << "Result: " << finalResult << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << std::endl;   
            }
            break;
        }
        case 2:
            helpMenu();
            break;
        case 3:
            std::cout << "Exiting...\n";
            appOpen = false;
            break;
        default:
            std::cerr << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}*/

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