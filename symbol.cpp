#include "symbol.h"

symbolNumber::symbolNumber()
{
    value = 0;
    type = symbolType::number;
}

symbolOper::symbolOper()
{
    func = nullptr;
    oper = ' ';
    type = symbolType::oper;
}

symbolFunc::symbolFunc()
{
    func = nullptr;
    type = symbolType::functions;
}
