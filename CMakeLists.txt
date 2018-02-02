cmake_minimum_required(VERSION 3.5)
project(prog)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    contest5/remove_copy_if.cpp
    contest5/reverse_copy.cpp
    contest5/set_difference.cpp
    contest5/unique.cpp
    contest6/a0.cpp
    contest6/a1.cpp
    contest6/a2.cpp
    contest6/a3.cpp
    contest6/a4.cpp
    contest6/a5.cpp
    contest6/a6.cpp
    contest6/a8.cpp
    contest6/a9.cpp
    contest7/a0.cpp
    contest7/a1.cpp
    contest7/checkmatrix.cpp
    contest7/Complex.cpp
    contest7/Matrix.cpp
    contest7/Rational.cpp
    "contest8/Polynomial(dense).cpp"
    "contest8/Polynomial(sparse).cpp"
    contest9/a0.cpp
    sortString/main.cpp
    sortLibrary.cpp
    startvim.cpp)

add_executable(prog ${SOURCE_FILES})