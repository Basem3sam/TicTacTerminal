#pragma once
#include <string>
#include "../entities/Human.h"
#include "../utils/Validation.h"
#include "../utils/Foundation.h"
#include "../utils/PlayerInfo.h"

class GameUI {
  static std::string p1WinMessage();
  static std::string p2WinMessage();
  static std::string botWinMessage();
  bool wantPlay(); 
  char askForSymbol(const std::string& playerName);
  public:
    static void printWinMessage(Human & player);
    static void sleepMilliSec(int delay); 
    static void slowPrint(const std::string& text, int delay = 50);
    void printBoard(char board[Board::MAX_HEIGHT][Board::MAX_WIDTH]);
    bool wantPlayUI(); 
    GameMode askGameMode();
    PlayerInfo promptPlayerInfo(int playerNumber, char takenSymbol); 
    void printWelcome(); 
};