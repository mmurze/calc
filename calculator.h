#ifndef CALCUULATOR_CALCULATOR_H
#define CALCUULATOR_CALCULATOR_H

#include "loader.h"
#include "RPN.h"
class calculator {
public:
    double result;
    loader loader;
    calculator() = default;
    calculator(std::string str);

};


#endif //CALCUULATOR_CALCULATOR_H
