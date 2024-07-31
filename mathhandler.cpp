#include "mathhandler.h"

#include <string>
#include <deque>
#include <iostream>
#include <algorithm>
#include <stdexcept>

std::deque<std::string> makeInfixDeque(const std::string& infixString, const bool& printInfix)
{
	std::deque<std::string> brokenEquation{};
	std::string temp{};

	for (int i{ 0 }; i < infixString.size(); ++i)
	{
		char ch{ infixString.at(i) };

		if (std::isdigit(ch) || ch == '.')
		{
			temp += ch;
		}
		else
		{
			if (!temp.empty())
			{
				brokenEquation.push_back(temp);
				temp.clear();
			}
			switch (ch)
			{
			case '(':
			case ')':
			case '^':
			case '*':
			case '/':
			case '%':
			case '+':
			case '-':
				brokenEquation.push_back(std::string(1, ch));
				break;
			default:
				break;
			}
		}
	}

	if (!temp.empty())
	{
		brokenEquation.push_back(temp);
	}

	if (printInfix == true)
	{
		std::cout << "Infix: ";
		for (int i{ 0 }; i < brokenEquation.size(); i++)
		{
			std::cout << brokenEquation.at(i);
		}
		std::cout << std::endl;
	}
	return brokenEquation;
}

std::deque<std::string> makePostfixDeque(const std::deque<std::string>& infixDequeArg, const bool& printPostfix)
{
	std::deque<std::string> infixDeque{ infixDequeArg };
	std::deque<std::string> postfixDeque{};
	std::deque<std::string> operatorStack{};
	std::string temp{};

	auto handleOperator = [&](const std::string& op, const std::vector<std::string>& higherPrecedenceOps)
	{
		while (!operatorStack.empty())
		{
			const std::string& top{ operatorStack.front() };
			if (std::find(higherPrecedenceOps.begin(), higherPrecedenceOps.end(), top) != higherPrecedenceOps.end())
			{
				postfixDeque.push_back(top);
				operatorStack.pop_front();
			}
			else
			{
				break;
			}
		}
		operatorStack.push_front(op);
	};

	for (int i{ 0 }; i < infixDeque.size(); i++)
	{
		switch (infixDeque.at(i)[0])
		{
		case '(':
			operatorStack.push_front("(");
			break;
		case ')':
			while (operatorStack.front() != "(")
			{
				postfixDeque.push_back(operatorStack.front());
				operatorStack.pop_front();
			}
			operatorStack.pop_front();
			break;
		case '^':
			operatorStack.push_front("^");
			break;
		case '*':
			handleOperator("*", { "^", "*", "/", "%" });
			break;
		case '/':
			handleOperator("/", {"^", "*", "/", "%" });
			break;
		case '%':
			handleOperator("%", { "^", "*", "/", "%" });
			break;
		case '+':
			handleOperator("+", { "^", "*", "/", "%", "+", "-"});
			break;
		case '-':
			handleOperator("-", { "^", "*", "/", "%", "+", "-" });
			break;
		default:
			if (std::isdigit(infixDeque.at(i)[0]) || infixDeque.at(i)[0] == '.')
			{
				postfixDeque.push_back(infixDeque.at(i));
			}
			break;
		}
	}
	for (; !operatorStack.empty(); operatorStack.pop_front())
	{
		postfixDeque.push_back(operatorStack.front());
	}

	if (printPostfix == true)
	{
		std::cout << "Postfix: ";
		for (int i{ 0 }; i < postfixDeque.size(); i++)
		{
			std::cout << postfixDeque.at(i);
		}
		std::cout << std::endl;
	}
	return postfixDeque;
}

int makeFinalResult(const std::deque<std::string>& postfixDequeArg)
{
	auto doOperation = [](int x, int y, char op)
		{
			int result{};
			switch (op)
			{
			case '^':
				result = pow(x, y);
				break;
			case '*':
				result = x * y;
				break;
			case '/':
				if (y == 0)
				{
					throw std::overflow_error("Division by 0 is undefined behavior!");
					break;
				}
				result = x / y;
				break;
			case '%':
				result = x % y;
				break;
			case '+':
				result = x + y;
				break;
			case '-':
				result = x - y;
				break;
			default:
				break;
			}
			return result;
		};

	std::deque<std::string> finalPostfixDeque{ postfixDequeArg };
	int sum{};

	while (finalPostfixDeque.size() > 1)
	{
		for (int finalResultIterator{ 0 }; finalResultIterator < finalPostfixDeque.size(); finalResultIterator++)
		{
			if (finalPostfixDeque.at(finalResultIterator) == "^" || finalPostfixDeque.at(finalResultIterator) == "*" || finalPostfixDeque.at(finalResultIterator) == "/" || finalPostfixDeque.at(finalResultIterator) == "%" || finalPostfixDeque.at(finalResultIterator) == "+" || finalPostfixDeque.at(finalResultIterator) == "-")
			{
				int numX{};
				int numY{};
				try
				{
					numX = std::stoi(finalPostfixDeque.at(finalResultIterator - 2));
					numY = std::stoi(finalPostfixDeque.at(finalResultIterator - 1));
				}
				catch (const std::out_of_range)
				{
					throw std::out_of_range("Invalid Input Detected!");
				}

				char newOp{ finalPostfixDeque.at(finalResultIterator)[0] };
				finalPostfixDeque.at(finalResultIterator) = std::to_string(doOperation(numX, numY, newOp));
				finalPostfixDeque.erase(finalPostfixDeque.begin() + (finalResultIterator - 1));
				finalPostfixDeque.erase(finalPostfixDeque.begin() + (finalResultIterator - 2));
				finalResultIterator = 0;
			}
		}
	}
	sum = std::stoi(finalPostfixDeque.front());
	return sum;
}