#pragma once
#include <iostream>
#include <vector>
#include <map>

#define LINE_LENGTH_LIMIT 200

class Analyzer
{
public:
    Analyzer();
    void open(std::string filename);
    void showRaw();
    bool analyze();
private:
    struct Line
    {
        size_t num;
        std::string line;

        Line()
        {
            this->num = 0;
            this->line = "";
        }

        Line(size_t num, std::string line)
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
        std::string first;
        std::string second;
        Unit(std::string first, std::string second)
        {
            this->first = first;
            this->second = second;
        }

    };

    std::vector<Line> text;
    std::vector<int> idTable;
    std::vector<std::string> numTable;

    void blankCheck(size_t &position, const Line &data);
    bool letterCheck(const size_t &position, const Line &data);
    bool digitCheck(const size_t &position, const Line &data);
    void tokenDivide(size_t lineNumber);
};
