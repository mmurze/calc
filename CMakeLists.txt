# CMakeList.txt: проект CMake для calculator_cmake; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("calculator_cmake")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (calculator_cmake "calculator_cmake.cpp"  "calculator.cpp" "calculator.h"  "function.cpp" "function.h" "loader.cpp" "loader.h" "RPN.cpp" "RPN.h" "symbol.cpp" "symbol.h")


# TODO: Добавьте тесты и целевые объекты, если это необходимо.

add_subdirectory("DLLfunc")
