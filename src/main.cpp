#include "utils/TextUtils.h"
#include "ui/UISwitcher.h"
#include "core/Game.h"

#ifdef ENABLE_SFML_GUI
#include <SFML/Audio.hpp>
#include "ui/GameGUI.h"
#endif

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
#ifdef ENABLE_SFML_GUI
  sf::Music music;
  if (!music.openFromFile("media/music.wav")) {
    std::cerr << "Could not load music\n";
  } else {
    music.setLoop(true);
    music.play();
    music.setVolume(100);
  }
#endif

  while (XOGame()) {}

  std::cout << FG_BRIGHT_BLACK << "Press Enter to exit..." << RESET;
  std::cin.get();
  return 0;
}
