#include "function.h"

function::function(std::string _name, functionType _type, int _priority, std::function<double(double, double)> _func)
{
    priority = _priority;
    name = _name;
    type = _type;
    func = _func;
}
function* function::findFuncByName(const std::string& name, const std::vector<function*>& functions) {
    function* func = nullptr;
    for (auto& f : functions) {
        if (f->getName() == name) {
            func = f;
            break;
        }
    }
    return func;
}
double function::compute(double firstNumber, double secondNumber) {

    double result;
    try {
        result = this->func(firstNumber, secondNumber);
    }
    catch (const std::exception& exception) {
        throw exception;
    }
    return result;

}
