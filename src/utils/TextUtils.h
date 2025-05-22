#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "PlayerInfo.h"
#include "TerminalStyle.h"

namespace TextUtils {

  inline void sleepMilliSec(int delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }

  // Slowly prints text with optional color/style
  inline void slowPrint(const std::string& text, int delay = 50, const std::string& color = RESET) {
    std::cout << color;
    for (char c : text) {
      std::cout << c << std::flush;
      sleepMilliSec(delay);
    }
    std::cout << RESET;
  }

  // Instant styled print
  inline void styledPrint(const std::string& text, const std::string& style = RESET) {
    std::cout << style << text << RESET;
  }

  // Player type string
  inline std::string playerTypeToString(PlayerType type) {
    switch (type) {
      case PlayerType::Human: return "Human";
      case PlayerType::Bot: return "Bot";
      default: return "Unknown";
    }
  }
}
