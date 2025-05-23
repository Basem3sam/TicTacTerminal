#include "../utils/TerminalStyle.h"
#include "../utils/TextUtils.h"
#include "UISwitcher.h"
#include "GameGUI.h"     // Graphical UI
#include "GameUI.h"     // Terminal UI

void UISwitcher::initGetChoice(std::string &input) {
  system(CLEAR_COMMAND);  // Clear the screen before showing the menu again

  std::cout << FG_CYAN << BOLD;
  std::cout << "+============================================+\n";
  std::cout << "|             UI MODE SELECTION              |\n";
  std::cout << "+--------------------------------------------+\n";
  std::cout << RESET;
  
  std::cout << FG_YELLOW << "| " << RESET << FG_GREEN << "1. Terminal" << RESET;
  std::cout << std::string(42 - std::string("1. Terminal").length(), ' ') << FG_YELLOW << " |\n";

  std::cout << FG_YELLOW << "| " << RESET << FG_GREEN << "2. GUI (Graphical User Interface)" << RESET;
  std::cout << std::string(42 - std::string("2. GUI (Graphical User Interface)").length(), ' ') << FG_YELLOW << " |\n";

  std::cout << FG_YELLOW << "| " << RESET << FG_RED << "3. Exit" << RESET;
  std::cout << std::string(42 - std::string("3. Exit").length(), ' ') << FG_YELLOW << " |\n";

  std::cout << FG_CYAN << "+============================================+\n" << RESET;

  std::cout << FG_BRIGHT_WHITE << BOLD << "\nEnter choice (1, 2 or 3): " << RESET;

  std::getline(std::cin, input);
}

bool UISwitcher::initWindow(std::unique_ptr<IGameUI> &ui) {
  while (true) {
    std::string input;
    initGetChoice(input);
    if (input == "1") {
      ui = std::make_unique<GameUI>();
      return true;
    } else if (input == "2") {
      ui = std::make_unique<GameGUI>();
      return true;
    } else if (input == "3") {
      std::cout << FG_BRIGHT_RED << "\nExiting the game. Goodbye!\n" << RESET;
      return false;  // Indicate quit
    } else {
      std::cout << FG_RED << "\n[!] Invalid choice. Please enter 1, 2 or 3.\n" << RESET;
      TextUtils::sleepMilliSec(1200);
    }
  }
}