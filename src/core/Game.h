#pragma once
#include "../utils/Foundation.h"
#include "../utils/PlayerInfo.h"
#include "../entities/Human.h"
#include "../entities/Bot.h"
#include "../ui/IGameUI.h"
#include <memory>
#include <array>


class Game {
  IGameUI* UI;
  Board board;
  std::array<std::unique_ptr<Player>, 2> players;
  Bot BOT;
  Human singlePlayer;

  void addPlayer(int index, const PlayerInfo& info);
  GameMode setup();
  void multiPlay();
  void singlePlay();
  // static Human addPlayer(int playerNumber, char takenSymbol = '\0'); OLD

public:
  explicit Game(IGameUI* ui);
  bool play();
};
