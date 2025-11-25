#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
#include "header.hpp"
int main(int argc, char *argv[])
{
    string boss_looks;
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        //i think ive heard that this is default on linux
    #endif
    int seed;
    if (argc > 1 && isdigit(argv[1][0])){
        seed = stoi(argv[1]);
    } else {
        seed = time(NULL);
    }
    PsRandField(seed);
}