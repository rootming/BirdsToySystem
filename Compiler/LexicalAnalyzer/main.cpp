#include <iostream>
#include "analyze.h"

using namespace std;

int main(int argc, char *argv[])
{
    Analyzer test;
    test.open("test.c");
    test.showRaw();
    test.analyze();
    return 0;
}
