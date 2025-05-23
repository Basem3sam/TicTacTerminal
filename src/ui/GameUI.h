#pragma once
#include "IGameUI.h"
#include <string>

class GameUI : public IGameUI {
  static std::string p1WinMessage();
  static std::string p2WinMessage();
  static std::string botWinMessage();
  char askForSymbol(const std::string& playerName);
  public:
    void printWelcome() override; 
    void printWinMessage(Player& player) override;
    void printBoard(char board[Board::MAX_HEIGHT][Board::MAX_WIDTH]) override;
    void printPlayerAdded(const Player &player) override;
    bool wantPlay() override; 
    GameMode askGameMode() override;
    PlayerInfo promptPlayerInfo(int playerNumber, char takenSymbol, bool askForType = true) override;
    short getPlayerMove(const std::string& name, char symbol, const char board[3][3]) override;
    void printDrawMessage() override;
    void displayGameOver() override;
    void printInvalidMoveMessage() override;
    void printInvalidInputMessage() override;
    BotDifficulty askBotDifficulty() override;
  };

