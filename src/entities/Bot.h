#pragma once
#include "Player.h"
class Bot : private Player {
  const short id = 0;
  public:
  Bot() : Player("BOT"){}
  short getId();
};