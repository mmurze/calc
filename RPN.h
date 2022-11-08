#ifndef CALCUULATOR_RPN_H
#define CALCUULATOR_RPN_H

#include "symbol.h"
#include "function.h"
#include <iostream>
#include <new>
#include <queue>
#include <stack>
#include <optional>
#include <map>
#include <cstdlib>
#include <vector>


class RPN {
private:
    std::queue<symbol*> quequeOfSymbols;

    std::queue<symbol*> queueRPN; // there are symbols
    std::stack<symbol*> stackRPN; // there are operatoprs and functions

    std::stack<symbol*> numberStack;
public:
    RPN() = default;

    void FromStringToQueue(const std::string& str, const std::vector<function*>& functions);
    void FromQueueToRPN(const std::vector<function*>& functions);
    double FromRPNToResult();

    std::string getName(symbol* top);
    int getPriority(symbol* top);
    ~RPN();
};


#endif //CALCUULATOR_RPN_H
