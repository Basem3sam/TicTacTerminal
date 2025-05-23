#pragma once
#include <string>
#include "BotDifficulty.h"

enum class PlayerType { Human, Bot };

struct PlayerInfo {
  std::string name;
  char symbol;
  PlayerType type = PlayerType::Human; // "human" or "bot"
  BotDifficulty difficulty = BotDifficulty::Easy;
};
