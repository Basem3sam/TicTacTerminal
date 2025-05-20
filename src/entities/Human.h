#pragma once
#include "Player.h"
#include <string>

class Human : public Player{
  std::string name;
  static short nextId;
  short id;

  void setName(std::string name);
  public:
    Human();
    Human(const std::string& name);
    short getId();
    std::string getName();
    void setSymbol(char symbol);
    int getScore();
    char getSymbol();
    void incrementScore();
    static void resetIdCounter();
  };
