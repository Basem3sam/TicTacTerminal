#include "../utils/TextUtils.h"
#include "../utils/Validation.h"
#include "../utils/TerminalStyle.h"
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

  TextUtils::slowPrint("\nDo you want to play again? (y/n): ", 40);
  std::getline(std::cin, response);

  for (char& c : response) c = tolower(c);

  if (response == "y" || response == "yes" || response == "1") {
    TextUtils::slowPrint("Great! Starting a new game...", 50);
    TextUtils::sleepMilliSec(1000);
    return true;
  } else {
    TextUtils::slowPrint("Thank you for playing. Exiting...", 50);
    TextUtils::sleepMilliSec(1000);
    return false;
  }
}

PlayerInfo GameUI::promptPlayerInfo(int playerNumber, char takenSymbol, bool askForType) {
  PlayerInfo info;
  std::string inputName;
  char inputSymbol;

  system(CLEAR_COMMAND);

  std::cout << FG_BRIGHT_BLACK;
  std::cout << "+--------------------------------------------------+\n";
  std::cout << RESET;
  std::cout << FG_CYAN << BOLD << "  Player " << playerNumber << " setup\n" << RESET;
  std::cout << FG_BRIGHT_BLACK;
  std::cout << "+--------------------------------------------------+\n";
  std::cout << RESET;

  // Prompt for player name
  std::cout << FG_YELLOW << "  Enter name for Player " << playerNumber << ": " << RESET;
  std::getline(std::cin, inputName);

  while (!Valid::isValidName(inputName)) {
    std::cout << FG_RED << "  Invalid name. Please enter again: " << RESET;
    std::getline(std::cin, inputName);
  }
  info.name = inputName;

  // Prompt for symbol
  while (true) {
    std::cout << FG_YELLOW << "  Choose your symbol (X or O): " << RESET;
    std::cin >> inputSymbol;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    inputSymbol = toupper(inputSymbol);

    if (!Valid::isValidSymbol(inputSymbol)) {
      std::cout << FG_RED << "  Invalid symbol. Only 'X' or 'O' allowed. Try again.\n" << RESET;
      continue;
    }
    if (inputSymbol == takenSymbol) {
      std::cout << FG_RED << "  Symbol already taken by another player. Choose a different one.\n" << RESET;
      continue;
    }
    break;
  }
  info.symbol = inputSymbol;

  // Prompt for player type
  if (askForType) {
    std::string typeInput;
    while (true) {
      std::cout << FG_YELLOW << "  Is this player a human or bot? (h/b): " << RESET;
      std::getline(std::cin, typeInput);

      if (typeInput == "h" || typeInput == "H") {
        info.type = PlayerType::Human;
        break;
      } else if (typeInput == "b" || typeInput == "B") {
        info.type = PlayerType::Bot;
        break;
      } else {
        std::cout << FG_RED << "  Invalid input. Please enter 'h' for human or 'b' for bot.\n" << RESET;
      }
    }
  } else {
    info.type = PlayerType::Human;
  }

  std::cout << FG_BRIGHT_GREEN << "\n  Player " << playerNumber << " setup complete!\n" << RESET;
  std::cout << FG_BRIGHT_BLACK << "+--------------------------------------------------+\n" << RESET;

  return info;
}

void GameUI::printWinMessage(Player& player) {
  const std::string border = FG_BRIGHT_BLACK "+========================================================+\n" RESET;
  const std::string scoreLabel = FG_YELLOW "  Current Score: " + std::string(BOLD) + std::to_string(player.getScore()) + RESET "\n";

  std::cout << border;

  const int id = player.getId();
  const std::string& name = player.getName();

  if (player.getRule() == "Bot") {
    TextUtils::styledPrint("  " + botWinMessage() + "\n", FG_RED);
    TextUtils::styledPrint("  The machines have won this round... again.\n", FG_BRIGHT_RED);
  } else if (player.getId() == 1) {
    TextUtils::styledPrint("  " + p1WinMessage() + "\n", FG_BRIGHT_CYAN);
    TextUtils::styledPrint("  " + name + " wins the round!\n", std::string(FG_BRIGHT_GREEN) + BOLD);
    std::cout << scoreLabel;
  } else {
    TextUtils::styledPrint("  " + p2WinMessage() + "\n", FG_MAGENTA);
    TextUtils::styledPrint("  " + name + " takes the victory!\n", std::string(FG_BRIGHT_GREEN) + BOLD);
    std::cout << scoreLabel;
  }

  std::cout << border;
}

void GameUI::printBoard(char board[Board::MAX_HEIGHT][Board::MAX_WIDTH]) {
  system(CLEAR_COMMAND);
  std::cout << "\n";
  std::cout << FG_BRIGHT_BLACK << "+===== TIC TAC TOE =====+\n" << RESET;

  for (int i = 0; i < Board::MAX_HEIGHT; i++) {
    std::cout << "      " << FG_BRIGHT_BLACK << " " << RESET;

    for (int j = 0; j < Board::MAX_WIDTH; j++) {
        char cell = board[i][j];
        std::string cellColor;

        if (cell == 'X') {
            cellColor = FG_BRIGHT_RED;
        } else if (cell == 'O') {
            cellColor = FG_BRIGHT_BLUE;
        } else {
            cellColor = FG_BRIGHT_BLACK;
        }

        std::cout << " " << cellColor << (cell == '\0' ? ' ' : cell) << RESET << " ";
        if (j < 2) std::cout << FG_BRIGHT_BLACK << "|" << RESET;
    }

    std::cout << "\n";
    if (i < 2) std::cout << "      " << FG_BRIGHT_BLACK << " ---+---+---" << RESET << "\n";
}


  std::cout << FG_BRIGHT_BLACK << "+=======================+\n\n" << RESET;
}

GameMode GameUI::askGameMode() {
  std::string input;

  while (true) {
    system(CLEAR_COMMAND);

    std::cout << FG_BRIGHT_BLACK << "+=============================================+\n";
    std::cout << "|                                             |\n";
    std::cout << "|            " << FG_YELLOW << BOLD << "Select Your Game Mode" << RESET << FG_BRIGHT_BLACK << "            |\n";
    std::cout << "|                                             |\n";
    std::cout << "+=============================================+\n" << RESET;

    std::cout << "\n";
    TextUtils::slowPrint(FG_BRIGHT_GREEN "  [1] Single Player (vs Bot)\n", 20);
    TextUtils::slowPrint(FG_BRIGHT_GREEN "  [2] Multiplayer (vs Friend)\n" RESET, 20);
    TextUtils::slowPrint(FG_BRIGHT_RED "  [3] Exit..\n" RESET, 20);

    std::cout << "\n" << FG_CYAN << "Enter your choice: " << RESET;
    std::getline(std::cin, input);

    // Trim whitespace
    input.erase(0, input.find_first_not_of(" \t\n\r\f\v"));
    input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1);

    if (input == "1" || input == "single" || input == "Single" || input == "S" || input == "s") {
    
      std::cout << "\n" << FG_GREEN;
      TextUtils::slowPrint(">> You selected Single Player mode. Loading...\n", 25);
      std::cout << RESET;
      TextUtils::sleepMilliSec(1000);
    
      return GameMode::SinglePlayer;
    
    } else if (input == "2" || input == "multi" || input == "Multi" || input == "M" || input == "m") {
      std::cout << "\n" << FG_GREEN;
      TextUtils::slowPrint(">> You selected Multiplayer mode. Preparing match...\n", 25);
      std::cout << RESET;
      TextUtils::sleepMilliSec(1000);
    
      return GameMode::MultiPlayer;
    
    } else if (input == "3" || input == "exit" || input == "Exit" || input == "Q" || input == "q") {
      std::cout << "\n" << FG_RED;
      TextUtils::slowPrint(">> Exiting...\n", 80);
      std::cout << RESET;
      TextUtils::sleepMilliSec(1000);

      return GameMode::Quit;
    } else {
      std::cout << "\n" << FG_RED;
      TextUtils::slowPrint("!! Invalid input. Please enter 1 or 2.\n", 20);
      std::cout << RESET;
      TextUtils::sleepMilliSec(1000);
    }
  }
}

void GameUI::printWelcome() {
    system(CLEAR_COMMAND);

    using namespace TextUtils;

    const std::string topBorder     = FG_CYAN BOLD "      +------------------------------------------------------------+\n";
    const std::string spacerLine    = FG_CYAN BOLD "      |                                                            |\n";
    const std::string bottomBorder  = FG_CYAN BOLD "      +------------------------------------------------------------+\n";

    // Top Border
    slowPrint(topBorder, 1);

    // Title Line
    slowPrint(FG_CYAN BOLD "      |" RESET, 1);
    slowPrint("              ", 2);
    slowPrint(FG_MAGENTA BOLD "Welcome to the ", 60);
    slowPrint(FG_BRIGHT_MAGENTA BOLD "Ultimate XO Game!", 60);
    slowPrint(FG_CYAN BOLD "              |\n", 2);

    // Spacer
    slowPrint(spacerLine, 1);

    // Creator Line
    slowPrint(FG_CYAN BOLD "      |" RESET, 1);
    slowPrint("                   ", 2);
    slowPrint(FG_YELLOW BOLD "Created by: ", 60);
    slowPrint(FG_GREEN BOLD "Basem Esam", 60);
    slowPrint(FG_CYAN BOLD "                   |\n", 2);

    // Spacer
    slowPrint(spacerLine, 1);

    // Bottom Border
    slowPrint(bottomBorder, 1);

    // Loading Message
    slowPrint("\n     ", 1);
    slowPrint(FG_BRIGHT_BLACK "Initializing", 100);
    slowPrint(FG_BRIGHT_BLACK "...\n", 250);

    // Final pause
    sleepMilliSec(1500);
}

void GameUI::printPlayerAdded(const Player& player) {
  std::string msg = std::string(FG_GREEN) + BOLD + "Player \"" + RESET +
                    std::string(FG_BRIGHT_YELLOW) + player.getName() + RESET +
                    std::string(FG_GREEN) + BOLD + "\" added with symbol '" + RESET +
                    std::string(FG_BRIGHT_CYAN) + player.getSymbol() + RESET +
                    std::string(FG_GREEN) + BOLD + "'" + RESET;
  TextUtils::slowPrint(msg, 60);
  TextUtils::sleepMilliSec(900);
}

void GameUI::printDrawMessage() {
  std::cout << FG_BRIGHT_BLACK;
  std::cout << "+--------------------------------------------------+\n";
  std::cout << RESET;
  std::cout << FG_BRIGHT_MAGENTA << BOLD << "  It's a draw! No one wins this round." << RESET << "\n";
  std::cout << FG_BRIGHT_BLACK;
  std::cout << "+--------------------------------------------------+\n";
  std::cout << RESET;
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
  std::cout << FG_RED BOLD << "Invalid move." << RESET << " Try a different position.\n";
}

void GameUI::printInvalidInputMessage() {
  std::cout << FG_RED BOLD << "Invalid input." << RESET << " Please enter a valid number.\n";
}

void GameUI::displayGameOver() {
  system(CLEAR_COMMAND);
  using namespace std::chrono_literals;
    std::cout << FG_BRIGHT_BLACK;
    std::cout << "+============================================+\n";
    std::cout << RESET;

    std::cout << "               " << FG_RED << "G A M E   O V E R" << RESET << "               \n";

    std::cout << FG_BRIGHT_BLACK;
    std::cout << "+============================================+\n\n";
    std::cout << RESET;

    std::cout << "        " << FG_CYAN << "Engine created by Basem Esam" << RESET << "\n\n";

    std::cout << FG_BRIGHT_BLACK;
    std::cout << "+============================================+\n";
    std::cout << RESET;

    std::this_thread::sleep_for(3s); // Pause for 3 seconds
}

BotDifficulty GameUI::askBotDifficulty() {
  int choice;

  while (true) {
    std::cout << "\n";
    TextUtils::slowPrint("Please choose the bot difficulty level:\n\n", 30, FG_CYAN);

    TextUtils::styledPrint("  1. Easy   ", FG_BRIGHT_GREEN);
    TextUtils::slowPrint(" - For a relaxed game with simple moves.\n", 15);

    TextUtils::styledPrint("  2. Medium ", FG_BRIGHT_YELLOW);
    TextUtils::slowPrint(" - A balanced challenge for casual players.\n", 15);

    TextUtils::styledPrint("  3. Hard   ", FG_BRIGHT_RED);
    TextUtils::slowPrint(" - For those seeking a serious test of skill.\n\n", 15);

    TextUtils::styledPrint("Enter your choice [1-3]: ", FG_CYAN);

    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > 3) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      TextUtils::styledPrint("\nInvalid input. Please enter a number between 1 and 3.\n", FG_BRIGHT_RED);
      TextUtils::sleepMilliSec(1500);
      std::cout << "\n";
      continue;
    }

    std::cout << "\n";

    switch (choice) {
      case 1:
        TextUtils::styledPrint("Bot difficulty set to Easy. Good luck! :)\n\n", FG_BRIGHT_GREEN);
        return BotDifficulty::Easy;

      case 2:
        TextUtils::styledPrint("Bot difficulty set to Medium. Challenge accepted!\n\n", FG_BRIGHT_YELLOW);
        return BotDifficulty::Medium;

      case 3:
        TextUtils::styledPrint("Bot difficulty set to Hard. Brace yourself! ⚔️\n\n", FG_BRIGHT_RED);
        return BotDifficulty::Hard;

      default:
        return BotDifficulty::Easy;  // Fallback, should never reach here
    }
  }
}
