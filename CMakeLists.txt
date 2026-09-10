cmake_minimum_required(VERSION 3.20)
project(Snack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Snack
src/main.cpp
src/Point.cpp
src/Snack.cpp
src/UI.cpp)

target_include_directories(Snack PRIVATE include)

enable_testing()
add_executable(unit_tests
tests/test_main.cpp
tests/test_point.cpp
tests/test_snack.cpp
src/Point.cpp
src/Snack.cpp
)
target_include_directories(unit_tests PRIVATE include tests)
add_test(NAME unit_tests COMMAND unit_tests)

# 编码参数：MSVC 用 /utf-8，g++ 用 -finput/-fexec-charset，统一按 UTF-8 读写源码
if(MSVC)
    set(SNACK_UTF8_FLAGS /utf-8)
else()
    set(SNACK_UTF8_FLAGS -finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

target_compile_options(Snack PRIVATE ${SNACK_UTF8_FLAGS})
target_compile_options(unit_tests PRIVATE ${SNACK_UTF8_FLAGS})