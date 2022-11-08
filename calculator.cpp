#include "calculator.h"

calculator::calculator(std::string str) {
    try {
        loader.createFuncVector();
    }
    catch (const std::exception& exception) {
        std::cout << "Calculator doesn't load functions";
        throw exception;
    }
    RPN result;

    try {
        result.FromStringToQueue(str, loader.getFunctionsVector());
    }
    catch (const std::exception& exception) {
        throw exception;
    }
    try {
        result.FromQueueToRPN(loader.getFunctionsVector());
    }
    catch (const std::exception& exception) {
        throw exception;
    }
    try {
        this->result = result.FromRPNToResult();
    }
    catch (const std::exception& exception) {
        throw exception;
    }

}