#include "Validation.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <cctype>

bool Valid::isValidName(const std::string& name) {
      if (name.empty()) return false;

      // Check that every character is alphabetic or space
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

bool Valid::isValidMove(char platform[Board::MAX_HEIGHT][Board::MAX_WIDTH], int move) {
  //max_width ==> no. columns in the matrix
  //max_height ==> no. raws in the matrix
  //the product is the no. of choices
  if (move < 1 || move > Board::MAX_WIDTH * Board::MAX_HEIGHT) return false;

  int row = (move - 1) / Board::MAX_HEIGHT;
  int col = (move - 1) % Board::MAX_HEIGHT;

  return platform[row][col] != 'X' && platform[row][col] != 'O';
}

short Valid::askValidMove(char platform[Board::MAX_HEIGHT][Board::MAX_WIDTH]) {
  int move;

  while (true) {
    std::cout << "Enter your move: ";
    std::cin >> move;

    // reseting the input stream
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number.\n";
        continue;
    }

    if (!isValidMove(platform, move)) {
        std::cout << "Invalid move. Try a different position.\n";
        continue;
    }
    return move;
  }
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
