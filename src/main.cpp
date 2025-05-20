#include <iostream>
#include <SFML/Audio.hpp>
#include "core/Game.h"
int main() {
  sf::Music music;
  if(!music.openFromFile("media/music.wav")) {
    std::cerr << "Could not load music\n";
  }
  music.setLoop(true);
  music.play();
  music.setVolume(100);
  Game::loop();
  
  std::cout << "Press Enter to exit...\n";
  std::cin.ignore();
  std::cin.get(); //pause
  return 0;
}