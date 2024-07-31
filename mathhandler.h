#ifndef MATHHANDLER_H
#define MATHHANDLER_H

#include <string>
#include <queue>

std::deque<std::string> makeInfixDeque(const std::string& infixString, const bool& printInfix);
std::deque<std::string> makePostfixDeque(const std::deque<std::string>& infixDequeArg, const bool& printPostfix);
int makeFinalResult(const std::deque<std::string>& postfixDequeArg);

#endif