#pragma once

#ifdef _WIN32
  #define CLEAR_COMMAND "cls"
#else
  #define CLEAR_COMMAND "clear"
#endif

struct Board {
  static const short MAX_WIDTH = 3;
  static const short MAX_HEIGHT = 3;

  char platform[MAX_HEIGHT][MAX_WIDTH];

  Board();

  void reset();
};

enum class GameMode {
  SinglePlayer,
  MultiPlayer
};