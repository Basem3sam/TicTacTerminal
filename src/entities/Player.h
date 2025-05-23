#pragma once
#include <string>

class Player {
private:
    const std::string RULE;
    char symbol = '\0';
    int score = 0;
    short id = -1;

protected:
    explicit Player(const std::string& rule);

public:
    virtual ~Player() = default;

    void setSymbol(char symbol);
    char getSymbol() const;

    void setScore(int score);
    int getScore() const;

    void setId(short id);
    virtual short getId() const;

    void incrementScore();

    std::string getRule() const;

    virtual std::string getName() const = 0;
};
