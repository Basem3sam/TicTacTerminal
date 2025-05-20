#pragma once
#include "../ui/GameUI.h"
#include "../utils/Foundation.h"
#include "../entities/Human.h"
#include "../entities/Bot.h"
#include <utility>

class Game {
  static GameUI UI;
  static Board board;
  static std::pair<Human, Human> players;
  static Bot BOT;
  static Human singlePlayer;

  static Human addPlayer(int playerNumber, char takenSymbol = '\0');

public:
  static void loop();
  static void setup();
  static void multiPlay();
};
