#include "analyze.h"
#include <fstream>
#include <cstring>

using namespace std;

static const vector<string> keyTable = {
    "char", "int", "short", "long", "float", "double", "void",
    "auto", "unsigned", "unsigned", "register", "static", "volatile", "extern", "const",
    "struct", "union", "enum", "typedef",
    "if", "else", "for", "while", "do", "switch", "case", "break", "continue", "default", "goto", "return",
    "sizeof",
    "+", "-", "*", "/", "<", ">"
};

//static const char *keyTable[] = {
//    "char", "int", "short", "long", "float", "double", "void",
//    "auto", "unsigned", "unsigned", "register", "static", "volatile", "extern", "const",
//    "struct", "union", "enum", "typedef",
//    "if", "else", "for", "while", "do", "switch", "case", "break", "continue", "default", "goto", "return",
//    "sizeof"
//};

void Analyzer::blankCheck(size_t &position, const Line &data)
{
    while(data.line.c_str()[position] == ' ' || data.line.c_str()[position] == '\t')
        position++;
}

bool Analyzer::letterCheck(const size_t &position, const Line &data)
{
    char c;
    c = data.line.c_str()[position];
    if(('A' <= c && c <= 'Z') ||  ('A' <= c && c <= 'Z'))
        return true;
    else
        return false;

}

bool Analyzer::digitCheck(const size_t &position, const Line &data)
{
    char c;
    c = data.line.c_str()[position];
    if('0' <= c && c <= '9')
        return true;
    else
        return false;
}

Analyzer::Analyzer()
{

}

void Analyzer::open(std::string filename)
{
    size_t number = 0;
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

bool Analyzer::analyze()
{
    for(auto i: text){
        tokenDivide(i.num);
    }

    return true;
}

void Analyzer::tokenDivide(size_t lineNumber)
{
    size_t position = 0;
    string token;                       //token buffer
    Line temp = text.at(lineNumber);
    for(; position < temp.line.length(); position++){
        blankCheck(position, temp);
        switch(temp.line.c_str()[position]){
        case 'a' ... 'z':
        case 'A' ... 'Z':
            while(letterCheck(position, temp) || digitCheck(position, temp))
                token.push_back(temp.line.c_str()[position++]);  //push char to token buffer, and move position to next

            break;
        case '0' ... '9':
            break;

        case '+':
        case '-':
        case '*':
        case '/':
        case '<':
        case '>':
        case '=':
        case '%':
        case '&':
        case '|':
        case '^':
        case '(':
        case ')':
        case '\\':
        case '[':
        case ']':
        case '{':
        case '}':
        case ';':
        case '"':
        case '.':
        case ',':
        case '!':
        case '?':
            break;

        }
    }
}
