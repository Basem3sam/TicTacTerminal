#include "utils/TextUtils.h"
#include "ui/UISwitcher.h"
#include <SFML/Audio.hpp>
#include "core/Game.h"
#include <iostream>
#include <memory>

bool XOGame() {
  std::unique_ptr<IGameUI> ui;
  if(!UISwitcher::initWindow(ui)) {
    return false;
  }

  Game game(ui.get());
  return game.play();
}

int main() {
  sf::Music music;
  if (!music.openFromFile("media/music.wav")) {
      std::cerr << "Could not load music\n";
  } else {
      music.setLoop(true);
      music.play();
      music.setVolume(100);
  }

  while (!XOGame()) {
    // If XOGame returns false, user quit — re-show UI mode selection
    continue;
  }

  std::cout << FG_BRIGHT_BLACK << "\nPress Enter to exit..." << RESET;
  std::cin.get();
  return 0;
}
