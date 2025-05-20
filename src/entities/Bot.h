#pragma once
#include "Player.h"

class Bot : public Player {
  std::string name;

  public:
    Bot(const std::string& name = "BOT") : Player("Bot"), name(name) {}
    short getId() const { return 0; }

    std::string getName() const override { return name; }
};
