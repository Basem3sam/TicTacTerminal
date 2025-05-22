#include "Validation.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <cctype>

bool Valid::isValidName(const std::string& name) {
  if (name.empty()) return false;

  // Trim spaces and check that something remains
  std::string trimmed;
  std::copy_if(name.begin(), name.end(), std::back_inserter(trimmed), [](char c) {
    return !isspace(c);
  });

  if (trimmed.empty()) return false;

  return std::all_of(name.begin(), name.end(), [](char c) {
    return isalpha(c) || isspace(c);
  });
}


bool Valid::isValidSymbol(char symbol) {
      symbol = toupper(symbol);
      return (symbol == 'X' || symbol == 'O');
    }

bool Valid::isSameName(const std::string &n1, const std::string &n2) {
  return (n1 == n2);
}

bool Valid::isValidMove(const char platform[Board::MAX_HEIGHT][Board::MAX_WIDTH], int move) {
  //max_width ==> no. columns in the matrix
  //max_height ==> no. raws in the matrix
  //the product is the no. of choices
  if (move < 1 || move > Board::MAX_WIDTH * Board::MAX_HEIGHT) return false;

  int row = (move - 1) / Board::MAX_WIDTH;
  int col = (move - 1) % Board::MAX_WIDTH;

  return platform[row][col] != 'X' && platform[row][col] != 'O';
}

bool Valid::isNumeric(const std::string& input) {
  if (input.empty()) return false;
  return std::all_of(input.begin(), input.end(), ::isdigit);
}

bool Valid::isWin(char platform[Board::MAX_HEIGHT][Board::MAX_WIDTH], char symbol) {
  for (int i = 0; i < 3; i++) {
    if (platform[i][0] == symbol && platform[i][1] == symbol && platform[i][2] == symbol)
      return true; //==> for rows
    if (platform[0][i] == symbol && platform[1][i] == symbol && platform[2][i] == symbol)
      return true; //==> for columns
  }
  //diagonals
  if (platform[0][0] == symbol && platform[1][1] == symbol && platform[2][2] == symbol)
    return true;
  if (platform[0][2] == symbol && platform[1][1] == symbol && platform[2][0] == symbol)
    return true;

  return false;
}
