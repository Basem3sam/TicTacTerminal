#pragma once
#include "../utils/PlayerInfo.h"
#include "../utils/Foundation.h"
#include "../entities/Human.h"

class IGameUI {
public:
  virtual ~IGameUI() = default;
  virtual PlayerInfo promptPlayerInfo(int playerNumber, char takenSymbol, bool askForType = true) = 0;
  virtual bool wantPlay() = 0;
  virtual GameMode askGameMode() = 0;
  virtual short getPlayerMove(const std::string& name, char symbol, const char board[3][3]) = 0;
  virtual void printBoard(char board[Board::MAX_HEIGHT][Board::MAX_WIDTH]) = 0;
  virtual void printWinMessage(Human& player) = 0;
  virtual void printWelcome() = 0;
  virtual void printPlayerAdded(const Player& player) = 0;
  virtual void printDrawMessage() = 0;
  virtual void printInvalidMoveMessage() = 0;
  virtual void printInvalidInputMessage() = 0;
  virtual void displayGameOver() = 0;
};
