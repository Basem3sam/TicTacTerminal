#pragma once
#include "../ui/GameUI.h"
#include "../utils/Foundation.h"
#include "../entities/Human.h"
#include "../entities/Bot.h"
#include <utility>
#include <memory>
#include <array>

class Game {
  static GameUI UI;
  static Board board;
  static std::array<std::unique_ptr<Player>, 2> players;
  static Bot BOT;
  static Human singlePlayer;
  static void addPlayer(int index, const PlayerInfo& info);
  // static Human addPlayer(int playerNumber, char takenSymbol = '\0'); OLD

public:
  static void loop();
  static void setup();
  static void multiPlay();
};
