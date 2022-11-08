#include "../function.h"

#define FUNC __declspec(dllexport)

std::vector<function*> functions;

extern "C" FUNC std::vector<function*>&getFunctions(void) {

    function* power, * sin, * cos, * tg;

    power = new function("^", functionType::binary, (int)priority::func,
        [](double a, double b) -> double { return std::pow(b, a); });
    functions.push_back(power);

    sin = new function("sin", functionType::unary, (int)priority::func,
        [](double a, double b) -> double { return std::sin(a); });
    functions.push_back(sin);

    cos = new function("cos", functionType::unary, (int)priority::func,
        [](double a, double b) -> double { return std::cos(a); });
    functions.push_back(cos);

    tg = new function("tg", functionType::unary, (int)priority::func,
        [](double a, double b) -> double { return std::tan(a); });
    functions.push_back(tg);

    return functions;
};