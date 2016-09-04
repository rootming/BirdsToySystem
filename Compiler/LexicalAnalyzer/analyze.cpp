#include "analyze.h"
#include <fstream>
#include <cstring>
#include <algorithm>


static const vector<string> keyTable = {
    "char", "int", "short", "long", "float", "double", "void",
    "auto", "unsigned", "unsigned", "register", "static", "volatile", "extern", "const",
    "struct", "union", "enum", "typedef",
    "if", "else", "for", "while", "do", "switch", "case", "break", "continue", "default", "goto", "return",
    "sizeof"
};

//static const char *keyTable[] = {
//    "char", "int", "short", "long", "float", "double", "void",
//    "auto", "unsigned", "unsigned", "register", "static", "volatile", "extern", "const",
//    "struct", "union", "enum", "typedef",
//    "if", "else", "for", "while", "do", "switch", "case", "break", "continue", "default", "goto", "return",
//    "sizeof"
//};

bool Analyzer::keyCheck(const string &data)
{
    auto it = find(keyTable.begin(), keyTable.end(), data);
    if(it != keyTable.end())
        return true;
    else
        return false;
}

void Analyzer::blankCheck(size_t &position, const Line &data)
{
    while(data.line[position] == ' ' || data.line[position] == '\t')
        position++;
}

bool Analyzer::letterCheck(const size_t &position, const Line &data)
{
    char c;
    c = data.line[position];
    if(('A' <= c && c <= 'Z') ||  ('a' <= c && c <= 'z'))
        return true;
    else
        return false;

}

bool Analyzer::digitCheck(const size_t &position, const Line &data)
{
    char c;
    c = data.line[position];
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
    ifstream file(filename);
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
    cout << "Raw data:" << endl;
    for(auto it: text){
        cout << it.num << ":" << it.line << endl;
    }
}


void Analyzer::showResult()
{
    for(auto it: resultTable){
        cout << "<" << it.first << ", " << it.second << ">" << endl;
    }
}

void Analyzer::showError()
{
    cout << "Count error:" << errorTable.size() << endl;
    for(auto it: errorTable){
        cout << "Line: " << it.line << ", Error: " << it.info << endl;
    }


}
bool Analyzer::analyze()
{
    cout << "Total: " << text.size() << " line(s)" << endl;
    for(auto i: text){
        cout << "Analyzing Line: " << i.num << endl;
        tokenDivide(i.num);
    }

    return true;
}

void Analyzer::tokenDivide(const size_t &lineNumber)
{
    size_t position = 0;
    string token;                       //token buffer
    Line temp = text.at(lineNumber);
    while(position < temp.line.length()){
        blankCheck(position, temp);
        switch(temp.line[position]){
        case 'a' ... 'z':
        case 'A' ... 'Z':
            while(letterCheck(position, temp) || digitCheck(position, temp))
                token.push_back(temp.line[position++]);  //push char to token buffer, and move position to next
            if(keyCheck(token)){
                resultTable.push_back(Unit("Key", "_"));
            }
            else{
                idTable.push_back(token);
                resultTable.push_back(Unit(token, idTable.size() - 1));
            }
            break;

        case '0' ... '9':
            //float double type will error, I will fix it later.
            while(digitCheck(position, temp)){
                 token.push_back(temp.line[position++]);  //push char to token buffer, and move position to next
            }
            numTable.push_back(token);
            resultTable.push_back(Unit("num", numTable.size() - 1));
            break;

        case '<':
            if(temp.line[position + 1] == '='){
                resultTable.push_back(Unit("relop", "LE"));
                position += 2;
            }
            else if(temp.line[position + 1] == '<'){
                resultTable.push_back(Unit("relop", "LSHIFT"));
                position += 2;
            }
            else{
                resultTable.push_back(Unit("<", "_"));
                position++;
            }
            break;
        case '>':
            if(temp.line[position + 1] == '='){
                resultTable.push_back(Unit("relop", "RE"));
                position += 2;
            }
            else if(temp.line[position + 1] == '>'){
                resultTable.push_back(Unit("relop", "RSHIFT"));
                position += 2;
            }
            else{
                resultTable.push_back(Unit(">", "_"));
                position++;
            }
            break;
        case '=':
            if(temp.line[position + 1] == '='){
                resultTable.push_back(Unit("relop", "EQ"));
                position += 2;
            }
            else{
                resultTable.push_back(Unit("=", "_"));
                position++;
            }

            break;
        case '+':
            if(temp.line[position + 1] == '='){
                resultTable.push_back(Unit("relop", "SELFADD"));
                position += 2;
            }
            else{
                resultTable.push_back(Unit("+", "_"));
                position++;
            }
            break;
        case '-':
            if(temp.line[position + 1] == '='){
                resultTable.push_back(Unit("relop", "SELFSUB"));
                position += 2;
            }
            else{
                resultTable.push_back(Unit("-", "_"));
                position++;
            }
            break;
        case '*':
            if(temp.line[position + 1] == '='){
                resultTable.push_back(Unit("relop", "SELFMULT"));
                position += 2;
            }
            else{
                resultTable.push_back(Unit("*", "_"));
                position++;
            }
            break;
        case '/':
            if(temp.line[position + 1] == '='){
                resultTable.push_back(Unit("relop", "SELFDIV"));
                position += 2;
            }
            else{
                resultTable.push_back(Unit("/", "_"));
                position++;
            }
            break;
        case '%':
            if(temp.line[position + 1] == '='){
                resultTable.push_back(Unit("relop", "SELFMOD"));
                position += 2;
            }
            else{
                resultTable.push_back(Unit("%", "_"));
                position++;
            }
            break;
        case '&':
            if(temp.line[position + 1] == '='){
                resultTable.push_back(Unit("relop", "SELFAND"));
                position += 2;
            }
            else if(temp.line[position + 1] == '&'){
                resultTable.push_back(Unit("relop", "LOGICAND"));
                position += 2;
            }
            else{
                resultTable.push_back(Unit("&", "_"));
                position++;
            }
            break;
        case '|':
            if(temp.line[position + 1] == '='){
                resultTable.push_back(Unit("relop", "SELFOR"));
                position += 2;
            }
            else if(temp.line[position + 1] == '|'){
                resultTable.push_back(Unit("relop", "LOGICOR"));
                position += 2;
            }
            else{
                resultTable.push_back(Unit("|", "_"));
                position++;
            }
            break;
        case '^':
            if(temp.line[position + 1] == '='){
                resultTable.push_back(Unit("relop", "SELFXOR"));
                position += 2;
            }
            else{
                resultTable.push_back(Unit("-", "^"));
                position++;
            }
            break;
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
            //not done, I will fix it later.
            resultTable.push_back(Unit(temp.line[position], "_"));
            position++;
            break;
        default:
//            errorTable.push_back(Error(lineNumber, "Error syntax"));
            position++;
            break;

        }
        token = "";
    }
}
