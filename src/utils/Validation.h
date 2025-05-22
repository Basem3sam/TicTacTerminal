#pragma once
#include "Foundation.h"
#include <string>

class Valid{
  public:
    static bool isValidName(const std::string& name);
    static bool isValidSymbol(char symbol);
    static bool isSameName(const std::string &n1, const std::string &n2);
    static bool isValidMove(const char platform[Board::MAX_HEIGHT][Board::MAX_WIDTH], int move);
    static bool isNumeric(const std::string& input);
    static bool isWin(char platform[Board::MAX_HEIGHT][Board::MAX_WIDTH], char symbol);
};
