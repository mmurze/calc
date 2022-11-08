#include <crtdbg.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "calculator.h"

int main(int arg, char* argv[]) {
    std::string str;
    double result = 0;


    while (getline(std::cin, str)) {
        try {
            calculator calc(str);
            result = calc.result;
        }
        catch (const std::exception& exception) {
            std::cout << str << " = " << "Error: " << exception.what() << std::endl;
            continue;
        }

        std::cout << str << " = " << result << std::endl;
    }
    return 0;
}