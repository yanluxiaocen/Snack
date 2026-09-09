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

if(MSVC)
    target_compile_options(Snack PRIVATE /utf-8)
else()
    target_compile_options(Snack PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()