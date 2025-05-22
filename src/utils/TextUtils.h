#pragma once
#include <iostream>
#include "PlayerInfo.h"
#include <string>
#include <chrono>
#include <thread>

namespace TextUtils {
  inline void sleepMilliSec(int delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }

  inline void slowPrint(const std::string& text, int delay = 50) {
    for (char c : text) {
      std::cout << c << std::flush;
      sleepMilliSec(delay);
    }
  }

  inline std::string playerTypeToString(PlayerType type) {
    switch (type) {
      case PlayerType::Human: return "human";
      case PlayerType::Bot: return "bot";
      default: return "unknown";
    }
  }
}
