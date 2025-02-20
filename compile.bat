@echo off

if not exist out (
    mkdir out
)

g++ -o ./out/bakery.exe -std=c++17 ./src/main.cpp