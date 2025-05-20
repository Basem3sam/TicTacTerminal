#pragma once
#include <string>

class Player {
private:
    std::string RULE;
    char symbol;
    int score = 0;

protected:
    explicit Player(const std::string& RULE);

public:
    virtual ~Player() = default;

    void setSymbol(char symbol);
    char getSymbol() const;

    void setScore(int score);
    int getScore() const;
    void incrementScore();

    std::string getRule() const;

    virtual std::string getName() const = 0;
};
