#include "analyze.h"
#include <fstream>
#include <cstring>

using namespace std;

static const char *keyTable[] = { "char", "int", "short", "long", "float", "double", "void",
                                      "auto", "unsigned", "unsigned", "register", "static", "volatile", "extern", "const",
                                      "struct", "union", "enum", "typedef",
                                      "if", "else", "for", "while", "do", "switch", "case", "break", "continue", "default", "goto", "return",
                                      "sizeof"
                                };
Analyzer::Analyzer()
{

}

void Analyzer::open(std::string filename)
{
    int number = 0;
    char buffer[LINE_LENGTH_LIMIT];
    ifstream file(filename.c_str());
    string line;

    if(file.is_open()){
        while(!file.eof()){
            file.getline(buffer, LINE_LENGTH_LIMIT);
            line = buffer;
            text.push_back(Line(number++, line));
            memset(buffer, '\0', LINE_LENGTH_LIMIT);
        }
    }
    else{
        cerr << "Open:" << filename << " failed" << endl;
    }

    file.close();

}

void Analyzer::showRaw()
{
    for(auto it: text){
        cout << it.num << ":" << it.line << endl;
    }
}

