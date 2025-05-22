#include "../utils/TextUtils.h"
#include "GameUI.h"
#include <iostream>
#include <limits>

std::string GameUI::p1WinMessage(){
      return R"(
  ___ _                     _  __      ___         
 | _ \ |__ _ _  _ ___ _ _  / | \ \    / (_)_ _  ___
 |  _/ / _` | || / -_) '_| | |  \ \/\/ /| | ' \(_-<
 |_| |_\__,_|\_, \___|_|   |_|   \_/\_/ |_|_||_/__/
             |__/                                  
)";
  }
std::string GameUI::p2WinMessage(){
    return R"(
  ___ _                     ___  __      ___         
 | _ \ |__ _ _  _ ___ _ _  |_  ) \ \    / (_)_ _  ___
 |  _/ / _` | || / -_) '_|  / /   \ \/\/ /| | ' \(_-<
 |_| |_\__,_|\_, \___|_|   /___|   \_/\_/ |_|_||_/__/
             |__/

    )";
  }
std::string GameUI::botWinMessage(){
    return R"(
  
  ___  ___ _____  __      ___         
 | _ )/ _ \_   _| \ \    / (_)_ _  ___
 | _ \ (_) || |    \ \/\/ /| | ' \(_-<
 |___/\___/ |_|     \_/\_/ |_|_||_/__/
                                      
    )";
  }

bool GameUI::wantPlay() {
    std::string response;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nDo you want to play again? (y/n): ";
    std::getline(std::cin, response);

    for (char& c : response) c = tolower(c);

    return (response == "y" || response == "yes" || response == "1");
  }

char GameUI::askForSymbol(const std::string& playerName) {
    char symbol;
    while (true) {
        std::cout << playerName << ", choose your symbol (X/O): ";
        std::cin >> symbol;
        if (Valid::isValidSymbol(symbol)) {
            std::cin.ignore();
            return toupper(symbol);
        }
        std::cout << "Invalid symbol! Please enter X or O.\n";
    }
}

PlayerInfo GameUI::promptPlayerInfo(int playerNumber, char takenSymbol, bool askForType) {
  PlayerInfo info;
  std::string inputName;
  char inputSymbol;

  system(CLEAR_COMMAND);

  std::cout << "Enter name for Player " << playerNumber << ": ";
  std::getline(std::cin, inputName);

  while (!Valid::isValidName(inputName)) {
    std::cout << "Invalid name. Please enter again: ";
    std::getline(std::cin, inputName);
  }
  info.name = inputName;

  // Ask for player symbol
  while (true) {
    std::cout << "Choose your symbol (X or O): ";
    std::cin >> inputSymbol;
    std::cin.clear(); // clear fail state
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    inputSymbol = toupper(inputSymbol);

    if (!Valid::isValidSymbol(inputSymbol)) {
      std::cout << "Invalid symbol. Only 'X' or 'O' allowed. Try again.\n";
      continue;
    }
    if (inputSymbol == takenSymbol) {
      std::cout << "Symbol already taken by another player. Choose a different one.\n";
      continue;
    }
    break;
  }
  info.symbol = inputSymbol;

  // Ask for player type
  if (askForType) {
    std::string typeInput;
    while (true) {
      std::cout << "Is this player a human or bot? (h/b): ";
      std::getline(std::cin, typeInput);

      if (typeInput == "h" || typeInput == "H") {
        info.type = PlayerType::Human;
        break;
      } else if (typeInput == "b" || typeInput == "B") {
        info.type = PlayerType::Bot;
        break;
      } else {
        std::cout << "Invalid input. Please enter 'h' for human or 'b' for bot.\n";
      }
    }
  } else {
    info.type = PlayerType::Human; // default
  }
  return info;
}

void GameUI::printWinMessage(Human& player){
  switch (player.getId())
  {
  case 1:
    std::cout << "========================================================" << std::endl;
    std::cout << p1WinMessage() << std::endl;
    std::cout << player.getName() << " wins! Current Score: " << player.getScore() << "\n";
  break;
  case 2:
    std::cout << "========================================================" << std::endl;
    std::cout << p2WinMessage() << std::endl;
    std::cout << player.getName() << " wins! Current Score: " << player.getScore() << "\n";
    break;
  case 0:
    std::cout << "=========================================================" << std::endl;
    std::cout << botWinMessage() << std::endl;
    std::cout << "humans had failed again :((" << std::endl;
    break;
  default:
    std::cout << "=========================================================" << std::endl;
    std::cout << "Unknown winner...\n";
    break;
  }
  // std::cout << "[DEBUG] ID passed to printWinMessage: " << player.getId() << "\n";
}

void GameUI::printBoard(char board[Board::MAX_HEIGHT][Board::MAX_WIDTH]) {
  system(CLEAR_COMMAND);
  std::cout << "\n";
  for (int i = 0; i < Board::MAX_HEIGHT; i++) {
    std::cout << " ";
    for (int j = 0; j < Board::MAX_WIDTH; j++) {
      std::cout << " " << (board[i][j] == '\0' ? ' ' : board[i][j]) << " ";
      if (j < 2) std::cout << "|";
    }
    std::cout << "\n";
    if (i < 2) std::cout << " ---+---+---\n";
  }
  std::cout << "\n"; 
}

GameMode GameUI::askGameMode() {
  std::string input;

  while (true) {
    system(CLEAR_COMMAND);
    std::cout << "Choose game mode:\n";
    std::cout << "1. Single Player (vs Bot)\n";
    std::cout << "2. Multiplayer (vs Friend)\n";
    std::cout << "Enter choice (1 or 2): ";

    std::getline(std::cin, input);
    // Remove leading/trailing spaces
    input.erase(0, input.find_first_not_of(" \t\n\r\f\v"));
    input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1);

    if (input == "1" || input == "single" || input == "Single" || input == "S" || input == "s") {
      return GameMode::SinglePlayer;
    }
    else if (input == "2" || input == "multi" || input == "Multi" || input == "M" || input == "m") {
      return GameMode::MultiPlayer;
    }
    else {
      TextUtils::slowPrint("Invalid input. Please enter 1 for Single Player or 2 for Multiplayer.",20);
      TextUtils::sleepMilliSec(750);
    }
  }
}

void GameUI::printWelcome() {
  system(CLEAR_COMMAND);
  TextUtils::slowPrint("     Welcome to the Ultimate XO Game!\n", 60);
  TextUtils::slowPrint("     Created by: Basem Esam\n", 60);
  TextUtils::slowPrint("     Get ready to play", 80);
  TextUtils::slowPrint("...",250);
  TextUtils::sleepMilliSec(2000);
}

void GameUI::printPlayerAdded(const Player& player) {
  TextUtils::slowPrint("Player \"" + player.getName() + "\" added with symbol '" + player.getSymbol() + "'", 100);
  TextUtils::sleepMilliSec(900);
}

void GameUI::printDrawMessage() {
  std::cout << "\nIt's a draw! No one wins this round.\n";
}

short GameUI::getPlayerMove(const std::string& name, char symbol, const char board[3][3]) {
  std::string input;

  while (true) {
    std::cout << "=> " << name << "'s turn (" << symbol << "). Enter a position (1-9): ";
    std::cin >> input;

    if (!Valid::isNumeric(input)) {
      printInvalidInputMessage();
      continue;
    }

    int move = std::stoi(input);

    if (!Valid::isValidMove(board, move)) {
      printInvalidMoveMessage();
      continue;
    }

    return move;
  }
}

void GameUI::printInvalidMoveMessage() {
  std::cout << "Invalid move. Try a different position.\n";
}

void GameUI::printInvalidInputMessage() {
  std::cout << "Invalid input. Please enter a number.\n";
}

void GameUI::displayGameOver() {
    system(CLEAR_COMMAND);
    using namespace std::chrono_literals;
    std::cout << "\n\n";
    std::cout << "=============================================\n";
    std::cout << "               \033[1;31mG A M E   O V E R\033[0m               \n";
    std::cout << "=============================================\n";
    std::cout << "\n";
    std::cout << "        \033[1;36mEngine created by Basem Esam\033[0m\n";
    std::cout << "\n";
    std::cout << "=============================================\n";
    std::this_thread::sleep_for(3s); // Pause for 3 seconds
}