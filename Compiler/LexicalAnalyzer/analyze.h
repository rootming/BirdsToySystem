#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

#define LINE_LENGTH_LIMIT 200

using namespace std;

class Analyzer
{
public:
    Analyzer();
    void open(string filename);
    void showRaw();
    void showResult();
    void showError();
    bool analyze();
private:
    struct Line
    {
        size_t num;
        string line;

        Line()
        {
            this->num = 0;
            this->line = "";
        }

        Line(size_t num, string line)
        {
            this->num = num;
            this->line = line;
        }

        Line(const Line &a)
        {
            this->num = a.num;
            this->line = a.line;
        }
    };

    struct Unit
    {
        string first;
        string second;
        Unit(string first, string second)
        {
            this->first = first;
            this->second = second;
        }

        Unit(char first, string second)
        {
            this->first = first;
            this->second = second;
        }

        Unit(string first, size_t second)
        {
            stringstream temp;
            temp << second;
            this->first = first;
            temp >> this->second;
        }

    };

    struct Error
    {
        size_t line;
        string info;
        Error(size_t line, string info)
        {
            this->line = line;
            this->info = info;
        }
    };

    vector<Line> text;
    vector<string> idTable;
    vector<string> numTable;
    vector<Unit> resultTable;
    vector<Error> errorTable;

    void blankCheck(size_t &position, const Line &data);
    bool letterCheck(const size_t &position, const Line &data);
    bool digitCheck(const size_t &position, const Line &data);
    void tokenDivide(const size_t &lineNumber);
    bool keyCheck(const string &data);
};
