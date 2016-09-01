#pragma once
#include <iostream>
#include <vector>

#define LINE_LENGTH_LIMIT 200

class Analyzer
{
public:
    Analyzer();
    void open(std::string filename);
    void showRaw();
    bool analyzer();
private:
    struct Line
    {
        int num;
        std::string line;
        Line(int num, std::string line)
        {
            this->num = num;
            this->line = line;
        }
    };

    std::vector<Line> text;
    std::vector<int> idTable;
    std::vector<std::string> numTable;
    void tokenDivide(int line);
};
