#include <iostream>
#include <memory>
#include <SFML/Audio.hpp>
#include "core/Game.h"
#include "ui/GameUI.h"     // Terminal UI
#include "ui/GameGUI.h"     // Graphical UI
#include "ui/IGameUI.h"

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
      std::cout << "Choose UI mode:\n";
      std::cout << "1. Terminal\n";
      std::cout << "2. GUI\n";
      std::cout << "Enter choice (1 or 2): ";

      std::string input;
      std::getline(std::cin, input);

      if (input == "1") {
          ui = std::make_unique<GameUI>();
          break;
      } else if (input == "2") {
          ui = std::make_unique<GameGUI>();
          break;
      } else {
          std::cout << "Invalid choice. Please enter 1 or 2.\n\n";
      }
  }

  Game game(ui.get());
  game.loop();

  std::cout << "Press Enter to exit...\n";
  std::cin.get();
  return 0;
}
