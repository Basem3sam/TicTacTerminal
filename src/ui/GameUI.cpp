#include "GameUI.h"
#include <iostream>
#include <chrono>
#include <thread>
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

    void GameUI::printWinMessage(Human & player){
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

    void GameUI::sleepMilliSec(int delay) {
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    void GameUI::slowPrint(const std::string& text, int delay) {
      for (char c : text) {
        std::cout << c << std::flush;
        sleepMilliSec(delay);
      }
    }

    void GameUI::printBoard(char board[Board::MAX_HEIGHT][Board::MAX_WIDTH]) {
      system(CLEAR_COMMAND);
      std::cout << "\n";
      for (int i = 0; i < 3; i++) {
        std::cout << " ";
        for (int j = 0; j < 3; j++) {
          std::cout << " " << (board[i][j] == '\0' ? ' ' : board[i][j]) << " ";
          if (j < 2) std::cout << "|";
        }
        std::cout << "\n";
        if (i < 2) std::cout << " ---+---+---\n";
      }
      std::cout << "\n"; 
    }

    bool GameUI::wantPlayUI() {
      return wantPlay();
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
          slowPrint("Invalid input. Please enter 1 for Single Player or 2 for Multiplayer.",20);
          sleepMilliSec(750);
        }
    }
}

    void GameUI::printWelcome() {
      system(CLEAR_COMMAND);
      slowPrint("     Welcome to the Ultimate XO Game!\n", 60);
      slowPrint("     Created by: Basem Esam\n", 60);
      slowPrint("     Get ready to play", 80);
      slowPrint("...",250);
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
