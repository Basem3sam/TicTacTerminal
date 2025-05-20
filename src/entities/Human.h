#pragma once
#include "Player.h"
#include <string>

class Human : public Player {
private:
    std::string name;
    static short nextId;
    short id;

    void setName(std::string name);

public:
    Human();
    Human(const std::string& name);

    short getId() const;
    std::string getName() const override;
    void setSymbol(char symbol);
    int getScore();
    char getSymbol();
    void incrementScore();
    static void resetIdCounter();
};
