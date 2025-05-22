#pragma once
#include <string>

enum class PlayerType { Human, Bot };

struct PlayerInfo {
  std::string name;
  char symbol;
  PlayerType type; // "human" or "bot"
};
