#include <iostream>
#include <cstdlib>
#include "core/Game.h"
int main() {
  
  Game::loop();
  
  std::cout << "Press Enter to exit...";
  std::cin.ignore();
  std::cin.get(); //pause
  return 0;
}