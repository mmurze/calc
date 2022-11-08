#ifndef CALCUULATOR_LOADER_H
#define CALCUULATOR_LOADER_H

#include "function.h"
#include <filesystem>
#include <Windows.h>

using functionPointer = std::vector<function*>& (*)(void);


class loader {
private:
    std::vector<function*> functions;
    std::vector<HMODULE> dllsHandlers;
public:
    void basicFunctions();
    void DLLFunctions();
    void createFuncVector();

    std::vector<function*>& getFunctionsVector() { return  functions; };

    loader() = default;
    ~loader();
};

#endif //CALCUULATOR_LOADER_H
