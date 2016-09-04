#include <iostream>
#include "analyze.h"

using namespace std;

int main(int argc, char *argv[])
{
    Analyzer test;
    test.open("test.txt");
    test.showRaw();
    test.analyze();
    test.showResult();
    test.showError();
    return 0;
}
