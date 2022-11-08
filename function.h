#ifndef CALCUULATOR_FUNCTION_H
#define CALCUULATOR_FUNCTION_H

#include <string>
#include <functional>
#include <vector>
#include <iostream>
enum class functionType {
    unary,
    binary
};
enum class priority
{
    first,    /*  ( )       */
    second,   /*   + -      */
    third,    /*   * \      */
    fourth,   /*   unary -  */
    fifth,    /*   ^        */
    func      /*   functions*/
};


class function {
private:
    std::function <double(double, double)> func;
    functionType type;
    std::string name;
    int priority;
public:
    function() = default;
    function(std::string name, functionType type, int priority, std::function <double(double, double)> func);

    static function* findFuncByName(const std::string& name, const std::vector <function*>& functions);
    double compute(double firstNumber, double secondNumber);
    std::string getName() { return name; };
    void setName(std::string& _name) { name = _name; };

    functionType getType() { return type; };
    void setType(functionType _type) { type = _type; };

    int getPriority() { return priority; };
};

#endif //CALCUULATOR_FUNCTION_H
