#include <iostream>
#include <memory>
#include <SFML/Audio.hpp>
#include "core/Game.h"
#include "ui/GameUI.h"     // Terminal UI
#include "ui/GameGUI.h"     // Graphical UI
#include "ui/IGameUI.h"
#include "utils/TextUtils.h"
#include "utils/TerminalStyle.h"

int main() {
  sf::Music music;
  if (!music.openFromFile("media/music.wav")) {
      std::cerr << "Could not load music\n";
  } else {
      music.setLoop(true);
      music.play();
      music.setVolume(100);
  }

  std::unique_ptr<IGameUI> ui;
  int choice = 0;

  while (true) {
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

    std::string input;
    std::getline(std::cin, input);

    if (input == "1") {
      ui = std::make_unique<GameUI>();
      break;
    } else if (input == "2") {
      ui = std::make_unique<GameGUI>();
      break;
    } else if (input == "3") {
      std::cout << FG_BRIGHT_RED << "\nExiting the game. Goodbye!\n" << RESET;
      return 0;
    } else {
      std::cout << FG_RED << "\n[!] Invalid choice. Please enter 1, 2 or 3.\n" << RESET;
      TextUtils::sleepMilliSec(1200);
    }
  }

  Game game(ui.get());
  game.loop();

  std::cout << FG_BRIGHT_BLACK << "\nPress Enter to exit..." << RESET;
  std::cin.get();
  return 0;
}
