#pragma once
#include <string>

class Player {
private:
    std::string RULE;
    char symbol;
    int score = 0;

protected:
    explicit Player(const std::string& RULE);

    void setScore(int score);
    void setSymbol(char symbol);
    void incrementScore();

public:
    int getScore() const;
    char getSymbol() const;
    std::string getRule() const;
};
