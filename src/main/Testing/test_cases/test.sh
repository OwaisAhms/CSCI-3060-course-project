#! /bin/bash

g++ test.cpp ../../User.cpp -o test.exe -I"C:\msys64\ucrt64\include" -L"C:\msys64\ucrt64\lib" -lgtest_main -lgtest
start ./test.exe