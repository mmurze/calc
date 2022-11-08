#include "loader.h"

void loader::basicFunctions(void) {

    function* plus, * minus, * mul, * div, * unarMinus, * openBracket, * closeBrachket;

    try {
        openBracket = new function("(", functionType::unary, (int)priority::first, nullptr);
    }
    catch (const std::bad_alloc) {
        throw  std::exception("Not enough memory for allocation");
    }
    functions.push_back(openBracket);

    try {
        closeBrachket = new function(")", functionType::unary, (int)priority::second, nullptr);
    }
    catch (const std::bad_alloc) {
        throw  std::exception("Not enough memory for allocation");
    }
    functions.push_back(closeBrachket);

    try {
        plus = new function("+", functionType::binary, (int)priority::third,
            [](double a, double b) -> double {return a + b; });
    }
    catch (const std::bad_alloc) {
        throw  std::exception("Not enough memory for allocation");
    }
    functions.push_back(plus);

    try {
        minus = new function("-", functionType::binary, (int)priority::third,
            [](double a, double b) -> double {return b - a; });
    }
    catch (const std::bad_alloc) {
        throw  std::exception("Not enough memory for allocation");
    }
    functions.push_back(minus);

    try {
        mul = new function("*", functionType::binary, (int)priority::fourth,
            [](double n1, double n2) -> double {return n1 * n2; });
    }
    catch (const std::bad_alloc) {
        throw  std::exception("Not enough memory for allocation");
    }
    functions.push_back(mul);

    try {
        div = new function("/", functionType::binary, (int)priority::fourth,
            [](double n1, double n2) -> double { if (n1 == 0)
            throw std::exception("Division by zero"); return n2 / n1; });
    }
    catch (const std::bad_alloc) {
        throw  std::exception("Not enough memory for allocation");
    }
    functions.push_back(div);

    try {
        unarMinus = new function("--", functionType::unary, (int)priority::fifth,
            [](double n1, double n2) -> double { return -n1; });
    }
    catch (const std::bad_alloc) {
        throw std::exception( "Not enough memory for allocation");
    }
    functions.push_back(unarMinus);
}

void loader::DLLFunctions() {
    std::vector<std::filesystem::path> filePaths;
    for (auto& file : std::filesystem::directory_iterator("DLLfunc/"))
        filePaths.push_back(file.path());

    std::vector<function*> tmpFunctions;
    for (auto& file : filePaths) {

        if (file.extension() != ".dll")
            continue;

        HMODULE dllAdress = LoadLibrary((LPCSTR)file.string().c_str());
        dllsHandlers.push_back(dllAdress);
        if (dllAdress == nullptr)
            continue;
        functionPointer getFunctions = (functionPointer)GetProcAddress(dllAdress, "getFunctions");
        
        tmpFunctions = getFunctions();
        while (tmpFunctions.size() != 0) {
            functions.push_back(tmpFunctions.back());
            tmpFunctions.pop_back();
        }
    }
}

void loader::createFuncVector() {
    try {
        basicFunctions();
    }
    catch (const std::exception& exception) {
        throw exception;
    }
    try {
        DLLFunctions();
    }
    catch (const std::exception& exception) {
        throw exception;
    }
}

loader::~loader() {
    while (!functions.empty()) {
        auto* off = functions.back();
        functions.pop_back();
        delete off;
    }

}
