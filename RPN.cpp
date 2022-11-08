#include "RPN.h"
using namespace std::string_literals;
void RPN::FromStringToQueue(const std::string& str, const std::vector<function*>& functions) {
    int pos = 0;
    int countOpenBracket = 0;
    int countCloseBracket = 0;

    while (str.length() > pos) {
        //check whitespace
        while (str[pos] == ' ') {
            pos++;
            continue;
        }

        //check letters
        std::string funcName = "";
        while (str.length() > pos && (str[pos] <= 'Z' && str[pos] >= 'A') || (str[pos] <= 'z' && str[pos] >= 'a'))
            funcName += str[pos++];
        if (funcName != "") {
            //check is it PI or not
            if (funcName == "pi" || funcName == "PI") {
                symbolNumber* number = nullptr;
                try {
                    number = new symbolNumber;
                }
                catch (const std::bad_alloc& e) {
                    std::cout << "Allocation failed: " << e.what() << '\n';
                }
                number->value = PI;
                quequeOfSymbols.push(number);
                continue;
            }

            //check is it function
            function* func = function::findFuncByName(funcName, functions);
            symbolFunc* sFunc = nullptr;
            if (func == nullptr)
                std::cout << "Function is unknown" << '\n';
            else {
                try {
                    sFunc = new symbolFunc;
                }
                catch (const std::bad_alloc& e) {
                    std::cout << "Allocation failed: " << e.what() << '\n';
                }
                sFunc->func = func;
                quequeOfSymbols.push(sFunc);
            }
        }

        double value = 0;
        //check numbers and operations
        switch (str[pos]) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
        case '.': {
            //collecting a number(double)
            std::string number = "";
            while (str.length() > pos && ((str[pos + 1] >= '0' && str[pos + 1] <= '9') || str[pos + 1] == '.' || str[pos + 1] == ',')) {
                if (str[pos] == ',')
                    number += '.';
                else
                    number += str[pos++];
            }
            number += str[pos++];

            //convert to double
            symbolNumber* sNumber = nullptr;
            try {
                sNumber = new symbolNumber;
            }
            catch (const std::bad_alloc& e) {
                std::cout << "Allocation failed: " << e.what() << '\n';
            }
            sNumber->value = std::stod(number);
            quequeOfSymbols.push(sNumber);
            break;
        }
        case '+':
        case '-':
        case '/':
        case '*':
        case '^':
        case ')':
        case '(': {

            //count a number of bracket
            if (str[pos] == '(')
                countOpenBracket++;
            if (str[pos] == ')')
                countCloseBracket++;


            function* func = function::findFuncByName(std::string{ str[pos] }, functions);
            symbolOper* sOper = nullptr;
            if (func == nullptr)
                throw "Function is unknown";
            else if (func->getName() == "-" && (pos == 0 || (pos != 0 && str[pos - 1] == '(' ))) {
                try {
                    sOper = new symbolOper;
                }
                catch (const std::bad_alloc& e) {
                    std::cout << "Allocation failed: " << e.what() << '\n';
                }
                
                std::string name = "--";
                func = function::findFuncByName(name, functions);
                sOper->type = symbolType::oper;
                sOper->func = func;
                sOper->oper = str[pos++];
                quequeOfSymbols.push(sOper);
            }
            else {
                try {
                    sOper = new symbolOper;
                }
                catch (const std::bad_alloc& e) {
                    std::cout << "Allocation failed: " << e.what() << '\n';
                }
                sOper->func = func;
                sOper->oper = str[pos++];
                quequeOfSymbols.push(sOper);
            }
            break;
        }
        default:
            throw std::exception("Symbol is unknown ");
            break;
        }
    }

    if (countOpenBracket != countCloseBracket) {
        throw std::exception("Incorrect number of brackets");
    }
}


void RPN::FromQueueToRPN(const std::vector<function*>& functions) {
    int pos = 0;
    while (!quequeOfSymbols.empty()) {

        if (quequeOfSymbols.front()->type == symbolType::number) 
            queueRPN.push(quequeOfSymbols.front());

        else if (quequeOfSymbols.front()->type == symbolType::oper) {
            std::string tmpName = getName(quequeOfSymbols.front());
            if (tmpName == "(");

            else if (tmpName == ")") {
                while (!stackRPN.empty() && getName(stackRPN.top()) != "(") {
                    queueRPN.push(stackRPN.top());
                    stackRPN.pop();
                }
                stackRPN.pop();
            }

            else if (!stackRPN.empty()) {
                while (!stackRPN.empty() && getPriority(stackRPN.top()) >= getPriority(quequeOfSymbols.front())) {
                    queueRPN.push(stackRPN.top());
                    stackRPN.pop();
                }
            }

            if (tmpName != ")")
                stackRPN.push(quequeOfSymbols.front());
        }

        else if (quequeOfSymbols.front()->type == symbolType::functions) {
            while (!stackRPN.empty() && getPriority(stackRPN.top()) == getPriority(quequeOfSymbols.front())) {
                queueRPN.push(stackRPN.top());
                stackRPN.pop();
            }
            stackRPN.push(quequeOfSymbols.front());
        }
        else {
            throw std::exception("Symbol is unknown");
            break;
        }
        quequeOfSymbols.pop();
    }

    while (!stackRPN.empty()) {
        queueRPN.push(stackRPN.top());
        stackRPN.pop();
    }

}

double RPN::FromRPNToResult() {
    while (!queueRPN.empty()) {
     
        symbol* tmp = queueRPN.front();
        symbol* sym, * sym2;
        function* func;
        switch (tmp->type) {
        case symbolType::number:
            numberStack.push(tmp);
            queueRPN.pop();
            break;

        case symbolType::oper:
        case symbolType::functions:
            if (tmp->type == symbolType::functions) 
                func = ((symbolFunc*)tmp)->func;
            
            else 
                func = ((symbolOper*)tmp)->func;
            
            switch (func->getType()) {  
            case functionType::unary:

                try {
                    sym = numberStack.top();
                    numberStack.pop();
                }
                catch (const std::exception& exception) {
                    throw exception;
                }
                try {
                    ((symbolNumber*)sym)->value = func->compute(((symbolNumber*)sym)->value, 0);
                }
                catch (const std::exception& exception) {
                    throw exception;
                }
                numberStack.push(sym);
                queueRPN.pop();
                break;

            case functionType::binary:
                sym = numberStack.top();
                numberStack.pop();
                sym2 = numberStack.top();
                numberStack.pop();
                try {
                    ((symbolNumber*)sym)->value = func->compute(((symbolNumber*)sym)->value, ((symbolNumber*)sym2)->value);
                }
                catch (const std::exception& exception) {
                    throw exception;
                }
                numberStack.push(sym);
                queueRPN.pop();
                break;
            }
        }
       
    }

    if (numberStack.size() != 1 || numberStack.top()->type != symbolType::number)
        throw std::exception("Error in counting of expression");

    return ((symbolNumber*)numberStack.top())->value;
}

std::string RPN::getName(symbol* top) {
    switch (top->type) {
    case symbolType::oper: {
        symbolOper* stackOper = (symbolOper*)top;
        std::string stackName = stackOper->func->getName();
        return stackName;
    }
    case symbolType::functions: {
        symbolFunc* stackFunc = (symbolFunc*)top;
        std::string stackName = stackFunc->func->getName();
        return stackName;
    }
    }
}


int RPN::getPriority(symbol* top) {
    switch (top->type) {
    case symbolType::oper: {
        symbolOper* stackOper = (symbolOper*)top;
        int stackName = stackOper->func->getPriority();
        return stackName;
    }
    case symbolType::functions: {
        symbolFunc* stackFunc = (symbolFunc*)top;
        int stackName = stackFunc->func->getPriority();
        return stackName;
    }
    }
    return 0;
}

RPN::~RPN() {
    while (!quequeOfSymbols.empty()) {
        auto* off = quequeOfSymbols.front();
        quequeOfSymbols.pop();
        delete off;
    }
    while (!queueRPN.empty()) {
        auto* off = queueRPN.front();
        queueRPN.pop();
        delete off;
    }
    while (!stackRPN.empty()) {
        auto* off = stackRPN.top();
        quequeOfSymbols.pop();
        delete off;
    }
    while (!numberStack.empty()) {
        auto* off = numberStack.top();
        numberStack.pop();
        delete off;
    }
}
