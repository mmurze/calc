#ifndef CALCUULATOR_SYMBOL_H
#define CALCUULATOR_SYMBOL_H

#include "function.h"

#define PI 3.141592653589793


enum class symbolType {
    number,
    oper, // operator
    functions
};

class symbol {
public:
    symbolType type;
};

class symbolNumber :public symbol {
public:
    double value;
    symbolNumber();
};

class symbolOper :public symbol {
public:
    function* func;
    char oper;
    symbolOper();
};

class symbolFunc :public symbol {
public:
    function* func;
    symbolFunc();
};



#endif //CALCUULATOR_SYMBOL_H
